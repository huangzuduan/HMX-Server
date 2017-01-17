
#ifndef  _CSBOX_H
#define  _CSBOX_H
#include "csCommon.h"

#pragma pack(1)


/////////////////////////////////////////////////////////////
/// 暂定宝盒相关指令
////////////////////////////////////////////////////////////

namespace Cmd
{

struct stCowBoxUserCmd : public stNullUserCmd
{
	stCowBoxUserCmd()
	{
		byCmd = SAFETY_COWBOX;
	}
};


//客户端发送钥匙被点击消息
#define SET_COWBOX_KEY_PARAMETER 1
struct stSetCowBoxKeyCmd : public stCowBoxUserCmd
{
	stSetCowBoxKeyCmd()
	{
		byParam = SET_COWBOX_KEY_PARAMETER;
	}
	DWORD Key_id;
	DWORD qwThisID;
};
//服务端发送宝盒初始化消息
#define GET_COWBOX_INIT_OPEN 2
struct stGetCowBoxInitCmd : public stCowBoxUserCmd
{
	stGetCowBoxInitCmd()
	{
		byParam = GET_COWBOX_INIT_OPEN;
	}
	//DWORD itemID[17];  //暂时用ID来获取ObjectBase_t数据，后期根据服务端发送的物品数据类型来跟换
	t_Object objects[17];
	int item_Ti;       //再来一次按键所以转到物品的格子数组下标标识
};

//用户点击宝盒控件的 提取 按键
#define SET_COWBOX_TIQU_ITEM 3
struct stSetCowBoxTiquCmd : public stCowBoxUserCmd
{
	stSetCowBoxTiquCmd()
	{
		byParam = SET_COWBOX_TIQU_ITEM;
	}
	bool item_id;
}; 


/////////////////////////////////////////////////////////////
/// 定义宝盒相关指令结束
//////////////////////////////////////////////////////////// 


struct stHotspringUserCmd : public stNullUserCmd    //温泉消息
{
	stHotspringUserCmd()
	{
		byCmd = HOTSPRING_USERCMD;
	}
};

#define SET_TRUN_GOTOMALE_PARAMETER 1
struct stGoToMaleCmd : public stHotspringUserCmd   //进入男温泉
{
	stGoToMaleCmd()
	{
		byParam = SET_TRUN_GOTOMALE_PARAMETER;
	}
};

#define SET_TRUN_GOTOFEMALE_PARAMETER 2
struct  stGoToFemaleCmd : public stHotspringUserCmd  //进入女温泉
{
	stGoToFemaleCmd()
	{
		byParam = SET_TRUN_GOTOFEMALE_PARAMETER;
	}
};

#define SET_TRUN_EXITHOTSPRING_PARAMETER 3
struct  stExitHotspringCmd : public stHotspringUserCmd  //离开温泉
{
	stExitHotspringCmd()
	{
		byParam = SET_TRUN_EXITHOTSPRING_PARAMETER;
	}
};

/************************************************************************/
/* sky 新打造消息定义 begin                                               */
/************************************************************************/
// sky 装备打造消息
struct stReMakUserCmd : public stNullUserCmd
{
	stReMakUserCmd()
	{
		byCmd = REMAKEOBJECT_USERCMD;
	}
};

//sky 客户端通知服务端打造物品消息
#define SET_NEW_MAKEOBJECT_USERCMD_ITEM 1
struct stNewMakeObjectUserCmd : public stReMakUserCmd
{
	stNewMakeObjectUserCmd()
	{
		byParam = SET_NEW_MAKEOBJECT_USERCMD_ITEM;
		dwID = 0;
		MakeLevel = 0;
		num = 0;
	}
	DWORD dwID;		//sky 要打造的物品ID
	BYTE MakeLevel; //sky 打造物品的级别(0普通,1蓝色,2绿装,4紫装,8橙装)
	BYTE num;		//sky 打造数量
};

//sky 服务端通知客户端打造结果
#define SET_NEW_MAKEOBJECT_RETURN_USERCMD_ITEM 2
struct stNewMakeObjectReturnUserCmd : public stReMakUserCmd
{
	stNewMakeObjectReturnUserCmd()
	{
		byParam = SET_NEW_MAKEOBJECT_RETURN_USERCMD_ITEM;
		MakeType = 1;
	}
	BYTE MakeType;	//sky 打造类型(1:打造)
	WORD returnNum; //sky 返回错误码(0:成功 1:钱不够 2:材料不够 3:包袱空间不足 4:未知错误)
};
/************************************************************************/
/*   sky 打造消息定义 end                                               */
/************************************************************************/

////////////////////////////////////////////////////////////
/// 训马指令
////////////////////////////////////////////////////////////
struct stHorseUserCmd : public stNullUserCmd
{
	stHorseUserCmd()
	{
		byCmd = HORSETRAINING_USERCMD;
	}
};

//战马训练1		0
//战马训练2		1
//战马训练3		2
//清除训练		3

#define HORSETRAINING_USERCMD_TEY 1
struct stHorseTrainingUserCmd : public stHorseUserCmd
{
	stHorseTrainingUserCmd()
	{
		byParam = HORSETRAINING_USERCMD_TEY;
	}
	int CmdTey;
};
/////////////////////////////////////////////////////////////
////  训马指令END
/////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////
////  SKY 自由加点指令
/////////////////////////////////////////////////////////////
struct stAttruByteUserCmd : public stNullUserCmd
{
	stAttruByteUserCmd()
	{
		byCmd = SURPLUS_ATTRIBUTE_USERCMD;
	}
};


//加点
enum ATTRIBUTETYPE{
  PPT_STR,	// 力量
  PPT_INTE,	// 智力
  PPT_DEX,	// 敏捷
  PPT_SPI,	// 精神
  PPT_CON,	// 体质
};

#define SURPLUS_ATTRIBUTE_USERCMD_ADD 1
struct stAddAttruByteUserCmd : public stAttruByteUserCmd
{
	stAddAttruByteUserCmd()
	{
		byParam = SURPLUS_ATTRIBUTE_USERCMD_ADD;
	}

