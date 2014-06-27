#ifndef _SCOREPANEL_HEAD
#define _SCOREPANEL_HEAD
#include "cocos2d.h"
USING_NS_CC;

class ScorePanel : public CCLayer
{
public:
	ScorePanel(void);
	~ScorePanel(void);
	CREATE_FUNC(ScorePanel);
	bool init();

	void setLives(int live);

	void setScore(int score);

	void setDistance(int distance);
private:
	CCLabelBMFont* m_livesLable;
	CCLabelBMFont* m_livesText;


	CCLabelBMFont* m_distanceLabel;
	CCLabelBMFont* m_distanceText;


	CCLabelBMFont* m_foodScoreLabel;
	CCLabelBMFont* m_foodScoreText;
};

#endif