#ifndef _GAMEOVERCONTAINER_HEAD
#define _GAMEOVERCONTAINER_HEAD
#include "cocos2d.h"
USING_NS_CC;

class GameOverContainer : public CCLayer
{
public:
	GameOverContainer(void);
	~GameOverContainer(void);

	CREATE_FUNC(GameOverContainer);
	bool init();
	void setResult(int score, int distance);
private:
	CCLabelBMFont* m_messageText;
	CCLayerColor* bg;

	CCLabelBMFont* m_distanceText;
	CCLabelBMFont* m_scoreText;

	CCMenuItemSprite* m_playAgainItem;
	CCMenuItemSprite* m_mainItem;

	void _onPlayAgainBtn(Ref* sender);
	void _onMainBtn(Ref* sender);
};

#endif