#include "GameBackground.h"
#include <math.h>

GameBackground::GameBackground(void)
{
	m_speed = 0;
}


GameBackground::~GameBackground(void)
{
}

bool GameBackground::init()
{
	if(CCSprite::init())
	{
		m_bgLayer1 = new BgLayer(1);
		m_bgLayer1->parallaxDepth = 0.02;
		addChild(m_bgLayer1);

		m_bgLayer2 = new BgLayer(2);
		m_bgLayer2->parallaxDepth = 0.2;
		addChild(m_bgLayer2);

		m_bgLayer3 = new BgLayer(3);
		m_bgLayer3->parallaxDepth = 0.5;
		addChild(m_bgLayer3);

		m_bgLayer4 = new BgLayer(4);
		m_bgLayer4->parallaxDepth = 1;
		addChild(m_bgLayer4);

		return true;
	}
	return false;
}

void GameBackground::onEnter()
{
	CCSprite::onEnter();
	this->scheduleUpdate();
}

void GameBackground::update(float delta)
{
	_updateBgLayerPosition(m_bgLayer1);
	_updateBgLayerPosition(m_bgLayer2);
	_updateBgLayerPosition(m_bgLayer3);
	_updateBgLayerPosition(m_bgLayer4);

}

void GameBackground::_updateBgLayerPosition(BgLayer* layer)
{
	auto director = Director::getInstance();
	layer->setPositionX(layer->getPositionX() - ceil(m_speed * layer->parallaxDepth));
	//CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCSize size = director->getOpenGLView()->getDesignResolutionSize();
	if(layer->getPositionX() > 0)
	{
		layer->setPositionX(layer->getPositionX() - size.width);
	}
	if(layer->getPositionX() < -size.width)
	{
		layer->setPositionX(0);
	}
}


void GameBackground::setSpeed(float speed)
{
	m_speed = speed;
}
