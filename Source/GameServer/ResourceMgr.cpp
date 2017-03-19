#include "ResourceMgr.h"

#include "def_buff.h"

#include "srvEngine.h"
#include "ConfigBase.h"
#include "GeneralScene.h"

#define XMLATTR(KEY) "<xmlattr>."#KEY 


using namespace boost::property_tree;

template <class TData, class TBase>
zDataBM<TData, TBase> *zDataBM<TData, TBase>::me(NULL);

zDataBM<zCharTypeB, CharTypeBase> &chartypebm = zDataBM<zCharTypeB, CharTypeBase>::getMe();
zDataBM<zCharLevelB, CharLevelBase> &charlevelbm = zDataBM<zCharLevelB, CharLevelBase>::getMe();
zDataBM<zNpcB, NpcBase> &npcbm = zDataBM<zNpcB, NpcBase>::getMe();
zDataBM<zShopB, ShopBase> &shopbm = zDataBM<zShopB, ShopBase>::getMe();
zDataBM<zSkillB, SkillBase> &skillbm = zDataBM<zSkillB, SkillBase>::getMe();
zDataBM<zItemB, ItemBase> &itembm = zDataBM<zItemB, ItemBase>::getMe();;


ResourceMgr::ResourceMgr()
{
}

ResourceMgr::~ResourceMgr()
{
}

//-----------------------------加载资源---------------------------------------------------

bool ResourceMgr::LoadAllResources()
{
	bool bResult = true;
	if(!LoadCharLevelResource(H::global["confdir"] +  "char_level.xml"))
	{
		bResult =  false;
	}

	if(!LoadMapInfoResource(H::global["confdir"] + "map_info.xml"))
	{
		bResult = false;
	}

	if(!LoadCharTypeResource(H::global["confdir"] + "char_type.xml"))
	{
		bResult = false;
	}

	if(!LoadQuestResource(H::global["confdir"] + "quest_info.xml"))
	{
		bResult = false;
	}

	if (!LoadNpcBaseResource(H::global["confdir"] + "npcbase.xml"))
	{
		bResult = false;
	}

	if (!LoadItemResource(H::global["confdir"] + "itembase.xml"))
	{
		bResult = false;
	}

	if (!LoadShopResource(H::global["confdir"] + "shop.xml"))
	{
		bResult = false;
	}

	if (!LoadSkillResource(H::global["confdir"] + "skillbase.xml"))
	{
		bResult = false;
	}

	GeneralSceneMgr::getMe().CreateAllScene();
	
	return bResult;
}

const StMapInfoResCfg* ResourceMgr::GetMapInfoCfg(int32 nMapID)
{
	MapInfoResMapType::const_iterator it = m_mapMapInfo.find(nMapID);
	if (it != m_mapMapInfo.end())
	{
		return &it->second;
	}
	return NULL;
}

const StMapZoneResCfg* ResourceMgr::GetMapZoneRes(int32 nMapID)
{
	MapZoneResMapType::const_iterator it = m_mapZoneInfo.find(nMapID);
	if( it != m_mapZoneInfo.end())
	{
		return &it->second;
	}
	return NULL;
}


