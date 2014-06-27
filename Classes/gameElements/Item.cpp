#include "Item.h"


Item::Item(void)
{
	m_itemImage = NULL;
}


Item::~Item(void)
{
	removeChild(m_itemImage, true);
	m_itemImage->release();
	m_itemImage = NULL;
}

void Item::setType(int type)
{
	if(m_itemImage == NULL)
	{
		m_itemImage = CCSprite::create();
		addChild(m_itemImage);
		m_itemImage->retain();
	}

	if(m_type != type)
	{
		m_type = type;
		char name[16];
		sprintf(name, "item%d", type);
		m_itemImage->setSpriteFrame(name);
	}
}

void Item::reset()
{
	this->setScale(1.0f);
}


void Item::dispose()
{
	this->release();
}