	stObjectLocation pos;   //物品在包袱中的位置
	BYTE Add_Type;  //需要加点的属性类型
	WORD Add_Num;	//具体操作的数值

};

//洗点 暂不使用

/////////////////////////////////////////////////////////////
////  自由加点指令 END
/////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////
////  sky 新镶嵌指令
/////////////////////////////////////////////////////////////

struct stMakeObjectUserCmd : public stNullUserCmd
{
	stMakeObjectUserCmd()
	{
		byCmd = MAKEOBJECT_USERCMD;
	}
};

#define SURPLUS_MOSAIGEM_USERCMD_ADD 1
struct stMosaicGemUserCmd : public stMakeObjectUserCmd
{
	stMosaicGemUserCmd()
	{
		byParam = SURPLUS_MOSAIGEM_USERCMD_ADD;
	}
	stObjectLocation	Epos;	//被镶嵌的装备在包袱中的位置
	stObjectLocation	Gpos;	//要镶嵌的宝石在包袱中的位置
	int					index;	//要镶嵌的孔的下标	
};

/////////////////////////////////////////////////////////////
//// 新镶嵌指令 end
/////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//// sky NPC试图被点击消息
////////////////////////////////////////////////////////////

//sky直接从镶嵌指令里派生算拉免的改头文件很编译很麻烦
#define RT_NPC_DIRITEM_USERCMD_PARA 2
struct stNpcDirItemUserCmd : public stMakeObjectUserCmd{

  stNpcDirItemUserCmd()
  {
    byParam = RT_NPC_DIRITEM_USERCMD_PARA;
  }

  DWORD dwNpcTempID;      /**< 尸体临时编号 */
};

#define RT_NPC_DIRITEM_DATA_USERCMD_PARA 3
struct stNpcDirItemDataUserCmd : public stMakeObjectUserCmd
{
	stNpcDirItemDataUserCmd()
	{
		byParam = RT_NPC_DIRITEM_DATA_USERCMD_PARA;
	}
	struct team
	{
		DWORD tempid;
		char name[MAX_NAMESIZE + 1];
	}fen_team[MAX_TEAM_NUM];

	DWORD		count; //物品个数
	t_Object	objects[0];
}; 

//sky 队长分配给队员物品
#define RT_NPC_GIVEITEM_USERCMD 4
struct stNpcGiveItemUserCmd : public stMakeObjectUserCmd
{
	stNpcGiveItemUserCmd()
	{
		byParam = RT_NPC_GIVEITEM_USERCMD;
	}
	DWORD	UserTemID;	//被分配人的唯一ID
	DWORD	qwThisID;	//被分配物品的唯一ID
};

//sky 客户端告知服务端需要ROLL的物品被拾取的消息
#define RT_TEAM_ROLL_ITEM_START 5
struct stTeamRollItemStartUserCmd : public stMakeObjectUserCmd
{
	stTeamRollItemStartUserCmd()
	{
		byParam = RT_TEAM_ROLL_ITEM_START;
	}
	DWORD itemX;	//要被ROLL的物品的坐标点X
	DWORD itemY;	//要被ROLL的物品的坐标点Y
};

//sky 服务端通知客户端队伍其他成员ROLL物品的消息
#define RT_TEAM_ROLL_ITEM_NOTICE 6
struct stTeamRollItemNoticeUserCmd : public stMakeObjectUserCmd
{
	stTeamRollItemNoticeUserCmd()
	{
		byParam = RT_TEAM_ROLL_ITEM_NOTICE;
	}
	t_Object object;	//被ROLL的物品的数据
};

//sky 客户端告知服务端玩家选择的ROLL方式消息
#define RT_TEAM_ROLL_ITEM_USERTYPE 7
struct stTeamRollItemTypeUserCmd : public stMakeObjectUserCmd
{
	stTeamRollItemTypeUserCmd()
	{
		byParam = RT_TEAM_ROLL_ITEM_USERTYPE;
	}
	BYTE	Rolltype;	//被选中的ROLL选项
};

//sky 制造炮塔的消息
#define RT_MAKE_TURRET_USERCMD 8
struct stMakeTurretUserCmd : public stMakeObjectUserCmd
{
	stMakeTurretUserCmd()
	{
		byParam = RT_MAKE_TURRET_USERCMD;
		dwThisID = 0;
		pos.x = 0;
		pos.y = 0;
	}

