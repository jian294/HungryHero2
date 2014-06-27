#include "InGameScene.h"
#include "SimpleAudioEngine.h"
#include "GameConstants.h"
#include "ObjectPool.h"
using namespace CocosDenshion;

#define BGWELCOME_MUSIC        "sounds/bgGame.mp3"
#define COFFEE_EFFECT "sounds/coffee.mp3"
#define MUSHROOM_EFFECT "sounds/mushroom.mp3"
#define EAT_EFFECT "sounds/eat.mp3"
#define HIT_EFFECT "sounds/hit.mp3"
#define HURT_EFFECT "sounds/hurt.mp3"

InGameScene::InGameScene(void)
{
}


InGameScene::~InGameScene(void)
{
}

Scene* InGameScene::staScene = NULL;
InGameScene* InGameScene::m_instance = NULL;

Scene* InGameScene::scene()
{
	if(staScene == NULL)
	{
		staScene = Scene::create();

		InGameScene* layer = getInstance();

		staScene->addChild(layer);
	}
	return staScene;
}


InGameScene* InGameScene::getInstance()
{
	if(m_instance == NULL)
	{
		m_instance = (InGameScene*) InGameScene::create();
	}
	return m_instance;
}

bool InGameScene::init()
{
	if(Layer::init())
	{
		//setTouchEnabled(true);

		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = CC_CALLBACK_2(InGameScene::onTouchBegan, this);
		listener->onTouchMoved = CC_CALLBACK_2(InGameScene::onTouchMoved, this);
		listener->onTouchEnded = CC_CALLBACK_2(InGameScene::onTouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

		bg = GameBackground::create();
		bg->setAnchorPoint(ccp(0,0));
		addChild(bg);

		Size size = Director::sharedDirector()->getWinSize();

		m_scorePanel = ScorePanel::create();
		m_scorePanel->setAnchorPoint(ccp(0,1));
		addChild(m_scorePanel);
		m_scorePanel->setPositionY(size.height);

		m_gameOverContainer = GameOverContainer::create();
		m_gameOverContainer->setAnchorPoint(ccp(0,0));
		addChild(m_gameOverContainer, 1);

		SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("graphics/mySpritesheet.plist");

		m_hero = Hero::getInstance();
		addChild(m_hero);

		_preloadMusic();

		m_ItemPool = new ObjectPool(GameConstants::OBJECT_TYPE_ITEM, 30);
		m_foodItemArray = Array::create();
		m_foodItemArray->retain();


		m_eatParticlesPool = new ObjectPool(GameConstants::OBJECT_TYPE_PARTICLE, 30);
		m_eatParticlesArray = Array::create();
		m_eatParticlesArray->retain();

		m_obstaclePool = new ObjectPool(GameConstants::OBJECT_TYPE_OBSTACLE, 30);
		m_obstacleArray = Array::create();
		m_obstacleArray->retain();


		m_windParticlesPool = new ObjectPool(GameConstants::OBJECT_TYPE_PARTICLE, 30);
		m_winParticlesArray = Array::create();
		m_winParticlesArray->retain();

		m_particleCoffee = ParticleSystemQuad::create("Particles/particleCoffee.plist");
		m_particleCoffee->retain();

		m_particleMushroom = ParticleSystemQuad::create("Particles/particleMushroom.plist");
		m_particleMushroom->retain();

		return true;
	}
	return false;
}


void InGameScene::_preloadMusic()
{
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(BGWELCOME_MUSIC);
	SimpleAudioEngine::sharedEngine()->preloadEffect(COFFEE_EFFECT);
	SimpleAudioEngine::sharedEngine()->preloadEffect(MUSHROOM_EFFECT);
	SimpleAudioEngine::sharedEngine()->preloadEffect(EAT_EFFECT);
	SimpleAudioEngine::sharedEngine()->preloadEffect(HIT_EFFECT);
	SimpleAudioEngine::sharedEngine()->preloadEffect(HURT_EFFECT);
}

void InGameScene::onEnter()
{
	Layer::onEnter();

	Size size = Director::sharedDirector()->getWinSize();
	SoundButton* soundBtn = SoundButton::getInstance();
	addChild(soundBtn);
	soundBtn->setPosition(ccp(40, size.height - 40));

	SimpleAudioEngine::sharedEngine()->playBackgroundMusic(BGWELCOME_MUSIC, true);

	startGame();
}


void InGameScene::startGame() 
{
	Size size = Director::sharedDirector()->getWinSize();
	m_hero->setPosition(ccp(250, size.height/2));
	touchY = m_hero->getPositionY();

	this->scheduleUpdate();

	m_gameState = GameConstants::GAME_STATE_FLYING;
	m_lives = GameConstants::HERO_LIVES;

	m_playerSpeed = 0;
	m_obstacleGapCount = 0;
	m_hitObstacle = 0;
	m_mushroomPower = 0;
	m_coffeePower = 0;
	m_distance = 0;
	m_score = 0;

	bg->setSpeed(0);
	m_gameOverContainer->setVisible(false);

	m_scorePanel->setLives(m_lives);
	m_scorePanel->setDistance(m_distance);
	m_scorePanel->setScore(m_score);
}

void InGameScene::update(float delta)
{
	Size size = Director::sharedDirector()->getWinSize();
	if(m_gameState == GameConstants::GAME_STATE_FLYING)
	{
		if (m_coffeePower > 0)
		{
			m_playerSpeed += (GameConstants::HERO_MAX_SPEED - m_playerSpeed) * 0.2;
		}

		if(m_hitObstacle <= 0)
		{
			if(m_playerSpeed > GameConstants::HERO_MIN_SPEED + 100)
			{
				_createWindParticles();
			}

			m_hero->setPositionY(m_hero->getPositionY() - (m_hero->getPositionY() - touchY) * 0.1);

			if ((-(m_hero->getPositionY() - touchY) * 0.2) < 30 && (-(m_hero->getPositionY() - touchY) * 0.2) > -30) 
				m_hero->setRotation((m_hero->getPositionY() - touchY) * 0.2);

			if(m_hero->getRotation() > 30)
			{
				m_hero->setRotation(30);
			}
			else if(m_hero->getRotation() < -30)
			{
				m_hero->setRotation(-30);
			}

			if (m_hero->getPositionY() < 250 - m_hero->getContentSize().height)    
			{
				m_hero->setPositionY(250 - m_hero->getContentSize().height);
				m_hero->setRotation(0);
			}
			if (m_hero->getPositionY() > size.height - 100 - m_hero->getContentSize().height * 0.5)
			{
				m_hero->setPositionY(size.height - 100 - m_hero->getContentSize().height * 0.5);
				m_hero->setRotation(0);
			}
		}
		else
		{
			m_hero->setPositionY(m_hero->getPositionY() - (m_hero->getPositionY() - size.height / 2) * 0.1);

			if (m_hero->getPositionY() > size.height * 0.5) 
				m_hero->setRotation(m_hero->getRotation() - m_hitObstacle * 2);
			else 
				m_hero->setRotation(m_hero->getRotation() + m_hitObstacle * 2);
			--m_hitObstacle;
			m_cameraShake = m_hitObstacle;
			_shakeAnimation();
		}

		if (m_mushroomPower > 0) 
		{
			m_mushroomPower -= delta;
			m_particleMushroom->setPosition(m_hero->getPosition());
			if(m_mushroomPower <= 0)
			{
				m_particleMushroom->resetSystem();
				removeChild(m_particleMushroom, false);
			}
		}
		if (m_coffeePower > 0) 
		{
			m_coffeePower -= delta;
			m_particleCoffee->setPosition(ccp(m_hero->getPositionX() + 40, m_hero->getPositionY()));
			if(m_coffeePower <= 0)
			{
				m_particleCoffee->resetSystem();
				removeChild(m_particleCoffee, false);
			}
		}

		m_playerSpeed -= (m_playerSpeed - GameConstants::HERO_MIN_SPEED) * 0.01;
		bg->setSpeed(m_playerSpeed * delta);

		_initObstacle(delta);
		_animateObstacles(delta);

		_createFoodItems();
		_animateItems(delta);

		_animateEatParticles(delta);
		_animateWindParticles();

		m_distance += m_playerSpeed * delta * 0.1;
		m_scorePanel->setDistance(ceil(m_distance));
	}
	else if(m_gameState == GameConstants::GAME_STATE_OVER)
	{
		for(int i = m_foodItemArray->count() - 1; i >= 0 ; --i)
		{
			_disposeItem((Item*)m_foodItemArray->objectAtIndex(i));
		}

		for(int i = m_obstacleArray->count() - 1; i >= 0 ; --i)
		{
			_disposeObstacle((Obstacle*) m_obstacleArray->objectAtIndex(i));
		}

		for(int i = m_eatParticlesArray->count() - 1; i >= 0; --i)
		{
			_disposeEatParticle((Particle*) m_eatParticlesArray->objectAtIndex(i));
		}

		for(int i = m_winParticlesArray->count() - 1; i >= 0; --i)
		{
			_disposeWindParticle((Particle*) m_winParticlesArray->objectAtIndex(i));
		}

		if(m_particleCoffee->getParent() != NULL)
		{
			m_particleCoffee->resetSystem();
			removeChild(m_particleCoffee, false);
		}

		if(m_particleMushroom->getParent() != NULL)
		{
			m_particleMushroom->resetSystem();
			removeChild(m_particleMushroom, false);
		}

		m_hero->setRotation(m_hero->getRotation() - 30);

		if(m_hero->getPositionY() > - m_hero->getContentSize().height / 2)
		{
			m_playerSpeed -= m_playerSpeed * delta;
			m_hero->setPositionY(m_hero->getPositionY() - size.height * delta);
		}
		else
		{
			m_playerSpeed = 0;
			this->unscheduleUpdate();
			_showGameOver();
		}
		bg->setSpeed(m_playerSpeed * delta);
	}
}


void InGameScene::_createFoodItems()
{
	if(double(rand() * 1.0 / RAND_MAX) < 0.997)
	{
		if(double(rand() * 1.0 / RAND_MAX) > 0.9)
		{
			Item* item = (Item*) m_ItemPool->makeObject();
			item->setType(rand()%5 + 1);
			item->setScale(1.2f);

			Size size = Director::sharedDirector()->getVisibleSize();
			item->setPositionX(size.width + item->getContentSize().width);
			item->setPositionY(250 + (size.height - 350) * (double)(rand() * 1.0 / RAND_MAX) );
			addChild(item);

			m_foodItemArray->addObject(item);
		}
	}
	else
	{
		Item* item = (Item*) m_ItemPool->makeObject();
		item->setType(rand()%2 + 6);

		Size size = Director::sharedDirector()->getVisibleSize();
		item->setPositionX(size.width + item->getContentSize().width);
		item->setPositionY(250 + (size.height - 350) * (double)(rand() * 1.0 / RAND_MAX) );
		addChild(item);

		m_foodItemArray->addObject(item);
	}
}


void InGameScene::_animateItems(float delta)
{
	Item* item;
	for(int i = m_foodItemArray->count() - 1; i >= 0 ; i--)
	{
		item = (Item*) m_foodItemArray->objectAtIndex(i);
		if(m_mushroomPower > 0 && item->getType() <= GameConstants::ITEM_TYPE_5)
		{
			item->setPositionX(item->getPositionX() - (item->getPositionX() - m_hero->getPositionX()) * 0.2);
			item->setPositionY(item->getPositionY() - (item->getPositionY() - m_hero->getPositionY()) * 0.2);
		}
		else
		{
			item->setPositionX(item->getPositionX() - m_playerSpeed * delta);
		}

		if(item->getPositionX() < -item->getContentSize().width || m_gameState == GameConstants::GAME_STATE_OVER)
		{
			_disposeItem(item);
		}
		else
		{
			if(item->boundingBox().intersectsRect(m_hero->boundingBox()))
			{
				m_score += item->getType();
				m_scorePanel->setScore(m_score);

				if(item->getType() <= GameConstants::ITEM_TYPE_5)
				{
					SimpleAudioEngine::sharedEngine()->playEffect(EAT_EFFECT);
				}
				else if(item->getType() == GameConstants::ITEM_TYPE_COFFEE)
				{
					m_coffeePower = 5;
					SimpleAudioEngine::sharedEngine()->playEffect(COFFEE_EFFECT);

					if(m_particleCoffee->getParent() != NULL)
					{
						removeChild(m_particleCoffee, false);
					}

					m_particleCoffee->setPosition(ccp(m_hero->getPositionX() + 40, m_hero->getPositionY()));
					addChild(m_particleCoffee);
				}
				else if(item->getType() == GameConstants::ITEM_TYPE_MUSHROOM)
				{
					m_mushroomPower = 4;
					SimpleAudioEngine::sharedEngine()->playEffect(MUSHROOM_EFFECT);
					if(m_particleMushroom->getParent() != NULL)
					{
						removeChild(m_particleMushroom, false);
					}

					m_particleMushroom->setPosition(ccp(m_hero->getPositionX(), m_hero->getPositionY()));
					addChild(m_particleMushroom);
				}

				_disposeItem(item);

				_createEatParticles(item);
				continue;
			}
		}
	}
}


void InGameScene::_animateEatParticles(float delta)
{
	Particle* particle;
	for(int i = m_eatParticlesArray->count() - 1; i >= 0 ; i--)
	{
		particle = (Particle* )m_eatParticlesArray->objectAtIndex(i);

		particle->setScale(particle->getScale() - 0.03);

		particle->setPositionY(particle->getPositionY() - particle->speedY); 
		particle->speedY -= particle->speedY * 0.2;

		particle->setPositionX(particle->getPositionX() + particle->speedX);
		particle->speedX--; 

		particle->setRotation(particle->getRotation() + particle->spin);
		particle->spin *= 1.1; 

		if (particle->getScale() <= 0.02)
		{
			_disposeEatParticle(particle);
		}
	}
}

void InGameScene::onExit()
{
	removeChild(SoundButton::getInstance(), false);
	Layer::onExit();

	SimpleAudioEngine::sharedEngine()->end();
}

bool InGameScene::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	return true;
}

