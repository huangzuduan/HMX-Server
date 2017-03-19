#ifndef __SCENECHANNEL_H_
#define __SCENECHANNEL_H_

#include <set>
#include "Single.h"
#include "UnorderedSet.h"


/*------------------------------------------------------------------
 *
 * @Brief : 场景频道定义文件，定义各种注册通信通道
 *
 * @Author: hzd 
 * @Fileanme  : SceneChannel.h
 * @Date  : 2014/09/18 01:31
 * @Copyright (c) 2014,hzd, All rights reserved.
 *-----------------------------------------------------------------*/


/*-------------------------------------------------------------
 * 场景注册接口，需要加入场景的物体，均需要继承该接口
 *------------------------------------------------------------*/
struct IChannelRegist
{
	// 是否注册指定频道 
	virtual bool IsRegist(EChannelRegistType eType) const = 0;
};


/*--------------------------------------------------------------------------------
 * 宏生成：IChannelOperateNotifyType 一个频道抽象结构类
 * 参  数：NotifyType 为一个struct消息传递结构体
 * 用  于：场景中的物体需要该NotifyType消息的广播与接收时，需要继承于该抽象接口
 *-------------------------------------------------------------------------------*/
#define DEF_IChannelOperate(NotifyType)\
template<typename NotifyType>\
struct IChannelOperate##NotifyType\
{\
	FUNCTION_CHANNEL_BROADCAST(NotifyType)\
	FUNCTION_CHANNEL_COLLECT(NotifyType)\
protected:\
	NotifyType m_s##NotifyType;\
};

/*------------------------------------------------
 * 宏生成：场景物体需要NotifyType类型的消息需求
 * 用  于：场景中的物体需要该NotifyType消息的广播与接收时，需要继承于该抽象接口
 *-----------------------------------------------*/
#define IChannelOperate(NotifyType) IChannelOperate##NotifyType<NotifyType>


/*------------------------------------------------------------------
 *
 * @Brief : 频道父类
 *
 * @Author: hzd 
 * @File  : SceneChannel.h
 * @Date  : 2014/09/19 01:36
 * @Copyright (c) 2014,hzd, All rights reserved.
 *-----------------------------------------------------------------*/
class ChannelEx
{
public:

	/*--------------------------------------------
	 *  @brief    :	频道构造：每种频道只能广播一类消息，接收一类消息
	 *  @input	  : ChannelRegistType:广播类型,ChannelRegistType:收集类型
	 *  @return   :	
	 *-------------------------------------------*/
	ChannelEx(EChannelRegistType eBroadcastType, EChannelRegistType eCollectType)
		: m_eBroadcastType(eBroadcastType), m_eReceiveType(eCollectType) {}

	/*------------------------------------------------
	 * 为该频道增加一个接收者
	 *-----------------------------------------------*/
	virtual void RegistReceiver(IChannelRegist& rRegister) = 0;

	/*------------------------------------------------
	 * 为该频道移除一个接收者
	 *-----------------------------------------------*/
	virtual void CancelReceiver(IChannelRegist& rRegister) = 0;
	
	/*------------------------------------------------
	 * 为该频道增加一个广播者
	 *-----------------------------------------------*/
	virtual void RegistBroadcaster(IChannelRegist& rRegister) = 0;

	/*------------------------------------------------
	 * 为该频道移除一个广播者
	 *-----------------------------------------------*/
	virtual void CancelBroadcaster(IChannelRegist& rRegister) = 0;

	/*------------------------------------------------
	 * 刷新消息，收集广播者的消息发给接收着  
	 *-----------------------------------------------*/
	virtual void Update() = 0;

protected:
	const EChannelRegistType		m_eBroadcastType;				// 广播者类型 
	const EChannelRegistType		m_eReceiveType;					// 接着者类型 
};

/*------------------------------------------------------------------
 *
 * @Brief : 场景频道宏定义
 *
 * @Author: hzd 
 * @File  : SceneChannel.h
 * @Date  : 2014/09/18 23:56
 * @Copyright (c) 2014,hzd, All rights reserved.
 *-----------------------------------------------------------------*/
