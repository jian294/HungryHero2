#ifndef _ITEM_HEAD
#define  _ITEM_HEAD
#include "cocos2d.h"
#include "PoolObject.h"
USING_NS_CC;

class Item : public CCSprite, PoolObject
{
public:
	Item(void);
	~Item(void);
	void setType(int type);
	int getType(){return m_type;};
	void reset();
	void dispose();
	CREATE_FUNC(Item);
private:
	int m_type;
	CCSprite* m_itemImage;
};
#endif