void InGameScene::onTouchMoved(Touch *pTouch, Event *pEvent)
{
	Point point = pTouch->getLocationInView();
	Point endPoint = Director::sharedDirector()->convertToGL(point);
	touchY = endPoint.y;
}

void InGameScene::onTouchEnded(Touch *pTouch, Event *pEvent)
{
	Point point = pTouch->getLocationInView();
	Point endPoint = Director::sharedDirector()->convertToGL(point);
	touchY = endPoint.y;
	//m_cameraShake = 30;
	//Game::getInstance()->switchScene(1);
}


void InGameScene::_createEatParticles(Node* item, int count  /*= 2*/ )
{
	while(count-- > 0)
	{
		Particle* particle = (Particle*) m_eatParticlesPool->makeObject();
		particle->setTypte(GameConstants::PARTICLE_TYPE_1);
		addChild(particle);

		particle->setPositionX(item->getPositionX() + rand() % 41 - 20);
		particle->setPositionY(item->getPositionY() - rand() % 41);

		particle->speedY = rand() % 11 - 5;
		particle->speedX = rand() % 3 + 1;

		particle->spin = rand() % 21 - 5;

		particle->setScale(rand() * 1.0 / RAND_MAX * 0.3 + 0.4);

		m_eatParticlesArray->addObject(particle);
	}
}


