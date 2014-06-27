#include "BgLayer.h"


BgLayer::BgLayer(int _layer)
{
	m_layer = _layer;

	init();
}


BgLayer::~BgLayer(void)
{
}


bool BgLayer::init()
{
	if(CCSprite::init())
	{
		setAnchorPoint(ccp(0,0));
		if(m_layer == 1)
		{
			image1 = CCSprite::create("graphics/BgLayer1.jpg");
			image2 = CCSprite::create("graphics/BgLayer1.jpg");
		}
		else
		{
			char str[10];
			sprintf(str, "bgLayer%d", m_layer);
			
			image1 = CCSprite::createWithSpriteFrameName(str);
			image2 = CCSprite::createWithSpriteFrameName(str);
		}
		
		image1->setAnchorPoint(ccp(0,0));
		image2->setAnchorPoint(ccp(0,0));

		addChild(image1);
		addChild(image2);

		image2->setPosition(ccp(image1->getContentSize().width,0));

		return true;
	}
	return false;
}