#pragma once
#include "cocos2d.h"
#include "BgLayer.h"
USING_NS_CC;

class GameBackground : public CCSprite
{
private:
	BgLayer* m_bgLayer1;
	BgLayer* m_bgLayer2;
	BgLayer* m_bgLayer3;
	BgLayer* m_bgLayer4;

	void _updateBgLayerPosition(BgLayer* );
	float m_speed;
public:
	GameBackground(void);
	~GameBackground(void);
	CREATE_FUNC(GameBackground);
	bool init();
	void update(float delta);
	void onEnter();
	void setSpeed(float speed);
};

