#pragma once
#include "cocos2d.h"
#include <stdlib.h> 
#include <stdio.h> 
USING_NS_CC;

class BgLayer : public CCSprite
{
private:
	int m_layer;
	CCSprite* image1;
	CCSprite* image2;

public:
	BgLayer(int);
	~BgLayer(void);
	bool init();
	float parallaxDepth;
};

