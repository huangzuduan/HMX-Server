#include "srvEngine.h"


zSerivceCfgMgr::zSerivceCfgMgr()
{

}

zSerivceCfgMgr::~zSerivceCfgMgr()
{

}

bool zSerivceCfgMgr::loadConfig(const std::string& filename)
{

	zXMLParser xml;
	if (!xml.initFile(filename.c_str()))
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
		Server serverInfo;
		xml.getNodePropNum(serverNode, "id", &serverInfo.id, sizeof(serverInfo.id));
		xml.getNodePropStr(serverNode, "name",serverInfo.name);
		xml.getNodePropNum(serverNode, "recvsrvlist", &serverInfo.recvsrvlist, sizeof(serverInfo.recvsrvlist));
		xml.getNodePropNum(serverNode, "broadcastlist", &serverInfo.broadcastlist, sizeof(serverInfo.broadcastlist));
		xmlNodePtr serivceNode = xml.getChildNode(serverNode, "Serivce");
		while (serivceNode)
		{
			Serivce serivceInfo;
			xml.getNodePropNum(serivceNode, "id", &serivceInfo.id, sizeof(serivceInfo.id));
			xml.getNodePropStr(serivceNode, "name", serivceInfo.name);
			xml.getNodePropNum(serivceNode, "remoteid", &serivceInfo.remoteid, sizeof(serivceInfo.remoteid));
			xml.getNodePropStr(serivceNode, "ip", serivceInfo.ip);
			xml.getNodePropNum(serivceNode, "port", &serivceInfo.port, sizeof(serivceInfo.port));
			xml.getNodePropNum(serivceNode, "maxConnects", &serivceInfo.maxConnects, sizeof(serivceInfo.maxConnects));
			xml.getNodePropStr(serivceNode, "fun", serivceInfo.fun);
			xml.getNodePropStr(serivceNode, "user", serivceInfo.user);
			xml.getNodePropStr(serivceNode, "passwd", serivceInfo.passwd);
			xml.getNodePropStr(serivceNode, "value", serivceInfo.value);
			xml.getNodePropNum(serivceNode, "broadcast", &serivceInfo.broadcast, sizeof(serivceInfo.broadcast));
			serverInfo.serivces.insert(std::make_pair(serivceInfo.id, serivceInfo));
			serivceNode = xml.getNextNode(serivceNode, "Serivce");
		}
		allServers.insert(std::make_pair(serverInfo.id, serverInfo));
		serverNode = xml.getNextNode(serverNode, "Server");
	}


	return true;
}


const std::map<int32, zSerivceCfgMgr::Server>& zSerivceCfgMgr::getServer() const
{
	return allServers;
}

const zSerivceCfgMgr::Server* zSerivceCfgMgr::getServer(int32 serverid) const
{
	std::map<int32, zSerivceCfgMgr::Server>::const_iterator it = allServers.find(serverid);
	if ( it != allServers.end())
	{
		return &it->second;
	}
	return NULL;
}

const zSerivceCfgMgr::Serivce* zSerivceCfgMgr::getSerivce(int32 serverid, int32 serivceid) const
{
	const zSerivceCfgMgr::Server* server = getServer(serverid);
	if (server)
	{
		std::map<int32, zSerivceCfgMgr::Serivce>::const_iterator it = server->serivces.find(serivceid);
		if (it != server->serivces.end())
		{
			return &it->second;
		}
	}
	return NULL;
}

