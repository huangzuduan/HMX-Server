#include "DBServer_PCH.h"
#include "Memory.h"

namespace dbmem
{

	Memory Memory::data("Data");
	Memory Memory::log("Log");

	Memory::Memory(const char* _name)
	{
		strncpy(name, _name, sizeof(name));
		dbConn = NULL;
	}

	Memory::~Memory()
	{

	}

}

