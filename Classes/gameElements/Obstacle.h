#ifndef _OBSTACLE_HEAD
#define _OBSTACLE_HEAD
#include "cocos2d.h"
#include "PoolObject.h"
USING_NS_CC;

class Obstacle : public CCSprite, PoolObject
{
public:
	Obstacle(void);
	~Obstacle(void);

	void reset();
	void dispose();

	float speed;
	int distance;

	int getType() const { return m_type; }
	void setType(int);

	bool getAlreadyHit() const { return m_bAlreadyHit; }
	void setAlreadyHit(bool val);

	bool getShowLookOut() const { return m_bShowLookOut; }
	void setShowLookOut(bool val);

	CREATE_FUNC(Obstacle);
private:
	int m_type;
	bool m_bAlreadyHit;
	bool m_bShowLookOut;
	
	CCSprite* m_obstacleImage;
	CCSprite* m_obstacleCrashImage;
	CCSprite* m_lookOutAnimation;

	void _createObstacleArt();
	void _createObstacleCrashArt();
	void _createLookOutAnimation();

	CCAnimate* _getObstacleAction();
	CCAnimate* _getLookOutAction();
};

#endif