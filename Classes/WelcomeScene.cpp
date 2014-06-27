#include "WelcomeScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

#define BGWELCOME_MUSIC        "sounds/bgWelcome.mp3"
#define COFFEE_EFFECT "sounds/coffee.mp3"
#define MUSHROOM_EFFECT "sounds/mushroom.mp3"

WelcomeScene::WelcomeScene(void)
{
	
}


WelcomeScene::~WelcomeScene(void)
{
}

CCScene* WelcomeScene::staScene = NULL;

bool WelcomeScene::init()
{
	if(CCLayer::init())
	{
		setTouchEnabled(true);

		CCSize size = CCDirector::sharedDirector()->getWinSize();

		CCSprite* _back = CCSprite::create("graphics/bgWelcome.jpg");
		this->addChild(_back);
		_back->setPosition(ccp(size.width/2, size.height/2));

		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("graphics/mySpritesheet.plist");
		hero = CCSprite::createWithSpriteFrameName("welcome_hero");
		this->addChild(hero);

		CCSprite* title = CCSprite::createWithSpriteFrameName("welcome_title");
		this->addChild(title);
		title->setPosition(ccp(725,580));

		CCSprite* playbtn = CCSprite::createWithSpriteFrameName("welcome_playButton");
		CCSprite* playbtnSelected = CCSprite::createWithSpriteFrameName("welcome_playButton");
		playbtnSelected->setScale(0.9f);
		playItem = CCMenuItemSprite::create(playbtn,playbtnSelected,CC_CALLBACK_1(WelcomeScene::_onPlayBtn, this));

		CCSprite* aboutBtn = CCSprite::createWithSpriteFrameName("welcome_aboutButton");
		CCSprite* aboutBtnSelected = CCSprite::createWithSpriteFrameName("welcome_aboutButton");
		aboutBtnSelected->setScale(0.9f);
		aboutItem = CCMenuItemSprite::create(aboutBtn,aboutBtnSelected,CC_CALLBACK_1(WelcomeScene::_onAboutBtn, this));
		aboutItem->setPosition(ccp(-150, -100));

		CCSprite* backBtn = CCSprite::createWithSpriteFrameName("about_backButton");
		CCSprite* backBtnSelected = CCSprite::createWithSpriteFrameName("about_backButton");
		backBtnSelected->setScale(0.9f);
		backItem = CCMenuItemSprite::create(backBtn,backBtnSelected,CC_CALLBACK_1(WelcomeScene::_onBackBtn, this));
		backItem->setPosition(ccp(100, -50));
		backItem->setVisible(false);

		CCMenu* menu = CCMenu::create(playItem,aboutItem,backItem, NULL);
		addChild(menu, 1, 1);
		menu->setPosition(ccp(size.width/3*2, size.height/2));

		labelAbout = CCLabelBMFont::create(
			"Hungry Hero is a simple game using Cocos2dx by Kanefan.\nhttp://kanefan.duapp.com\n    The concept is very simple. The hero is pretty much always hungry and you need to feed him with food. You score when your Hero eats food. \n    There are different obstacles that fly in with a \"Look out!\" caution before they appear. Avoid them at all costs. You only have 5 lives. Try to score as much as possible and also try to travel the longest distance."
			 , "fonts/markerFelt.fnt", 600, kCCTextAlignmentLeft);
		labelAbout->setAnchorPoint(ccp(0,1));
		addChild(labelAbout);
		//labelAbout->setScale(0.5f);
		labelAbout->setPosition(ccp(50, size.height - 300));
		labelAbout->setVisible(false);

		SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(BGWELCOME_MUSIC);
		SimpleAudioEngine::sharedEngine()->preloadEffect(COFFEE_EFFECT);
		SimpleAudioEngine::sharedEngine()->preloadEffect(MUSHROOM_EFFECT);

		return true;
	}
	return false;
}

void WelcomeScene::_onPlayBtn(Ref* sender)
{
	SimpleAudioEngine::sharedEngine()->playEffect(COFFEE_EFFECT);
	Game::getInstance()->switchScene(2);
}

void WelcomeScene::_onAboutBtn(Ref* sender)
{
	SimpleAudioEngine::sharedEngine()->playEffect(MUSHROOM_EFFECT);
	hero->setVisible(false);
	playItem->setVisible(false);
	aboutItem->setVisible(false);
	labelAbout->setVisible(true);
	backItem->setVisible(true);
}


void WelcomeScene::_onBackBtn(Ref* sender)
{
	SimpleAudioEngine::sharedEngine()->playEffect(COFFEE_EFFECT);
	hero->setVisible(true);
	playItem->setVisible(true);
	aboutItem->setVisible(true);
	labelAbout->setVisible(false);
	backItem->setVisible(false);
}

void WelcomeScene::onEnter()
{
	CCLayer::onEnter();
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic(BGWELCOME_MUSIC, true);

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	SoundButton* soundBtn = SoundButton::getInstance();
	addChild(soundBtn);
	soundBtn->setPosition(ccp(40, size.height - 40));

	hero->setPosition(ccp(-hero->getContentSize().width / 2, 400));

	CCMoveBy* moveBy = CCMoveBy::create(1, ccp(hero->getContentSize().width + 80,0));

	ccBezierConfig bezierHeroConfig;
	bezierHeroConfig.controlPoint_1 = ccp(0, 100);
	bezierHeroConfig.controlPoint_2 = ccp(0, -100);
	bezierHeroConfig.endPosition = ccp(0, 0);
	CCBezierBy* bezierHero = CCBezierBy::create(3, bezierHeroConfig);
	CCRepeatForever* rep = CCRepeatForever::create(bezierHero);

	CCMenu* menu = (CCMenu*) getChildByTag(1);
	ccBezierConfig bezier;
	float targetX = menu->getPositionX();
	bezier.controlPoint_1 = ccp(0, 50);
	bezier.controlPoint_2 = ccp(0, -50);
	bezier.endPosition = ccp(0, 0);
	CCBezierBy* bezierMenu = CCBezierBy::create(3, bezier);
	CCRepeatForever* repMenu = CCRepeatForever::create(bezierMenu);
	menu->runAction(repMenu);

	hero->runAction(moveBy);
	hero->runAction(rep);
}

void WelcomeScene::onExit()
{
	removeChild(SoundButton::getInstance(),false);
	CCLayer::onExit();

	SimpleAudioEngine::sharedEngine()->end();
}

CCScene* WelcomeScene::scene()
{
	if(staScene == NULL)
	{
		staScene = CCScene::create();
		
		WelcomeScene* layer = (WelcomeScene*) WelcomeScene::create();

		staScene->addChild(layer);
	}
	return staScene;
}