	DWORD dwThisID;		//被使用物品的唯一ID
	POINT pos;			//制造点
};

//sky 炮塔升级消息

//sky 客户端通知服务端NPC变身消息
#define RT_NPC_START_CHANGE_USERCMD 9
struct stNpcStartChangeUserCmd : public stMakeObjectUserCmd
{
	stNpcStartChangeUserCmd()
	{
		byParam = RT_NPC_START_CHANGE_USERCMD;
		npcid = 0;
	}

	DWORD npcid;
};


//sky 服务端通知客户端NPC变身成功跟新客户端该NPC的信息
#define RT_NPC_CHANGE_USERCMD 10
struct stNpcChangeUserCmd : public stMakeObjectUserCmd
{
	stNpcChangeUserCmd()
	{
		byParam = RT_NPC_CHANGE_USERCMD;
	}

	t_MapNpcData data;
};

//sky 包袱和仓库购买页的消息
#define PACKE_TYPE 1
#define SAVEBOX_TYPE 2

#define PACK_BUYTAB_NUM_USERCMD 11
struct stPackBuyTanbNumUserCmd : public stMakeObjectUserCmd
{
	stPackBuyTanbNumUserCmd() 
	{ 
		byParam = PACK_BUYTAB_NUM_USERCMD;
		TabNum = 0;
		PackType = 0;
	}
	BYTE PackType;  //sky 被操作的包袱类型(PACKE_TYPE:包裹 SAVEBOX_TYPE:仓库)
	BYTE TabNum;
};

//sky 物品冷却配置消息
#define ITEM_COOL_TIMES_USERCMD 12
struct stItemCoolTimesUserCmd : public stMakeObjectUserCmd
{
	stItemCoolTimesUserCmd(WORD Count = 0)
	{
		byParam = ITEM_COOL_TIMES_USERCMD;
		DataCount = Count;
	}
	WORD DataCount;  //数据个数
};

//sky 物品使用成功
#define ITEN_USEITEM_SUCCESS_USERCMD 13
struct stItemUseItemSuccessUserCmd : public stMakeObjectUserCmd
{
	stItemUseItemSuccessUserCmd()
	{
		byParam = ITEN_USEITEM_SUCCESS_USERCMD;
		ItemID = 0;
	}
	DWORD ItemID;
};

//lxb begin 08.12.09
//队伍所有NPC标志  参考   程序\通讯协议开发目录\黎湘斌.doc
#define TEAM_ALL_NPC_FLAG_USERCMD_PARA 28
struct stTeamAllNPCFlagUserCmd: public stChatUserCmd
{
	stTeamAllNPCFlagUserCmd()
	{
		byParam = TEAM_ALL_NPC_FLAG_USERCMD_PARA;
		memset( dwFlag, 0xff, sizeof( DWORD ) * 10 );
	}
	DWORD dwFlag[10];  //sky 线性标志存放NPC的唯一ID
};

//设置队伍NPC标志  参考   程序\通讯协议开发目录\黎湘斌.doc
#define TEAM_SET_NPC_FLAG_USERCMD_PARA 29
struct stTeamSetNPCFlagUserCmd: public stChatUserCmd
{
	stTeamSetNPCFlagUserCmd()
	{
		byParam = TEAM_SET_NPC_FLAG_USERCMD_PARA;
		nFlag = -1;
		dwNPCID = INVALID_THISID;
	}

	int nFlag;    //sky 被设置的标志
	DWORD dwNPCID; //sky 被设置NPC的唯一ID
};
//lxb end

////////////////////////////////////////////////////////////
//// NPC试图被点击消息 end
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
//// sky 战场-副本-竞技场相关指令
////////////////////////////////////////////////////////////
struct stArenaUserCmd : public stNullUserCmd
{
	stArenaUserCmd()
	{
		byCmd = ARENA_USERCMD;
	}
};

//sky 排队消息
#define ARENA_QUEUING_USERCMD_PARA 1;
struct stArenaQueuingUserCmd : stArenaUserCmd
{
	DWORD UserID;			//sky 用户ID(type为队伍时候该ID为队伍唯一ID)
	BYTE  Type;				//sky 排队类型(0:个人 1:队伍)
	WORD  AddMeType;		//sky 排队的战场类型

	stArenaQueuingUserCmd()
	{
		byParam = ARENA_QUEUING_USERCMD_PARA;
		UserID = 0;
		Type = 0;
		AddMeType = 0;
	}
};
////////////////////////////////////////////////////////////
//// 战场-副本-竞技场相关指令 end
////////////////////////////////////////////////////////////

}
#pragma pack()


#endif