#pragma once
#include "cocos2d.h"
USING_NS_CC;

class SoundButton : public Sprite
{
private:
	static SoundButton* soundBtn;
	static Animate* _getAction();
	bool _isTouchInside( Touch* touch );
	bool _isMute;
	void _changeMute();
	void _updateMute();

public:
	SoundButton(void);
	~SoundButton(void);
	static SoundButton* getInstance();
	bool onTouchBegan(Touch *pTouch, Event *pEvent);
	void onTouchEnded( Touch *pTouch, Event *pEvent );
	CREATE_FUNC(SoundButton);
	void onEnter();
	void onExit();
};