// 角色等级 
bool ResourceMgr::LoadCharLevelResource(const std::string& strFileName)
{
	ptree cPtreeDoc;
	ptree cRootNode;
	read_xml(strFileName, cPtreeDoc, xml_parser::trim_whitespace);
	cRootNode = cPtreeDoc.get_child("root");
	for(BOOST_AUTO(pos,cRootNode.begin());pos != cRootNode.end();++pos)  //boost中的auto     
	{    
		ptree& itemNode = pos->second;
		CharLevelBase sItem;
		sItem.field0 = itemNode.get<int32>(XMLATTR(field0));
		sItem.field1 = itemNode.get<int32>(XMLATTR(field1));
		sItem.field2 = itemNode.get<int32>(XMLATTR(field2));
		sItem.field3 = itemNode.get<int32>(XMLATTR(field3));
		sItem.field4 = itemNode.get<int32>(XMLATTR(field4));
		sItem.field5 = itemNode.get<int32>(XMLATTR(field5));
		sItem.field6 = itemNode.get<int32>(XMLATTR(field6));
		sItem.field7 = itemNode.get<int32>(XMLATTR(field7));
		sItem.field8 = itemNode.get<int32>(XMLATTR(field8));
		sItem.field9 = itemNode.get<int32>(XMLATTR(field9));
		sItem.field10 = itemNode.get<int32>(XMLATTR(field10));
		sItem.field11 = itemNode.get<int32>(XMLATTR(field11));
		sItem.field12 = itemNode.get<int32>(XMLATTR(field12));
		sItem.field13 = itemNode.get<int32>(XMLATTR(field13));
		sItem.field14 = itemNode.get<int32>(XMLATTR(field14));
		sItem.field15 = itemNode.get<int32>(XMLATTR(field15));
		sItem.field16 = itemNode.get<int32>(XMLATTR(field16));
		sItem.field17 = itemNode.get<int32>(XMLATTR(field17));
		sItem.field18 = itemNode.get<int32>(XMLATTR(field18));
		sItem.field19 = itemNode.get<int32>(XMLATTR(field19));
		charlevelbm.refresh(sItem);

	}    
	return true;
}


bool ResourceMgr::LoadMapInfoResource(const std::string& strFileName)
{
	ptree cPtreeDoc;
	ptree cRootNode;
	read_xml(strFileName, cPtreeDoc, xml_parser::trim_whitespace);
	cRootNode = cPtreeDoc.get_child("root");
	for(BOOST_AUTO(pos,cRootNode.begin());pos != cRootNode.end();++pos)  //boost中的auto     
	{    
		ptree& itemNode = pos->second;
		StMapInfoResCfg sItem;
		sItem.nMapId = itemNode.get<int32>(XMLATTR(id));
		sItem.nSceneType = itemNode.get<int32>(XMLATTR(scene_type));
		sItem.strSceneFileName = itemNode.get<std::string>(XMLATTR(scenefile));
		sItem.strZoneFileName = itemNode.get<std::string>(XMLATTR(zonefile));
		m_mapMapInfo.insert(std::make_pair(sItem.nMapId,sItem));

	}

	// 加载地图区域与阻挡 
	MapInfoResMapType::iterator it = m_mapMapInfo.begin();
	for (; it != m_mapMapInfo.end();++it)
	{
		int32 nMapId = it->first;
		StMapInfoResCfg rItem = it->second;
		if (!LoadMapRes(nMapId, std::string(H::global["datadir"] + rItem.strSceneFileName)))
		{
			H::logger->error("Load map fail,id=%u", nMapId);
		}

		if(!LoadZoneRes(nMapId,std::string(H::global["confdir"] + "zone/" + rItem.strZoneFileName)))
		{
			H::logger->error("Load zone fail,id=%u",nMapId);
		}
	}

	return true;
}