void InGameScene::_initObstacle(float delta)
{
	if(m_obstacleGapCount < GameConstants::OBSTACLE_GAP)
	{
		m_obstacleGapCount += m_playerSpeed * delta;
	}
	else if(m_obstacleGapCount != 0)
	{
		m_obstacleGapCount = 0;

		_createObstacle(rand() % 4 + 1, rand() % 1000 + 1000);
	}
}


void InGameScene::_createObstacle(int type, float distance)
{
	Size size = Director::sharedDirector()->getVisibleSize();
	Obstacle* obstable = (Obstacle*)m_obstaclePool->makeObject();
	obstable->setType(type);
	obstable->distance = distance;
	obstable->setPositionX(size.width + 60);
	if(type <= GameConstants::OBSTACLE_TYPE_3)
	{
		if(rand() % 2 == 1)
		{
			obstable->setPositionY(size.height - 150);
		}
		else
		{
			obstable->setPositionY(250);
		}
	}
	else
	{
		obstable->setPositionY(250 + (size.height - 350) * (double)(rand() * 1.0 / RAND_MAX) );
	}
	obstable->speed = GameConstants::OBSTACLE_SPEED;
	obstable->setShowLookOut(true);
	m_obstacleArray->addObject(obstable);
	addChild(obstable);
}


