#include "SrvEngine.h"

zServerRegMgr::zServerRegMgr()
{
}


zServerRegMgr::~zServerRegMgr()
{
}

bool zServerRegMgr::getUniqeID(QWORD& tempid)
{
	return true;
}

void zServerRegMgr::putUniqeID(const QWORD& tempid)
{

}

zServerReg* zServerRegMgr::CreateObj()
{
	return objpool.CreateObj();
}

void zServerRegMgr::DestroyObj(zServerReg* obj)
{
	objpool.DestroyObj(obj);
}

bool zServerRegMgr::add(zServerReg* obj)
{
	return zEntryMgrsessid::addEntry(obj);
}

void zServerRegMgr::remove(zServerReg* obj)
{
	return zEntryMgrsessid::removeEntry(obj);
}

zServerReg* zServerRegMgr::get(int64 id)
{
	return (zServerReg*)zEntryMgrsessid::getEntryByID(id);
}

zServerReg* zServerRegMgr::getBySessID(int64 id)
{
	return (zServerReg*)zEntryMgrsessid::getEntryBysessid(id);
}