/*------------------------------------------------
* 加载地图区域资源 
*-----------------------------------------------*/
bool ResourceMgr::LoadZoneRes(int32 nMapId,const std::string& strFileName)
{
	ptree cPtreeDoc;
	ptree cMapNode;
	//ptree cBlockNode;
	//ptree cNpcNode;
	ptree cData;

	read_xml(strFileName, cPtreeDoc, xml_parser::trim_whitespace);
	cMapNode = cPtreeDoc.get_child("map");

	StMapZoneResCfg sItem;

	sItem.nMapId = cMapNode.get<int32>(XMLATTR(id));
	if(sItem.nMapId != nMapId)
	{
		return false;
	}

	sItem.nXAmount = cMapNode.get<int32>(XMLATTR(maxX));
	sItem.nYAmount = cMapNode.get<int32>(XMLATTR(maxY));
	sItem.nXCellLength = cMapNode.get<int32>(XMLATTR(gridSizeX));
	sItem.nYCellLength = cMapNode.get<int32>(XMLATTR(gridSizeY));
	sItem.nBlock = cMapNode.get<int32>(XMLATTR(block));
	sItem.nNpc = cMapNode.get<int32>(XMLATTR(npc));

//	sItem.strData = cMapNode.get<string>(XMLATTR(data));


	//cBlockNode = cMapNode.get_child("block");
	//cNpcNode = cMapNode.get_child("npc");
	cData = cMapNode.get_child("data");
	sItem.strData = cData.data();

	ASSERT(sItem.strData.length() < 10240 );

	static char arrValues[10240];
	memset(arrValues,0,sizeof(10240));
	strncpy(arrValues,sItem.strData.c_str(), sItem.nXAmount * sItem.nYAmount);
	//// 将data=000022226666的数据进行小格子化 
	for(int32 j = 0 ; j < sItem.nYAmount; ++j)
	{
		std::vector<int8> items_vec;
		for (int32 i = 0 ; i < sItem.nXAmount; ++i)
		{
			int32 nIndex = j * sItem.nYAmount + i;
			char  a =  arrValues[nIndex];
			items_vec.push_back(atoi(&a));

		}
		sItem.regionValue.push_back(items_vec);
	}  

	m_mapZoneInfo.insert(std::make_pair(sItem.nMapId,sItem));
	return true;
}

/*------------------------------------------------
* 加载地图阻挡资源
*-----------------------------------------------*/
bool ResourceMgr::LoadMapRes(int32 nMapId,const std::string& strFileName)
{

	ptree cPtreeDoc;
	ptree cMapNode;
	ptree cData;
	//ptree cBlockNode;
	//ptree cNpcNode;

	read_xml(strFileName, cPtreeDoc, xml_parser::trim_whitespace);
	cMapNode = cPtreeDoc.get_child("map");

	StMapSceneResCfg sItem;

	sItem.nMapId = cMapNode.get<int32>(XMLATTR(id));
	if(sItem.nMapId != nMapId)
	{
		return false;
	}

	sItem.nXAmount = cMapNode.get<int32>(XMLATTR(maxX));
	sItem.nYAmount = cMapNode.get<int32>(XMLATTR(maxY));
	sItem.nXCellLength = cMapNode.get<int32>(XMLATTR(gridSizeX));
	sItem.nYCellLength = cMapNode.get<int32>(XMLATTR(gridSizeY));

	//cBlockNode = cMapNode.get_child("block");
	//cNpcNode = cMapNode.get_child("npc");

	cData = cMapNode.get_child("data");
	sItem.strData = cData.data();

	ASSERT(sItem.strData.length() < 10240);

	static char arrValues[10240];
	memset(arrValues, 0, sizeof(10240));
	strncpy(arrValues, sItem.strData.c_str(), sItem.nXAmount * sItem.nYAmount);
	//// 将data=000022226666的数据进行小格子化 
	for (int32 j = 0; j < sItem.nYAmount; ++j)
	{
		std::vector<int8> items_vec;
		for (int32 i = 0; i < sItem.nXAmount; ++i)
		{
			int32 nIndex = j * sItem.nYAmount + i;
			char  a = arrValues[nIndex];
			items_vec.push_back(atoi(&a));

		}
		sItem.regionValue.push_back(items_vec);
	}
	m_mapSceneInfo.insert(std::make_pair(sItem.nMapId,sItem));

	return true;
}

