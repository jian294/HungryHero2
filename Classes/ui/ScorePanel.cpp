#include "ScorePanel.h"


ScorePanel::ScorePanel(void)
{
}


ScorePanel::~ScorePanel(void)
{
}

bool ScorePanel::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	CCSize size = CCDirector::sharedDirector()->getVisibleSize();

	m_livesLable = CCLabelBMFont::create("L I V E S","fonts/fontScoreLabel.fnt");
	m_livesLable->setAnchorPoint(ccp(0,1));
	m_livesLable->setPosition(250, -10);
	m_livesLable->setScale(1.3f);
	addChild(m_livesLable);

	m_livesText = CCLabelBMFont::create("5","fonts/fontScoreValue.fnt");
	m_livesText->setAnchorPoint(ccp(0,1));
	m_livesText->setPosition(265, -40);
	m_livesText->setScale(1.3f);
	addChild(m_livesText);
	
	m_foodScoreLabel = CCLabelBMFont::create("S C O R E","fonts/fontScoreLabel.fnt");
	m_foodScoreLabel->setAnchorPoint(ccp(0,1));
	m_foodScoreLabel->setPosition(size.width - 350, -10);
	m_foodScoreLabel->setScale(1.3f);
	addChild(m_foodScoreLabel);

	m_foodScoreText = CCLabelBMFont::create("100","fonts/fontScoreValue.fnt");
	m_foodScoreText->setAnchorPoint(ccp(1,1));
	m_foodScoreText->setPosition(size.width - 270, -40);
	m_foodScoreText->setScale(1.3f);
	addChild(m_foodScoreText);
	
	m_distanceLabel = CCLabelBMFont::create("D I S T A N C E","fonts/fontScoreLabel.fnt");
	m_distanceLabel->setAnchorPoint(ccp(1,1));
	m_distanceLabel->setPosition(size.width - 10, -10);
	m_distanceLabel->setScale(1.3f);
	addChild(m_distanceLabel);

	m_distanceText = CCLabelBMFont::create("100","fonts/fontScoreValue.fnt");
	m_distanceText->setAnchorPoint(ccp(1,1));
	m_distanceText->setPosition(size.width - 10, -40);
	m_distanceText->setScale(1.3f);
	addChild(m_distanceText);

	return true;
}

void ScorePanel::setLives(int live)
{
	char str[10];
	sprintf(str, "%d", live);
	m_livesText->setString(str);
}

void ScorePanel::setScore(int score)
{
	char str[16];
	sprintf(str, "%d", score);
	m_foodScoreText->setString(str);
}

void ScorePanel::setDistance(int distance)
{
	char str[16];
	sprintf(str, "%d", distance);
	m_distanceText->setString(str);
}