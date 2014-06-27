#ifndef _OBJECTPOOL_HEAD
#define  _OBJECTPOOL_HEAD
#include "PoolObject.h"
#include <vector>
//�����
class ObjectPool
{
public:
	ObjectPool(int, int);
	~ObjectPool(void);
	
	//************************************
	// Method:    ����һ��ʵ�����ӳ�������ȡ�������´���
	// Returns:   PoolObject*
	// FullName:  ObjectPool::makeObject
	// Access:    public 
	// author:    kanefan
	//************************************
	PoolObject* makeObject();

	
	//************************************
	// Method:    �سػ�������
	// Parameter: PoolObject * obj �����Ķ���
	// Returns:   void
	// FullName:  ObjectPool::passivateObject
	// Access:    public 
	// author:    kanefan
	//************************************
	void passivateObject(PoolObject* obj);
private:
	//��������
	int m_max;

	//����
	int m_type;

	//����
	std::vector<PoolObject*> m_list;
};
#endif