bool ResourceMgr::LoadCharTypeResource(const std::string& strFileName)
{
	ptree cPtreeDoc;
	ptree cRootNode;
	read_xml(strFileName, cPtreeDoc, xml_parser::trim_whitespace);
	cRootNode = cPtreeDoc.get_child("root");
	for(BOOST_AUTO(pos,cRootNode.begin());pos != cRootNode.end();++pos)  //boost中的auto     
	{    
		ptree& itemNode = pos->second;
		CharTypeBase sItem;
		sItem.field0 = itemNode.get<int32>(XMLATTR(field0));
		std::string name = itemNode.get<std::string>(XMLATTR(field1));
		strncpy(sItem.field1, name.c_str(), 32);
		sItem.field2 = itemNode.get<int32>(XMLATTR(field2));
		sItem.field3 = itemNode.get<int32>(XMLATTR(field3));
		sItem.field4 = itemNode.get<int32>(XMLATTR(field4));
		sItem.field5 = itemNode.get<int32>(XMLATTR(field5));
		chartypebm.refresh(sItem);
	}   

	printf("[INFO]:Load %s .............ok\n", strFileName.c_str());

	return true;
}

bool ResourceMgr::LoadQuestResource(const std::string& strFileName)
{
	ptree cPtreeDoc;
	ptree cRootNode;
	read_xml(strFileName, cPtreeDoc, xml_parser::trim_whitespace);
	cRootNode = cPtreeDoc.get_child("root");
	for(BOOST_AUTO(pos,cRootNode.begin());pos != cRootNode.end();++pos)  //boost中的auto     
	{    
		ptree& itemNode = pos->second;
		StQuestInfoResCfg  sItem;
		sItem.nId = itemNode.get<int32>(XMLATTR(id));
		sItem.nType = itemNode.get<int32>(XMLATTR(type));
		sItem.nSubType = itemNode.get<int32>(XMLATTR(subtype));
		//sItem.strTitle = itemNode.get<std::string>(XMLATTR(title));
		//sItem.strContent = itemNode.get<std::string>(XMLATTR(content));
	
		sItem.accept[0].nType = itemNode.get<int32>(XMLATTR(apt_type_0));
		sItem.accept[0].nArg0 = itemNode.get<int32>(XMLATTR(apt_arg_0_0));
		sItem.accept[0].nArg1 = itemNode.get<int32>(XMLATTR(apt_arg_0_1));
		sItem.accept[1].nType = itemNode.get<int32>(XMLATTR(apt_type_1));
		sItem.accept[1].nArg0 = itemNode.get<int32>(XMLATTR(apt_arg_1_0));
		sItem.accept[1].nArg1 = itemNode.get<int32>(XMLATTR(apt_arg_1_1));
		sItem.accept[2].nType = itemNode.get<int32>(XMLATTR(apt_type_2));
		sItem.accept[2].nArg0 = itemNode.get<int32>(XMLATTR(apt_arg_2_0));
		sItem.accept[2].nArg1 = itemNode.get<int32>(XMLATTR(apt_arg_2_1));
		sItem.accept[3].nType = itemNode.get<int32>(XMLATTR(apt_type_3));
		sItem.accept[3].nArg0 = itemNode.get<int32>(XMLATTR(apt_arg_3_0));
		sItem.accept[3].nArg1 = itemNode.get<int32>(XMLATTR(apt_arg_3_1));

		sItem.finish[0].nType = itemNode.get<int32>(XMLATTR(fsh_type_0));
		sItem.finish[0].nArg0 = itemNode.get<int32>(XMLATTR(fsh_arg_0_0));
		sItem.finish[0].nArg1 = itemNode.get<int32>(XMLATTR(fsh_arg_0_1));
		sItem.finish[1].nType = itemNode.get<int32>(XMLATTR(fsh_type_1));
		sItem.finish[1].nArg0 = itemNode.get<int32>(XMLATTR(fsh_arg_1_0));
		sItem.finish[1].nArg1 = itemNode.get<int32>(XMLATTR(fsh_arg_1_1));
		sItem.finish[2].nType = itemNode.get<int32>(XMLATTR(fsh_type_2));
		sItem.finish[2].nArg0 = itemNode.get<int32>(XMLATTR(fsh_arg_2_0));
		sItem.finish[2].nArg1 = itemNode.get<int32>(XMLATTR(fsh_arg_2_1));
		sItem.finish[3].nType = itemNode.get<int32>(XMLATTR(fsh_type_3));
		sItem.finish[3].nArg0 = itemNode.get<int32>(XMLATTR(fsh_arg_3_0));
		sItem.finish[3].nArg1 = itemNode.get<int32>(XMLATTR(fsh_arg_3_1));

		sItem.award[0].nType = itemNode.get<int32>(XMLATTR(ard_type_0));
		sItem.award[0].nArg0 = itemNode.get<int32>(XMLATTR(ard_arg_0_0));
		sItem.award[0].nArg1 = itemNode.get<int32>(XMLATTR(ard_arg_0_1));
		sItem.award[1].nType = itemNode.get<int32>(XMLATTR(ard_type_1));
		sItem.award[1].nArg0 = itemNode.get<int32>(XMLATTR(ard_arg_1_0));
		sItem.award[1].nArg1 = itemNode.get<int32>(XMLATTR(ard_arg_1_1));
		sItem.award[2].nType = itemNode.get<int32>(XMLATTR(ard_type_2));
		sItem.award[2].nArg0 = itemNode.get<int32>(XMLATTR(ard_arg_2_0));
		sItem.award[2].nArg1 = itemNode.get<int32>(XMLATTR(ard_arg_2_1));
		sItem.award[3].nType = itemNode.get<int32>(XMLATTR(ard_type_3));
		sItem.award[3].nArg0 = itemNode.get<int32>(XMLATTR(ard_arg_3_0));
		sItem.award[3].nArg1 = itemNode.get<int32>(XMLATTR(ard_arg_3_1));

		m_mapQuestResInfo.insert(std::make_pair(sItem.nId,sItem));
	}   

	printf("[INFO]:Load %s .............ok\n", strFileName.c_str());

	return true;
}