void InGameScene::_animateObstacles(float delta)
{
	Obstacle* obstacle;
	for(int i = m_obstacleArray->count() - 1; i >= 0; --i)
	{
		obstacle = (Obstacle*) m_obstacleArray->objectAtIndex(i);
		if(obstacle->distance > 0)
		{
			obstacle->distance -= m_playerSpeed * delta;
		}
		else
		{
			if(obstacle->getShowLookOut())
			{
				obstacle->setShowLookOut(false);
			}

			obstacle->setPositionX(obstacle->getPositionX() - (m_playerSpeed + obstacle->speed) * delta);

			if(!obstacle->getAlreadyHit() && m_hero->boundingBox().intersectsRect(obstacle->boundingBox()))
			{
				obstacle->setAlreadyHit(true);
				SimpleAudioEngine::sharedEngine()->playEffect(HIT_EFFECT);
				if(m_coffeePower > 0)
				{
					obstacle->setRotation(100);
					m_playerSpeed *= 0.8;
				}
				else
				{
					obstacle->setRotation(70);
					SimpleAudioEngine::sharedEngine()->playEffect(HURT_EFFECT);
					m_playerSpeed *= 0.5;
					m_hitObstacle = 30;

					--m_lives;
					if(m_lives <= 0)
					{
						m_lives = 0;
						m_gameState = GameConstants::GAME_STATE_OVER;
					}
					m_scorePanel->setLives(m_lives);
				}
			}

			if(obstacle->getPositionX() < - obstacle->getContentSize().width || m_gameState == GameConstants::GAME_STATE_OVER)
			{
				_disposeObstacle(obstacle);

			}
		}
	}
}


