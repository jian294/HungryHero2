#ifndef _OBJECTPOOL_HEAD
#define  _OBJECTPOOL_HEAD
#include "PoolObject.h"
#include <vector>
//对象池
class ObjectPool
{
public:
	ObjectPool(int, int);
	~ObjectPool(void);
	
	//************************************
	// Method:    创建一个实例，从池子里面取或者重新创建
	// Returns:   PoolObject*
	// FullName:  ObjectPool::makeObject
	// Access:    public 
	// author:    kanefan
	//************************************
	PoolObject* makeObject();

	
	//************************************
	// Method:    回池或者销毁
	// Parameter: PoolObject * obj 操作的对象
	// Returns:   void
	// FullName:  ObjectPool::passivateObject
	// Access:    public 
	// author:    kanefan
	//************************************
	void passivateObject(PoolObject* obj);
private:
	//池子容量
	int m_max;

	//类型
	int m_type;

	//池子
	std::vector<PoolObject*> m_list;
};
#endif
