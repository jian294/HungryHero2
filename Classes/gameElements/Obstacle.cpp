#include "Obstacle.h"
#include "GameConstants.h"

Obstacle::Obstacle(void)
{
	m_lookOutAnimation = NULL;
	m_obstacleCrashImage = NULL;
	m_obstacleImage = NULL;

	m_bAlreadyHit = false;
	m_bShowLookOut = true;
}


Obstacle::~Obstacle(void)
{
	removeChild(m_lookOutAnimation, true);
	m_lookOutAnimation->release();
	m_lookOutAnimation = NULL;

	removeChild(m_obstacleCrashImage, true);
	m_obstacleCrashImage->release();
	m_obstacleCrashImage = NULL;

	removeChild(m_obstacleImage, true);
	m_obstacleImage->release();
	m_obstacleImage = NULL;
}

void Obstacle::setType(int type)
{
	m_type = type;

	_createObstacleArt();

	_createObstacleCrashArt();

	_createLookOutAnimation();
}

void Obstacle::_createObstacleArt()
{
	if(m_obstacleImage == NULL)
	{
		m_obstacleImage = CCSprite::create();
		//m_obstacleImage->setAnchorPoint(ccp(0,0));
		addChild(m_obstacleImage);
		m_obstacleImage->retain();
	}

	if (m_type == GameConstants::OBSTACLE_TYPE_4)
	{
		m_obstacleImage->runAction(CCRepeatForever::create(_getObstacleAction()));
	}
	else
	{
		m_obstacleImage->stopAllActions();

		char str[16];
		sprintf(str, "obstacle%d", m_type);
		m_obstacleImage->setSpriteFrame(str);
	}
	m_obstacleImage->setVisible(true);
}

void Obstacle::_createObstacleCrashArt()
{
	if(m_obstacleCrashImage == NULL)
	{
		m_obstacleCrashImage = CCSprite::create();
		//m_obstacleCrashImage->setAnchorPoint(ccp(0,0));
		addChild(m_obstacleCrashImage);
		m_obstacleCrashImage->retain();
	}
	
	char str[16];
	sprintf(str, "obstacle%d_crash", m_type);
	m_obstacleCrashImage->setSpriteFrame(str);
	m_obstacleCrashImage->setVisible(false);
}

CCAnimate* Obstacle::_getObstacleAction()
{
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	CCAnimation* animation = CCAnimation::create();
	for( int i=1;i<=2;i++)
	{
		char szName[20] = {0};
		sprintf(szName, "obstacle%d_00%02d", m_type, i);
		CCSpriteFrame* frame = cache->spriteFrameByName(szName);
		animation->addSpriteFrame(frame);
	}

	animation->setDelayPerUnit(0.06f);

	CCAnimate* action = CCAnimate::create(animation);
	return action;
}


CCAnimate* Obstacle::_getLookOutAction()
{
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	CCAnimation* animation = CCAnimation::create();
	for( int i=1;i<=4;i++)
	{
		char szName[20] = {0};
		sprintf(szName, "watchOut_00%02d", i);
		CCSpriteFrame* frame = cache->spriteFrameByName(szName);
		animation->addSpriteFrame(frame);
	}

	animation->setDelayPerUnit(0.10f);

	CCAnimate* action = CCAnimate::create(animation);
	return action;
}


void Obstacle::_createLookOutAnimation()
{
	if(m_lookOutAnimation == NULL)
	{
		m_lookOutAnimation = CCSprite::create();
		//m_lookOutAnimation->setAnchorPoint(ccp(0,0));
		addChild(m_lookOutAnimation);
		m_lookOutAnimation->retain();
	}
	m_lookOutAnimation->setSpriteFrame("watchOut_0001");
	m_lookOutAnimation->runAction(CCRepeatForever::create(_getLookOutAction()));
	m_lookOutAnimation->setPositionX(-m_lookOutAnimation->getContentSize().width);
	//m_lookOutAnimation->setVisible(false);
}


void Obstacle::setAlreadyHit(bool val)
{
	m_bAlreadyHit = val;
	if(m_bAlreadyHit)
	{
		m_obstacleImage->stopAllActions();
		m_obstacleImage->setVisible(false);
		m_obstacleCrashImage->setVisible(true);
	}
}


void Obstacle::setShowLookOut(bool val)
{
	m_bShowLookOut = val;
	if(m_bShowLookOut)
	{
		m_lookOutAnimation->setVisible(true);
		m_obstacleImage->setVisible(false);
	}
	else
	{
		m_lookOutAnimation->stopAllActions();
		m_lookOutAnimation->setVisible(false);
		m_obstacleImage->setVisible(true);
	}
}


void Obstacle::reset()
{
	this->setAlreadyHit(false);
	this->setShowLookOut(true);
	this->setRotation(0);
}


void Obstacle::dispose()
{
	this->release();
}