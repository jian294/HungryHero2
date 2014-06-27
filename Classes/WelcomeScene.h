#ifndef _WELCOME_HEAD
#define _WELCOME_HEAD

#include "cocos2d.h"
#include "SoundButton.h"
#include "Game.h"
USING_NS_CC;

class WelcomeScene : public CCLayer
{
private:
	static CCScene* staScene;
	void _onPlayBtn(Ref* sender);
	void _onAboutBtn(Ref* sender);
	void _onBackBtn(Ref* sender);
	CCSprite* hero;
	CCMenuItemSprite* playItem;
	CCMenuItemSprite* aboutItem;
	CCMenuItemSprite* backItem;
	CCLabelBMFont * labelAbout;
public:
	WelcomeScene(void);
	~WelcomeScene(void);
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

	static CCScene* scene();
	CREATE_FUNC(WelcomeScene);
};

#endif