bool ResourceMgr::LoadNpcBaseResource(const std::string& strFileName)
{
	ptree cPtreeDoc;
	ptree cRootNode;
	read_xml(strFileName, cPtreeDoc, xml_parser::trim_whitespace);
	cRootNode = cPtreeDoc.get_child("root");
	for (BOOST_AUTO(pos, cRootNode.begin()); pos != cRootNode.end(); ++pos)  //boost中的auto     
	{
		ptree& itemNode = pos->second;
		NpcBase sItem;
		sItem.field0 = itemNode.get<int32>(XMLATTR(field0));
		std::string name = itemNode.get<std::string>(XMLATTR(field1));
		strncpy(sItem.field1, name.c_str(),32);
		sItem.field2 = itemNode.get<int32>(XMLATTR(field2));
		sItem.field3 = itemNode.get<int32>(XMLATTR(field3));
		sItem.field4 = itemNode.get<int32>(XMLATTR(field4));
		sItem.field5 = itemNode.get<int32>(XMLATTR(field5));
		sItem.field6 = itemNode.get<int32>(XMLATTR(field6));
		sItem.field7 = itemNode.get<int32>(XMLATTR(field7));
		sItem.field8 = itemNode.get<int32>(XMLATTR(field8));
		sItem.field9 = itemNode.get<int32>(XMLATTR(field9));
		sItem.field10 = itemNode.get<int32>(XMLATTR(field10));
		sItem.field11 = itemNode.get<int32>(XMLATTR(field11));
		sItem.field12 = itemNode.get<int32>(XMLATTR(field12));
		sItem.field13 = itemNode.get<int32>(XMLATTR(field13));
		sItem.field14 = itemNode.get<int32>(XMLATTR(field14));
		sItem.field15 = itemNode.get<int32>(XMLATTR(field15));
		sItem.field16 = itemNode.get<int32>(XMLATTR(field16));
		sItem.field17 = itemNode.get<int32>(XMLATTR(field17));
		sItem.field18 = itemNode.get<int32>(XMLATTR(field18));
		sItem.field19 = itemNode.get<int32>(XMLATTR(field19));
		sItem.field20 = itemNode.get<int32>(XMLATTR(field20));
		sItem.field21 = itemNode.get<int32>(XMLATTR(field21));
		sItem.field22 = itemNode.get<int32>(XMLATTR(field22));
		sItem.field23 = itemNode.get<int32>(XMLATTR(field23));
		sItem.field24 = itemNode.get<int32>(XMLATTR(field24));
		sItem.field25 = itemNode.get<int32>(XMLATTR(field25));
		sItem.field26 = itemNode.get<int32>(XMLATTR(field26));
		sItem.field27 = itemNode.get<int32>(XMLATTR(field27));
		sItem.field28 = itemNode.get<int32>(XMLATTR(field28));
		sItem.field29 = itemNode.get<int32>(XMLATTR(field29));
		sItem.field30 = itemNode.get<int32>(XMLATTR(field30));
		sItem.field31 = itemNode.get<int32>(XMLATTR(field31));
		sItem.field32 = itemNode.get<int32>(XMLATTR(field32));
		sItem.field33 = itemNode.get<int32>(XMLATTR(field33));
		sItem.field34 = itemNode.get<int32>(XMLATTR(field34));
		sItem.field35 = itemNode.get<int32>(XMLATTR(field35));
		sItem.field36 = itemNode.get<int32>(XMLATTR(field36));
		sItem.field37 = itemNode.get<int32>(XMLATTR(field37));
		std::string carryObjs = itemNode.get<std::string>(XMLATTR(field38));
		strncpy(sItem.field38, carryObjs.c_str(), 256);
		npcbm.refresh(sItem);
	}

	printf("[INFO]:Load %s .............ok\n", strFileName.c_str());

	return true;
}