void InGameScene::_createWindParticles()
{
	Size size = Director::sharedDirector()->getVisibleSize();

	Particle* wind = (Particle*) m_windParticlesPool->makeObject();
	wind->setTypte(GameConstants::PARTICLE_TYPE_2);
	addChild(wind);

	wind->setPositionX(size.width);
	wind->setPositionY(rand() % int(size.height));

	wind->setScale(rand() * 1.0 / RAND_MAX * 0.5 + 0.5);

	m_winParticlesArray->addObject(wind);
}


void InGameScene::_animateWindParticles()
{
	Particle* wind;
	for(int i = m_winParticlesArray->count() - 1; i >= 0 ; --i)
	{
		wind = (Particle*) m_winParticlesArray->objectAtIndex(i);

		wind->setPositionX(wind->getPositionX() - wind->getScale() * 100.0);

		if(wind->getPositionX() < - wind->getContentSize().width || m_gameState == GameConstants::GAME_STATE_OVER)
		{
			_disposeWindParticle(wind);
		}
	}
}

void InGameScene::_shakeAnimation()
{
	if(m_cameraShake > 0)
	{
		this->setPositionX(int(rand() * 1.0 /RAND_MAX * m_cameraShake - m_cameraShake * 0.5)); 
		char s[16];
		sprintf(s, "%f", this->getPositionX());

		this->setPositionY(int(rand() * 1.0 /RAND_MAX * m_cameraShake - m_cameraShake * 0.5)); 
		sprintf(s, "%f", this->getPositionY());
	}
	else if (this->getPositionX() != 0) 
	{
		this->setPositionX(0);
		this->setPositionY(0);
	}
}

void InGameScene::_disposeItem( Item* item ) 
{
	removeChild(item, false);
	m_foodItemArray->removeObject(item, false);
	m_ItemPool->passivateObject((PoolObject*)item);
}


void InGameScene::_disposeEatParticle( Particle* particle )
{
	removeChild(particle, false);
	m_eatParticlesArray->removeObject(particle, false);
	m_eatParticlesPool->passivateObject((PoolObject*)particle);
}


void InGameScene::_disposeObstacle( Obstacle* obstacle ) 
{
	removeChild(obstacle, false);
	m_obstacleArray->removeObject(obstacle,false);
	m_obstaclePool->passivateObject((PoolObject*)obstacle);
}

void InGameScene::_disposeWindParticle( Particle* wind ) 
{
	removeChild(wind, false);
	m_winParticlesArray->removeObject(wind,false);
	m_windParticlesPool->passivateObject((PoolObject*)wind);
}


void InGameScene::_showGameOver()
{
	m_gameOverContainer->setResult(m_score, m_distance);
	m_gameOverContainer->setVisible(true);
}