#ifndef _GAME_DEFINE_H_
#define _GAME_DEFINE_H_





#include "BaseDefine.h"

class BaseContext;
class BaseStatus;

class BaseStatus
{
public:
	BaseStatus(int32 nValue):m_nValue(nValue)
	{

	}

	virtual void DoHandler(BaseContext* pContext);

protected:

	int32 m_nValue;

};

class BaseContext
{
public:

	BaseContext(BaseStatus* pStatus):m_pStatus(pStatus)
	{

	}

	virtual void Request() = 0;

protected:

	BaseStatus* m_pStatus;
};

// compsite mode design 
class BaseObject
{
public:
	BaseObject(int32 nObjId):m_nObjId(nObjId){}

	virtual void Add(int32 nObjId,BaseObject* pObject){}

	virtual void Remove(int32 nObjId){}

	virtual void Display(){}

protected:

	int32 m_nObjId;
};


class CommonObject : public BaseObject, public BaseContext
{
public:
	CommonObject(int32 nObjId,BaseStatus* pStatus ):BaseObject(nObjId),BaseContext(pStatus)
	{

	}
};







#endif


