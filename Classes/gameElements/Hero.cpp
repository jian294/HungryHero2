#include "Hero.h"


Hero::Hero(void)
{
}


Hero::~Hero(void)
{
}

Hero* Hero::heroArt = NULL;

Hero* Hero::getInstance()
{
	if(heroArt == NULL)
	{
		heroArt = Hero::create();
	}
	return heroArt;
}

CCAnimate* Hero::_getAction()
{
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	CCAnimation* animation = CCAnimation::create();
	for( int i=1;i<=20;i++)
	{
		char szName[20] = {0};
		sprintf(szName, "fly_00%02d", i);
		CCSpriteFrame* frame = cache->spriteFrameByName(szName);
		animation->addSpriteFrame(frame);
	}

	animation->setDelayPerUnit(0.06f);

	CCAnimate* action = CCAnimate::create(animation);
	return action;
}

void Hero::onEnter()
{
	CCSprite::onEnter();

	heroArt->runAction(CCRepeatForever::create(_getAction()));
}