bool ResourceMgr::LoadItemResource(const std::string& strFileName)
{
	ptree cPtreeDoc;
	ptree cRootNode;
	read_xml(strFileName, cPtreeDoc, xml_parser::trim_whitespace);
	cRootNode = cPtreeDoc.get_child("root");
	for (BOOST_AUTO(pos, cRootNode.begin()); pos != cRootNode.end(); ++pos)  //boost中的auto     
	{
		ptree& itemNode = pos->second;
		ItemBase sItem;
		sItem.field0 = itemNode.get<int32>(XMLATTR(field0));
		sItem.field1 = itemNode.get<std::string>(XMLATTR(field1));
		sItem.field2 = itemNode.get<int32>(XMLATTR(field2));
		sItem.field3 = itemNode.get<int32>(XMLATTR(field3));
		sItem.field4 = itemNode.get<int32>(XMLATTR(field4));
		sItem.field5 = itemNode.get<int32>(XMLATTR(field5));
		sItem.field6 = itemNode.get<int32>(XMLATTR(field6));
		sItem.field7 = itemNode.get<std::string>(XMLATTR(field7));
		sItem.field8 = itemNode.get<std::string>(XMLATTR(field8));
		sItem.field9 = itemNode.get<int32>(XMLATTR(field9));
		sItem.field10 = itemNode.get<int32>(XMLATTR(field10));
		sItem.field11 = itemNode.get<int32>(XMLATTR(field11));
		sItem.field12 = itemNode.get<int32>(XMLATTR(field12));
		sItem.field13 = itemNode.get<int32>(XMLATTR(field13));
		sItem.field14 = itemNode.get<int32>(XMLATTR(field14));
		sItem.field15 = itemNode.get<int32>(XMLATTR(field15));
		sItem.field16 = itemNode.get<int32>(XMLATTR(field16));
		sItem.field17 = itemNode.get<int32>(XMLATTR(field17));
		sItem.field18 = itemNode.get<int32>(XMLATTR(field18));
		sItem.field19 = itemNode.get<int32>(XMLATTR(field19));
		sItem.field20 = itemNode.get<int32>(XMLATTR(field20));
		sItem.field21 = itemNode.get<int32>(XMLATTR(field21));
		sItem.field22 = itemNode.get<int32>(XMLATTR(field22));
		sItem.field23 = itemNode.get<int32>(XMLATTR(field23));
		sItem.field24 = itemNode.get<int32>(XMLATTR(field24));
		sItem.field25 = itemNode.get<int32>(XMLATTR(field25));
		sItem.field26 = itemNode.get<int32>(XMLATTR(field26));
		sItem.field27 = itemNode.get<int32>(XMLATTR(field27));

		itembm.refresh(sItem);
	}

	printf("[INFO]:Load %s .............ok\n", strFileName.c_str());
	return true;
}

