#ifndef _POOLOJBECT_HEAD
#define _POOLOJBECT_HEAD

class PoolObject
{
public:
	PoolObject(void);
	virtual ~PoolObject(void);
	virtual void reset() = 0;
	virtual void dispose() = 0;
};

#endif