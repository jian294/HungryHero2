#pragma once
#include "cocos2d.h"
USING_NS_CC;

class Hero : public Sprite
{
public:
	Hero(void);
	~Hero(void);
	CREATE_FUNC(Hero);
	static Hero* getInstance();
	void onEnter();
private:
	static Hero* heroArt;
	static Animate* _getAction();
};

