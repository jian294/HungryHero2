#ifndef _PARTICLE_HEAD
#define _PARTICLE_HEAD
#include "cocos2d.h"
#include "PoolObject.h"
USING_NS_CC;

class Particle : public CCSprite, PoolObject
{
public:
	Particle(void);
	~Particle(void);
	void setTypte(int);
	int getType(){return m_type;};
	float speedX;
	float speedY;
	float spin;
	CREATE_FUNC(Particle);
private:
	int m_type;
	CCSprite* m_particleImage;
	void reset();
	void dispose();
};

#endif