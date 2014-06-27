#include "GameOverContainer.h"
#include "SimpleAudioEngine.h"
#include "Game.h"
#include "InGameScene.h"
using namespace CocosDenshion;

#define COFFEE_EFFECT "sounds/coffee.mp3"
#define MUSHROOM_EFFECT "sounds/mushroom.mp3"

GameOverContainer::GameOverContainer(void)
{
}


GameOverContainer::~GameOverContainer(void)
{
}

bool GameOverContainer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	CCSize size = CCDirector::sharedDirector()->getVisibleSize();

	CCSize boxSize = CCSizeMake(size.width, size.height);
	bg = CCLayerColor::create(ccc4(0,0,0,200));
	bg->setAnchorPoint(ccp(0.5,0.5));
	bg->setContentSize( boxSize );
	bg->ignoreAnchorPointForPosition(false);
	bg->setPosition(ccp(size.width/2, size.height/2));
	this->addChild(bg);

	m_messageText = CCLabelBMFont::create("HERO WAS KILLED!","fonts/fontScoreValue.fnt");
	m_messageText->setPosition(size.width/2, size.height/4*3);
	m_messageText->setScale(1.3f);
	m_messageText->setColor(ccc3(0xf3, 0xe7, 0x5f));
	addChild(m_messageText);

	m_distanceText = CCLabelBMFont::create("DISTANCE TRAVELLED: 0000000","fonts/fontScoreLabel.fnt");
	m_distanceText->setPosition(size.width/2, size.height/2);
	m_distanceText->setScale(1.3f);
	addChild(m_distanceText);

	m_scoreText = CCLabelBMFont::create("SCORE: 0000000","fonts/fontScoreLabel.fnt");
	m_scoreText->setPosition(size.width/2, size.height/2 - 40);
	m_scoreText->setScale(1.3f);
	addChild(m_scoreText);

	CCSprite* playbtn = CCSprite::createWithSpriteFrameName("gameOver_playAgainButton");
	CCSprite* playbtnSelected = CCSprite::createWithSpriteFrameName("gameOver_playAgainButton");
	playbtnSelected->setScale(0.9f);
	m_playAgainItem = CCMenuItemSprite::create(playbtn,playbtnSelected,CC_CALLBACK_1(GameOverContainer::_onPlayAgainBtn, this));
	m_playAgainItem->setPosition(-100,0);

	CCSprite* mainBtn = CCSprite::createWithSpriteFrameName("gameOver_mainButton");
	CCSprite* mainBtnSelected = CCSprite::createWithSpriteFrameName("gameOver_mainButton");
	mainBtnSelected->setScale(0.9f);
	m_mainItem = CCMenuItemSprite::create(mainBtn,mainBtnSelected,CC_CALLBACK_1(GameOverContainer::_onMainBtn, this));
	m_mainItem->setPosition(ccp(100, 0));

	CCMenu* menu = CCMenu::create(m_playAgainItem,m_mainItem,NULL);
	addChild(menu, 1, 1);
	menu->setPosition(ccp(size.width/2, size.height/4));

	return true;
}

void GameOverContainer::_onPlayAgainBtn(Ref* sender)
{
	SimpleAudioEngine::sharedEngine()->playEffect(COFFEE_EFFECT);
	InGameScene::getInstance()->startGame();
}

void GameOverContainer::_onMainBtn(Ref* sender)
{
	SimpleAudioEngine::sharedEngine()->playEffect(MUSHROOM_EFFECT);
	Game::getInstance()->switchScene(1);
}


void GameOverContainer::setResult(int score, int distance)
{
	char s[50];
	sprintf(s, "DISTANCE TRAVELLED: %d", distance);
	m_distanceText->setString(s);

	sprintf(s, "SCORE: %d", score);
	m_scoreText->setString(s);
}
