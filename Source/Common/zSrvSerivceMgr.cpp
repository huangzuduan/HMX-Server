#include "SrvEngine.h"

zSerivce::zSerivce()
{
}

int32_t zSerivce::GetType() const
{
	if (STRNICMP(name_.c_str(), "server", 6) == 0)
	{
		return 1;
	}
	else if (STRNICMP(name_.c_str(), "client", 6) == 0)
	{
		return 2;
	}
	else if (STRNICMP(name_.c_str(), "mysqld", 6) == 0)
	{
		return 3;
	}
	else if (STRNICMP(name_.c_str(), "webserver", 9) == 0)
	{
		return 4;
	}
	else
	{
		return 0;
	}
}

bool zSerivce::LoadConfig(zXMLParser& xml, xmlNodePtr node)
{
	xml.getNodePropNum(node, "id", &id, sizeof(id));
	xml.getNodePropStr(node, "name", name_);
	xml.getNodePropNum(node, "remoteid", &remoteid, sizeof(remoteid));
	xml.getNodePropStr(node, "ip", host);
	xml.getNodePropNum(node, "port", &port, sizeof(port));
	xml.getNodePropNum(node, "maxConnects", &maxConnects, sizeof(maxConnects));
	xml.getNodePropStr(node, "fun", fun);
	xml.getNodePropStr(node, "user", user);
	xml.getNodePropStr(node, "passwd", passwd);
	xml.getNodePropStr(node, "value", value);
	xml.getNodePropNum(node, "broadcast", &broadcast, sizeof(broadcast));

	dataProto.set_serivceid(this->id);
	dataProto.set_serivcename(this->name_);
	dataProto.set_serivcefun(this->fun);
	dataProto.set_serivceremoteid(this->remoteid);
	dataProto.set_serivceip(this->host);
	dataProto.set_serivceport(this->port);
	dataProto.set_serivceuser(this->user);
	dataProto.set_serivcepasswd(this->passwd);
	dataProto.set_serivcevalue(this->value);
	dataProto.set_maxconntions(this->maxConnects);

	return true;
}

zServerMgr::zServerMgr()
{
	id = recvsrvlist = broadcastlist = 0;
}

zServerMgr::~zServerMgr()
{

}

bool zServerMgr::LoadConfig(zXMLParser& xml, xmlNodePtr node)
{
	xml.getNodePropNum(node, "id", &id, sizeof(id));
	xml.getNodePropStr(node, "name", name_);
	xml.getNodePropNum(node, "recvsrvlist", &recvsrvlist, sizeof(recvsrvlist));
	xml.getNodePropNum(node, "broadcastlist", &broadcastlist, sizeof(broadcastlist));
	xml.getNodePropStr(node, "platUrl", platUrl);
	

	dataProto.set_serverid(this->id);
	dataProto.set_recvsrvlist(this->recvsrvlist);
	dataProto.set_broadcastlist(this->broadcastlist);

	xmlNodePtr serivceNode = xml.getChildNode(node, "Serivce");
	while (serivceNode)
	{
		zSerivce* obj = objpool.construct();
		obj->LoadConfig(xml, serivceNode);
		if (!zEntryMgr< zEntryID<0> >::addEntry(obj))
		{
			objpool.destroy(obj);
		}
		serivceNode = xml.getNextNode(serivceNode, "Serivce");
	}
	return true;
}

bool zServerMgr::StartSerivces(zNetSerivce* pNetSerivce)
{
	struct MyStruct : public execEntry<zSerivce>
	{
		MyStruct(zNetSerivce* zNetSrv_)
		{
			isFinish = true;
			zNetSrv = zNetSrv_;
		}
		virtual bool exec(zSerivce *entry)
		{
			if (entry->GetType() == 1)
			{
				zNetSrv->doBindServer(entry->GetDataProto());
			}
			else if (entry->GetType() == 2)
			{
				zNetSrv->doConnectServer(entry->GetDataProto());
			}
			else if (entry->GetType() == 3)
			{
				zNetSrv->doConnectMysql(entry->GetDataProto());
			}
			else if (entry->GetType() == 4)
			{
				zNetSrv->doWebServer(entry->GetDataProto());
			}
			return true;
		}
		bool isFinish;
		zNetSerivce* zNetSrv;
	};
	MyStruct myStruct(pNetSerivce);
	execEvery(myStruct);
	pNetSerivce->bindTimer();
	return myStruct.isFinish;
}

void zServerMgr::GetBroadSerives(std::vector<zSerivce*>& vecBroadSerives)
{
	struct MyStruct : public execEntry<zSerivce>
	{
		MyStruct(std::vector<zSerivce*>& _vecBroadSerives):vecBroadSerives(_vecBroadSerives)
		{
		}
		virtual bool exec(zSerivce *entry)
		{
			if (entry->GetType() == 1 )
			{
				bool result = STRNICMP(entry->GetDataProto().serivcefun().c_str(), "forss",5) == 0 || STRNICMP(entry->GetDataProto().serivcefun().c_str(), "foruser",7) == 0;
				if (result)
				{
					vecBroadSerives.push_back(entry);
				}
			}
			return true;
		}
		std::vector<zSerivce*>& vecBroadSerives;
	};
	MyStruct myStruct(vecBroadSerives);
	execEvery(myStruct);
}

zSrvSerivceMgr::zSrvSerivceMgr()
{

}

zSrvSerivceMgr::~zSrvSerivceMgr()
{
	
}

bool zSrvSerivceMgr::LoadConfig(const std::string& filename)
{
	zXMLParser xml;
	if (!xml.initFile(filename))
	{
		return false;
	}

	xmlNodePtr rootNode = xml.getRootNode("Serivces");
	if (!rootNode)
	{
		return false;
	}

	xmlNodePtr serverNode = xml.getChildNode(rootNode, "Server");
	while (serverNode)
	{
		zServerMgr* obj = new zServerMgr();
		obj->LoadConfig(xml, serverNode);
		zEntryMgr< zEntryID<0> >::addEntry(obj);
		serverNode = xml.getNextNode(serverNode, "Server");
	}
	return true;
}




