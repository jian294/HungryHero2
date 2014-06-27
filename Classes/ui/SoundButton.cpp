#include "SoundButton.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

SoundButton* SoundButton::soundBtn = NULL;

SoundButton::SoundButton(void)
{
	_isMute = false;

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(SoundButton::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(SoundButton::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}


SoundButton::~SoundButton(void)
{
}

SoundButton* SoundButton::getInstance()
{
	if(soundBtn == NULL)
	{
		soundBtn = SoundButton::create();
		soundBtn->retain();
	}
	return soundBtn;
}

Animate* SoundButton::_getAction()
{
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	Animation* animation = Animation::create();
	for( int i=0;i<3;i++)
	{
		char szName[20] = {0};
		sprintf(szName, "soundOn00%02d", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(szName);
		animation->addSpriteFrame(frame);
	}

	animation->setDelayPerUnit(0.4f);
	animation->setRestoreOriginalFrame(true);

	Animate* action = Animate::create(animation);
	return action;
}


void SoundButton::onEnter()
{
	Sprite::onEnter();
	
	//CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128/*priority=??*/, true);
	_updateMute();
}

void SoundButton::onExit()
{
	//CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	Sprite::onExit();
}


bool SoundButton::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	return _isTouchInside(pTouch);
}

void SoundButton::onTouchEnded(Touch *pTouch, Event *pEvent )
{
	if(_isTouchInside(pTouch))
	{
		_changeMute();
	}
	
}

bool SoundButton::_isTouchInside( Touch* touch )
{
	Point touchLocation = touch->getLocation(); // ·µ»ØGL×ø±ê
	Point localPos = convertToNodeSpace(touchLocation);
	Rect rc = this->getTextureRect();
	rc.origin = Vec2::ZERO;
	bool isTouched = rc.containsPoint(localPos);

	return isTouched;
}


void SoundButton::_changeMute()
{
	_isMute = !_isMute;
	_updateMute();
}


void SoundButton::_updateMute()
{
	if(_isMute)
	{
		soundBtn->stopAllActions();
		soundBtn->initWithSpriteFrameName("soundOff");
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0);
		SimpleAudioEngine::getInstance()->setEffectsVolume(0);

	}
	else
	{
		soundBtn->runAction(RepeatForever::create(_getAction()));
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0f);
		SimpleAudioEngine::getInstance()->setEffectsVolume(1.0f);
	}
}