#include "ObjectPool.h"
#include "GameConstants.h"
#include "Item.h"
#include "Particle.h"
#include "Obstacle.h"
using namespace std;

ObjectPool::ObjectPool(int type, int max)
{
	m_type = type;
	m_max = max;
}


ObjectPool::~ObjectPool(void)
{
}

PoolObject* ObjectPool::makeObject()
{
	if(m_list.size() > 0)
	{
		PoolObject* object = m_list[m_list.size() - 1];
		m_list.pop_back();
		return object;
	}
	PoolObject* obj;

	switch(m_type)
	{
		case GameConstants::OBJECT_TYPE_ITEM:
		{
			Item* item = Item::create();
			item->retain();
			obj = (PoolObject*) item;
			break;
		}
		case GameConstants::OBJECT_TYPE_PARTICLE:
		{
			Particle* particle = Particle::create();
			particle->retain();
			obj = (PoolObject*) particle;
			break;
		}
		case GameConstants::OBJECT_TYPE_OBSTACLE:
		{
			Obstacle* obstacle = Obstacle::create();
			obstacle->retain();
			obj = (PoolObject*) obstacle;
			break;
		}
	}
	
	return obj;
}

void ObjectPool::passivateObject(PoolObject* obj)
{
	bool isIn = false;
	for(vector<PoolObject*>::iterator it = m_list.begin(); it != m_list.end(); it++)
	{
		if(*it == obj)
		{
			isIn = true;
			break;
		}
	}

	if(m_list.size() >= m_max)
	{
		if(!isIn)
		{
			obj->dispose();
			obj = NULL;
		}
	}
	else
	{
		obj->reset();
		if(!isIn)
		{
			m_list.push_back(obj);
		}
	}
}
