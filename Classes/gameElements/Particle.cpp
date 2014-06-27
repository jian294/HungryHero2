#include "Particle.h"
#include "GameConstants.h"

Particle::Particle(void)
{
	m_particleImage = NULL;
}


Particle::~Particle(void)
{
	removeChild(m_particleImage, true);
	m_particleImage->release();
	m_particleImage = NULL;
}


void Particle::setTypte(int type)
{
	if(m_particleImage == NULL)
	{
		m_particleImage = CCSprite::create();
		addChild(m_particleImage);
		m_particleImage->retain();
	}
	if(m_type != type)
	{
		switch(type)
		{
		case GameConstants::PARTICLE_TYPE_1:
			m_particleImage->setSpriteFrame("particleEat");
			break;
		case GameConstants::PARTICLE_TYPE_2:
			m_particleImage->setSpriteFrame("particleWindForce");
			break;
		}
	}
}

void Particle::reset()
{
	this->setScale(1.0f);
	this->setRotation(0);
}

void Particle::dispose()
{
	this->release();
}