#define DEF_SceneChannel(NotifyType)\
template<typename NotifyType>\
class SceneChannel##NotifyType : public ChannelEx\
{\
public:\
	SceneChannel##NotifyType(EChannelRegistType eBroadcastType, EChannelRegistType eCollectType)\
		: ChannelEx(eBroadcastType, eCollectType)\
	{}\
	virtual void RegistReceiver(IChannelRegist& rRegister)\
	{\
		if (rRegister.IsRegist(m_eBroadcastType))\
		{\
			if (IChannelOperate(NotifyType)* pOperate = dynamic_cast< IChannelOperate(NotifyType) * >(&rRegister))\
			{\
				m_setChannnelReceivers.insert(pOperate);\
			}\
		}\
	}\
	virtual void CancelReceiver(IChannelRegist& rRegister)\
	{\
		if (rRegister.IsRegist(m_eBroadcastType))\
		{\
			if (IChannelOperate(NotifyType)* pOperate = dynamic_cast< IChannelOperate(NotifyType) * >(&rRegister))\
			{\
				m_setChannnelReceivers.erase(pOperate);\
			}\
		}\
	}\
	virtual void RegistBroadcaster(IChannelRegist& rRegister)\
	{\
		if (rRegister.IsRegist(m_eReceiveType))\
		{\
			if (IChannelOperate(NotifyType)* pOperate = dynamic_cast< IChannelOperate(NotifyType) * >(&rRegister))\
			{\
				m_setChannnelBroadcasters.insert(pOperate);\
			}\
		}\
	}\
	virtual void CancelBroadcaster(IChannelRegist& rRegister)\
	{\
		if (rRegister.IsRegist(m_eReceiveType))\
		{\
			if (IChannelOperate(NotifyType)* pOperate = dynamic_cast< IChannelOperate(NotifyType) * >(&rRegister))\
			{\
				m_setChannnelBroadcasters.erase(pOperate);\
			}\
		}\
	}\
	virtual void Update()\
	{\
		std::set<const NotifyType*> setChannnelMsg;\
		{\
			typename std::set< IChannelOperate(NotifyType) * >::const_iterator iter_broadcaster;\
			for (iter_broadcaster = m_setChannnelBroadcasters.begin(); iter_broadcaster != m_setChannnelBroadcasters.end(); ++iter_broadcaster)\
			{\
				const NotifyType* pMsg;\
				(**iter_broadcaster).ChannelCollect(pMsg);\
				setChannnelMsg.insert(pMsg);\
			}\
		}\
		{\
			typename std::set< IChannelOperate(NotifyType) * >::const_iterator iter_receiver;\
			for (iter_receiver = m_setChannnelReceivers.begin(); iter_receiver != m_setChannnelReceivers.end(); ++iter_receiver)\
			{\
				(**iter_receiver).ChannelBroadcast(setChannnelMsg);\
			}\
		}\
	}\
private:\
	std::set< IChannelOperate(NotifyType) * >		m_setChannnelBroadcasters;\
	std::set< IChannelOperate(NotifyType) * >		m_setChannnelReceivers;\
};

/*------------------------------------------------
 * 场景频道宏定义
 *-----------------------------------------------*/
#define SceneChannel(NotifyType) SceneChannel##NotifyType<NotifyType>

/*------------------------------------------------------------------
 *
 * @Brief : 场景频道管理器
 *
 * @Author: hzd 
 * @File  : SceneChannel.h
 * @Date  : 2014/09/18 23:57
 * @Copyright (c) 2014,hzd, All rights reserved.
 *-----------------------------------------------------------------*/
class SceneChannelManager : public Single<SceneChannelManager>
{
public:

	/*--------------------------------------------
	 *  @brief    :	增加一个频道
	 *  @input	  : SceneChannel##NotifyType
	 *  @return   :	无 
	 *-------------------------------------------*/
	void AddSceneChannel(ChannelEx& rChannel);
	
	/*--------------------------------------------
	 *  @brief    :	处理频道update消息
	 *  @input	  : 无
	 *  @return   :	无
	 *-------------------------------------------*/
	void Update();

private:

	/*------------------------------------------------
	 * 频道容器
	 *-----------------------------------------------*/
	UNORDERED_SET<ChannelEx*>		m_usetChannels;
};


/*------------------------------------------------
 * 宏生成位置频道接口
 *-----------------------------------------------*/
DEF_IChannelOperate(ChannelPosition)
DEF_SceneChannel(ChannelPosition)
extern zObjPool< SceneChannel(ChannelPosition) > g_cPositionChannelFactory;		 

/*------------------------------------------------
 * 宏生成生物体频道接口
 *-----------------------------------------------*/
DEF_IChannelOperate(ChannelCreature)
DEF_SceneChannel(ChannelCreature)
extern zObjPool< SceneChannel(ChannelCreature) > g_cCreatureChannelFactory;			

/*------------------------------------------------
 * 宏生成穿着频道接口
 *-----------------------------------------------*/
DEF_IChannelOperate(ChannelWear)
DEF_SceneChannel(ChannelWear)
extern zObjPool< SceneChannel(ChannelWear) > g_cWearChannelFactory;		

/*------------------------------------------------
 * 宏生成技能频道接口
 *-----------------------------------------------*/
DEF_IChannelOperate(ChannelSpell)
DEF_SceneChannel(ChannelSpell)
extern zObjPool< SceneChannel(ChannelSpell) > g_cSpellChannelFactory;		

/*------------------------------------------------
 * 宏生成Buff频道接口
 *-----------------------------------------------*/
DEF_IChannelOperate(ChannelBuff)
DEF_SceneChannel(ChannelBuff)
extern zObjPool< SceneChannel(ChannelBuff) > g_cBuffChannelFactory;		

#endif