bool ResourceMgr::LoadShopResource(const std::string& strFileName)
{
	ptree cPtreeDoc;
	ptree cRootNode;
	read_xml(strFileName, cPtreeDoc, xml_parser::trim_whitespace);
	cRootNode = cPtreeDoc.get_child("root");
	for (BOOST_AUTO(pos, cRootNode.begin()); pos != cRootNode.end(); ++pos)  //boost中的auto     
	{
		ptree& itemNode = pos->second;
		ShopBase sItem;
		sItem.field0 = itemNode.get<int32>(XMLATTR(field0));
		std::string name = itemNode.get<std::string>(XMLATTR(field1));
		strncpy(sItem.field1, name.c_str(), 32);
		sItem.field2 = itemNode.get<int32>(XMLATTR(field2));
		sItem.field3 = itemNode.get<int32>(XMLATTR(field3));
		sItem.field4 = itemNode.get<int32>(XMLATTR(field4));
		sItem.field5 = itemNode.get<int32>(XMLATTR(field5));
		sItem.field6 = itemNode.get<int32>(XMLATTR(field6));
		sItem.field7 = itemNode.get<int32>(XMLATTR(field7));
		sItem.field8 = itemNode.get<int32>(XMLATTR(field8));
		shopbm.refresh(sItem);
	}

	printf("[INFO]:Load %s .............ok\n", strFileName.c_str());

	return true;
}

bool ResourceMgr::LoadSkillResource(const std::string& strFileName)
{
	ptree cPtreeDoc;
	ptree cRootNode;
	read_xml(strFileName, cPtreeDoc, xml_parser::trim_whitespace);
	cRootNode = cPtreeDoc.get_child("root");
	for (BOOST_AUTO(pos, cRootNode.begin()); pos != cRootNode.end(); ++pos)  //boost中的auto     
	{
		ptree& itemNode = pos->second;
		SkillBase sItem;
		sItem.field0 = itemNode.get<int32>(XMLATTR(field0));
		std::string name = itemNode.get<std::string>(XMLATTR(field1));
		strncpy(sItem.field1, name.c_str(), 32);
		sItem.field2 = itemNode.get<int32>(XMLATTR(field2));
		sItem.field3 = itemNode.get<int32>(XMLATTR(field3));
		sItem.field4 = itemNode.get<std::string>(XMLATTR(field4));
		sItem.field5 = itemNode.get<std::string>(XMLATTR(field5));
		sItem.field6 = itemNode.get<std::string>(XMLATTR(field6));
		sItem.field7 = itemNode.get<std::string>(XMLATTR(field7));
		sItem.field8 = itemNode.get<std::string>(XMLATTR(field8));
		skillbm.refresh(sItem);
	}

	printf("[INFO]:Load %s .............ok\n", strFileName.c_str());
	return true;
}


/////////////////////////////////////GET/////////////////////////////////////

const StCharacterLevelCfg* ResourceMgr::GetCharacterLevelBase(int32 nRoleType,int32 nLevel)
{
	CharacterLevelMapType::iterator it = m_mapCharacterLevelBase.find(nRoleType * 1000 + nLevel);
	if( it != m_mapCharacterLevelBase.end())
	{
		return &(it->second);
	}
	return NULL;
}


const StRoleTypeInitCfg* ResourceMgr::GetRoleTypeInitInfoRes(int32 nRoleType)
{
	RoleTypeInitMapType::iterator it = m_mapRoleTypeInitInfo.find(nRoleType);
	if( it != m_mapRoleTypeInitInfo.end())
	{
		return &(it->second);
	}
	return NULL;
}


