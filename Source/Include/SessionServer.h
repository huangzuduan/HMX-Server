/**
 * \brief 游戏全局会话服务器 
 */
#pragma once
#include <zebra/srvEngine.h>
#include <set>
//需要替换
#include <hash_set>
#include <hash_map>
#include <vector>
#include <map>

//sky 排队系统依赖的类接结构的预申明
struct QueueTeamData;
struct CampData;
class CQueueManager;
class CQueuingManager;
class CArenaManager;

class UserSession;
class SessionTask;

class Recommend;

class CDare;
class CNpcDareObj;

class CQuiz;
class CVoteM;
class CTech;
class CGem;
class CArmy;

class CUnion;
class CUnionMember;

class CSchool;
class CSchoolMember;

class CSept;
class CSeptMember;

//sky 战场等级队列最大最小等级
#define MAX_ARENA_USERLEVEL 60
#define MIN_ARENA_USERLEVEL 10

//sky 跨场景队员临时列表
extern std::map<DWORD, DWORD> MoveSceneMemberMap;
extern zMutex g_MoveSceneMemberMapLock;

//sky 可用战场场景列表
extern std::set<SessionTask *> setBattleTask;

#pragma pack(1)

struct auctionBidInfo
{
  DWORD auctionID;
  DWORD ownerID;
  char owner[MAX_NAMESIZE+1];
  BYTE state;
  DWORD charge;
  DWORD minMoney;
  DWORD maxMoney;
  DWORD minGold;
  DWORD maxGold;
  DWORD bidderID;
  DWORD bidder2ID;
  char bidder[MAX_NAMESIZE+1];
  char bidder2[MAX_NAMESIZE+1];
  DWORD endTime;
  BYTE bidType;
  DWORD itemID;
  Cmd::Session::SessionObject item;
};

#pragma pack()

class AuctionService
{
  private:
    static AuctionService *as;
    AuctionService();
    ~AuctionService();
  public:
    static AuctionService& getMe();
    static void delMe();

    bool doAuctionCmd(const Cmd::Session::t_AuctionCmd *cmd,const DWORD cmdLen);
    void checkDB();

    bool sendAuctionItem(DWORD,DWORD,BYTE,bool);
    void delAuctionRecordByName(char *);

    static bool error(const char * msg,...);
};

#pragma pack(1)

struct mailHeadInfo
{
  DWORD id;
  BYTE state;
  char fromName[MAX_NAMESIZE+1];
  DWORD delTime;
  BYTE accessory;
  BYTE itemGot;
  BYTE type;
};

struct mailContentInfo
{
  DWORD id;
  BYTE state;
  char toName[MAX_NAMESIZE+1];
  char title[MAX_NAMESIZE+1];
  BYTE accessory;
  BYTE itemGot;
  char text[256];
  DWORD sendMoney;
  DWORD recvMoney;
  DWORD sendGold;
  DWORD recvGold;
  DWORD toID;
  Cmd::Session::SessionObject item;
};

struct mailStateInfo
{
  BYTE state;
};

struct mailNewInfo
{
  DWORD id;
  DWORD toID;
};

struct mailCheckInfo
{
  DWORD id;
  char toName[MAX_NAMESIZE+1];
  DWORD toID;
};

struct mailTurnBackInfo
{
  BYTE state;
  char fromName[MAX_NAMESIZE+1];
  char toName[MAX_NAMESIZE+1];
  char title[MAX_NAMESIZE+1];
  BYTE type;
  DWORD createTime;
  DWORD delTime;
  BYTE accessory;
  BYTE itemGot;
  char text[256];
  DWORD recvMoney;
  DWORD recvGold;
  DWORD fromID;
  DWORD toID;
};

struct mailForwardInfo
{
  BYTE state;
  char fromName[MAX_NAMESIZE+1];
  char toName[MAX_NAMESIZE+1];
  BYTE type;
  DWORD delTime;
  char text[256];
  DWORD recvMoney;
  DWORD recvGold;
  DWORD toID;
};

#pragma pack()

class MailService : public Singleton<MailService>
{
  friend class SingletonFactory<MailService>;
  private:
    hash_map<DWORD,hash_set<DWORD> > newMailMap;
    MailService();
  public:
    ~MailService();

    void loadNewMail();
    bool doMailCmd(const Cmd::t_NullCmd *cmd,const DWORD cmdLen);
    bool sendTextMail(char *,DWORD,char *,DWORD,char *,DWORD=(DWORD)-1,BYTE=1);
    bool sendMoneyMail(char *,DWORD,char *,DWORD,DWORD,char *,DWORD=(DWORD)-1,BYTE=1,DWORD=0);
    bool sendMail(Cmd::Session::t_sendMail_SceneSession &);
    bool sendMail(DWORD,Cmd::Session::t_sendMail_SceneSession &);
    bool turnBackMail(DWORD);
    void checkDB();

    void delMailByNameAndID(char *,DWORD);
};

/**
 * \brief 离线消息管理器
 *
 * 提供了对离线消息的管理
 *
 */
class COfflineMessage
{
private:
  static std::string rootpath;
public:

  static bool init();

  static void writeOfflineMessage(const BYTE &type,const DWORD &id,const Cmd::stNullUserCmd *pNullCmd,const DWORD cmdLen);

  static void getOfflineMessage(const UserSession *pUser);

  static void getOfflineMessageSetAndSend(const UserSession *pUser,std::string path);
};

#pragma pack(1)

struct cartoon_load_struct
{
  DWORD cartoonID;        
  Cmd::t_CartoonData data;
  cartoon_load_struct()
  {
    cartoonID = 0;
    bzero(&data,sizeof(data));
  }
};

struct cartoon_relation_struct
{
  DWORD relationID;        
  BYTE type;
};

#pragma pack()

class CartoonPetService
{
  private:
    /*struct key_hash : public std::unary_function<const std::string,size_t>
    {
      size_t operator()(const std::string &x) const
      {
        hash<const char *> H;
        return H(x.c_str());
      }

	  static const int bucket_size = 1000000;
	  static const int min_buckets = 1000000;

    };*/


	//const int key_hash::bucket_size = 10000000;
	//const int key_hash::min_buckets = 10000000;

    hash_map<DWORD,Cmd::t_CartoonData> cartoonPetList;
    hash_set<DWORD> modifyList;
    hash_set<DWORD> waitingList;
    hash_map<DWORD,hash_set<DWORD> > cartoonPetMap;
    hash_map<std::string,hash_set<DWORD>/*,key_hash*/> adoptedPetMap;

    static CartoonPetService *cs;
    CartoonPetService();
    ~CartoonPetService();

    void sendCmdToItsFriendAndFamily(DWORD,const char *,const void *,DWORD,const char * = "");
    void repairData();

    bool loadAllFromDB();
    DWORD group;
  public:
    DWORD writeAllToDB(bool groupflag=true);

    static CartoonPetService& getMe();
    static void delMe();

    bool doCartoonCmd(const Cmd::Session::t_CartoonCmd *cmd,const DWORD cmdLen);
    void loadFromDB(DWORD);
    void checkAdoptable(DWORD);
    bool writeDB(DWORD,Cmd::t_CartoonData&);
    void userLevelUp(DWORD id,DWORD level);

    void delPetRecordByID(DWORD masterID);

    void userOnline(UserSession * pUser);
};

const DWORD KING_CITY_ID = 139;

typedef std::set<DWORD> DareSet;

class CCity
{
  public:
    CCity()
    {
      dwCountry = 0;
      dwCityID = 0;
      dwUnionID = 0;
      isAward = 0;
      dwGold = 20000;
      bzero(catcherName,MAX_NAMESIZE);
      //dwDareUnionID = 0;
      vDareList.clear();
    }
    
    ~CCity()
    {
    }
    
    void init(DBRecord* rec);
    void writeDatabase();
    bool insertDatabase();
    bool isMe(DWORD country,DWORD cityid,DWORD unionid);
    bool changeUnion(DWORD unionid);
    bool changeCatcher(UserSession* pUser);
    bool cancelCatcher();
    bool abandonCity();
    bool addDareList(DWORD dwUnionID);
    bool isDare(DWORD dwUnionID);
    size_t dareSize()
    {
      return vDareList.size();
    }
    
    char* getName();

    void   beginDare();
    void   endDare();  

    DWORD dwCountry;
    DWORD dwCityID;
    DWORD dwUnionID;
    int   isAward;  // 当天的钱，是否已经刷新
    DWORD dwGold;
    char  name[MAX_NAMESIZE + 1];
    char  catcherName[MAX_NAMESIZE + 1];
    
    //DWORD dwDareUnionID;
    DareSet vDareList;
    
    zRWLock rwlock;
};

class CCityM : public Singleton<CCityM>
{
  friend class SingletonFactory<CCityM>;
  public:
    bool init();
    static void destroyMe();

    void timer();

    bool load();
    bool refreshDB();
    void refreshUnion(DWORD dwCountryID,DWORD dwCityID);
    bool addNewCity(Cmd::Session::t_UnionCity_Dare_SceneSession* pCmd);

    
    CCity* find(DWORD country,DWORD cityid,DWORD unionid);
    CCity* find(DWORD country,DWORD cityid);
    CCity* findByUnionID(DWORD unionid);
    CCity* findDareUnionByID(DWORD unionid);
    bool   isCastellan(UserSession* pUser);
    bool   isCatcher(UserSession* pUser);

    void   awardTaxGold(UserSession *pUser);

    struct cityCallback
    {
      virtual void exec(CCity *)=0;
      virtual ~cityCallback(){};
    };

    void execEveryCity(cityCallback &);//不包括无国籍国家   
    
    void beginDare();
                void endDare();
  private:
    CCityM();
    std::vector<CCity*> citys;
    bool isBeging;
    zRWLock rwlock;
};

/// 间隔六十小时以秒为单位的数字
#define MAX_GROUP_TIME_GAP 60*60*60

/// 友好度扣除点数单位为分钟
#define DEDUCT_POINT 5*60

struct CRelation : public zEntry
{
public:
  ///  关系类型 
  BYTE  type;

  ///  关系级别
  WORD  level;

  ///  用户Session对象
//  UserSession *user;
  bool online;

  /// 用户角色ID
  DWORD charid;

  ///  最后更新时间
  DWORD lasttime;

  ///  职业
  WORD  occupation;

  CRelation();
  void sendNotifyToScene();
  bool isOnline();
private:
  /// 读写锁
  //zRWLock rwlock;
};

class CRelationManager : public zEntryMgr<zEntryID,zEntryName>
{
private:
  /// 读写锁
  //zRWLock rwlock;

  /// 用户对象
  UserSession *user;

public:
  ~CRelationManager();
  template <class YourEntry>
  bool execEveryOne(execEntry<YourEntry> &exec)
  {
    //rwlock.rdlock();
    bool ret=execEveryEntry<>(exec);
    //rwlock.unlock();
    return ret;
  }


  void init();
  void loadFromDatabase();
  void deleteDBRecord(const DWORD dwID);
  bool insertDBRecord(const CRelation *);
  void updateDBRecord(const CRelation *relation);
  void updateOtherOfflineUserDBRecord(const CRelation *relation);
  void writeOfflineNotify(const CRelation *relation);
//  void writeDatabase();
  bool processUserMessage(const Cmd::stNullUserCmd *pNullCmd,const DWORD cmdLen);
  void removeRelation(const char *);
  void addBadRelation(const char *name);
  void addEnemyRelation(const char *name);
  inline void sendStatusChange(const CRelation *,const BYTE byState);
  void addRelation(const DWORD dwID,const BYTE type);
  void changeRelationType(const char * name,const BYTE type);
  void sendRelationList();
  void online(const DWORD dwID);
  void offline(const DWORD dwID,const char* name);
  void setUser(UserSession *);
  void sendChatToMyFriend(const Cmd::stChannelChatUserCmd *,const DWORD cmdLen);
  void sendCmdToMyFriend(const void *,const DWORD,bool sendMe=true);
  void sendCmdToMyFriendExcept(const void *,const DWORD,bool sendMe=true,const char * = "");
  void sendPrivateChatToFriend(const Cmd::stChannelChatUserCmd *,const DWORD cmdLen);
  void sendBlackListToGateway(const char *,const BYTE oper);
  void sendAllBlackListToGateway();
  CRelation*  getRelationByType(int relationType);
  CRelation * getRelationByName(const char *);
  CRelation*  getRelationByID(DWORD dwRelationID);
  CRelation*  getMarryRelation();
  void setFriendDegree(Cmd::Session::t_CountFriendDegree_SceneSession *);
  void setFriendDegreeByOtherUser(const DWORD dwUserID,const WORD wdDegree,const DWORD currTime);
};

class SessionChannel : public zEntry
{               
  private:
    std::list<DWORD> userList;
    //char creater[MAX_NAMESIZE + 1];
  public:
    bool sendToOthers(UserSession *pUser,const Cmd::stChannelChatUserCmd *rev,DWORD cmdLen);

    //bool sendToAll(UserSession *,const char *pattern,...);
    bool sendCmdToAll(const void *cmd,int len);
    SessionChannel(UserSession *);
    bool remove(DWORD);
    bool remove(UserSession *pUser);
    bool removeAllUser();
    //bool add(const char *name);
    bool add(UserSession *pUser);
    bool has(DWORD);
    DWORD count();

    static bool sendCountry(DWORD,const void *rev,DWORD cmdLen);
    static bool sendCountryInfo(int type,DWORD countryID,const char* mess,...);
    static bool sendAllInfo(int type,const char* mess,...);
    static bool sendAllCmd(const void *cmd,const DWORD len);
    static bool sendPrivate(UserSession * pUser,const char * fromName,const char* mess,...);
};

typedef zUniqueID<QWORD> zUniqueDWORDID;
class SessionChannelManager : public zEntryMgr< zEntryTempID,zEntryName >
{
  private:
    //std::map<DWORD,SessionChannel *> channelList;
    zUniqueDWORDID *channelUniqeID;
    bool getUniqeID(QWORD &tempid);
    void putUniqeID(const QWORD &tempid);
    static SessionChannelManager * scm;

    SessionChannelManager();
    ~SessionChannelManager();
  public:
    static SessionChannelManager & getMe();
    static void destroyMe();
    bool add(SessionChannel *);
    void remove(DWORD);
    SessionChannel * get(DWORD);
    //void removeUser(DWORD);
    void removeUser(UserSession *);
};

/**
 * \brief 服务器连接任务
 *
 */
class SessionTask : public zTCPTask, public zEntry,public MessageQueue
{

  public:

    /**
     * \brief 构造函数
     *
     * \param pool 所属连接池指针
     * \param sock TCP/IP套接口
     * \param addr 地址
     */
    SessionTask(
        zTCPTaskPool *pool,
        const SOCKET sock,
        const struct sockaddr_in *addr = NULL) : zTCPTask(pool,sock,addr)
    {
      wdServerID = 0;
      wdServerType = UNKNOWNSERVER;
      recycle_state = 0;
    }

    /**
     * \brief 虚析构函数
     *
     */
    virtual ~SessionTask();

    int verifyConn();
    int recycleConn();
    void addToContainer();
    void removeFromContainer();
    bool uniqueAdd();
    bool uniqueRemove();
    bool msgParse(const Cmd::t_NullCmd *,const DWORD);
    bool cmdMsgParse(const Cmd::t_NullCmd *,const DWORD);

    /**
     * \brief 返回服务器编号
     *
     * 编号在一个区中是唯一的，保存在管理服务器中
     *
     * \return 服务器编号
     */
    const WORD getID() const
    {
      return wdServerID;
    }

    /**
     * \brief 返回服务器类型
     *
     * \return 服务器类型
     */
    const WORD getType() const
    {
      return wdServerType;
    }
    bool checkRecycle();

  private:

    /**
     * \brief 服务器编号
     *
     */
    WORD wdServerID;

    /**
     * \brief 服务器类型
     *
     */
    WORD wdServerType;
    ///设置回收标志
    int recycle_state;

    bool verifyLogin(const Cmd::Session::t_LoginSession *ptCmd);

    /**
     * \brief 删除角色的处理
     *
     * 从角色相应的社会关系中把它删除，如果角色是某一社会关系的建立者则不允许删除该角色
     * 如果允许删除，则通知GATEWAY让其从档案中删除。如果不允许删除，则发送一条通知命令给客户端。
     *
     *
     */
    bool del_role(const Cmd::t_NullCmd* cmd,const DWORD cmdLen);
    /**
     * \brief 更换国籍
     *
     * \param dwUserID : 更换国籍的用户ID
     *
     */
    bool SessionTask::change_country(const Cmd::Session::t_changeCountry_SceneSession* cmd);
    bool msgParse_Scene(const Cmd::t_NullCmd *cmd,const DWORD cmdLen);
    bool msgParse_Gate(const Cmd::t_NullCmd *cmd,const DWORD cmdLen);
    bool msgParse_Forward(const Cmd::t_NullCmd *pNullCmd,const DWORD cmdLen);

	//sky 竞技战场副本类Session消息处理函数
	bool msgParse_Arena(const Cmd::t_NullCmd *cmd, const DWORD cmdLen);

};

/**
 * \brief 会话服务器子连接管理器
 *
 */
class SessionTaskManager : private zNoncopyable
{

  public:

    /**
     * \brief 析构函数
     *
     */
    ~SessionTaskManager() {};

    /**
     * \brief 获取子连接管理器唯一实例
     *
     * \return 子连接唯一实例
     */
    static SessionTaskManager &getInstance()
    {
      if (NULL == instance)
        instance = new SessionTaskManager();

      return *instance;
    }

    /**
     * \brief 释放类的唯一实例
     *
     */
    static void delInstance()
    {
      SAFE_DELETE(instance);
    }

    void addSessionTask(SessionTask *task);
    void removeSessionTask(SessionTask *task);
    bool uniqueAdd(SessionTask *task);
    bool uniqueRemove(SessionTask *task);
    bool broadcastGateway(const void *pstrCmd,int nCmdLen);
    bool broadcastScene(const void *pstrCmd,int nCmdLen);
    bool sendCmdToWorld(const void *pstrCmd,int nCmdLen);
    bool broadcastByID(const WORD wdServerID,const void *pstrCmd,int nCmdLen);
    void execEvery();
    bool sendCmdToCountry(DWORD country,const void *pstrCmd,int nCmdLen);

  private:

    /**
     * \brief 类的唯一实例指针
     *
     */
    static SessionTaskManager *instance;

    /**
     * \brief 构造函数
     *
     */
    SessionTaskManager() {};

    /**
     * \brief 定义容器类型
     *
     */
    typedef hash_map<WORD,SessionTask *> SessionTaskHashmap;
    /**
     * \brief 定义容器迭代器类型
     *
     */
    typedef SessionTaskHashmap::iterator SessionTaskHashmap_iterator;
    /**
     * \brief 定义容器常量迭代器类型
     *
     */
    typedef SessionTaskHashmap::const_iterator SessionTaskHashmap_const_iterator;
    /**
     * \brief 定义容器键值对类型
     *
     */
    typedef SessionTaskHashmap::value_type SessionTaskHashmap_pair;
    /**
     * \brief 定义容器类型
     *
     */
    typedef std::list<SessionTask *> TaskContainer;
    /**
     * \brief 定义容器迭代器类型
     *
     */
    typedef TaskContainer::iterator TaskContainer_iterator;
    /**
     * \brief 容器访问互斥变量
     *
     */
    zRWLock rwlock;
    //zMutex mlock;
    /**
     * \brief 声明一个容器，存放所有的子连接
     *
     */
    SessionTaskHashmap sessionTaskSet;
    /**
     * \brief 与场景服务器连接的链表
     *
     */
    TaskContainer sceneTaskList;
    /**
     * \brief 与网关服务器连接的链表
     *
     */
    TaskContainer gatewayTaskList;

};


/**
 * \brief 会话类
 * 用户会话和场景会话的基类
 *
 */
class Session:private zNoncopyable
{

  private:
    ///创建时间
    time_t createtime;
    ///该会话的连接
    SessionTask *task;

  protected:

    /**
     * \brief 构造函数
     * \param task 该会话的连接
     */
    Session(SessionTask *task)
    {
      createtime=time(NULL);
      this->task=task;
    }

  public:
    ///请求领养过的人
    DWORD reqAdopter;

    /**
     * \brief 得到该会话的连接
     * \return 该会话的连接
     */
    SessionTask *  getTask() const
    {
      return task;
    }
    
    /**
     * \brief 向对方发送消息
     * \param pstrCmd 要发送的消息
     * \param nCmdLen 消息长度
     * \return 发送是否成功
     */
    bool sendCmd(const void *pstrCmd,const int nCmdLen) const
    {
      if (task)
        return task->sendCmd(pstrCmd,nCmdLen);
      else
        return false;
    }

};

/**
 * \brief 场景会话
 *
 */
class SceneSession:public zScene,public Session
{

  public:

    ///当前地图允许的最低玩家等级为0表示不限制
    BYTE level;
    /**
     * \brief 构造函数
     */
    SceneSession::SceneSession(SessionTask *task):zScene(),Session(task)
    {
    }

    /**
     * \brief 通过消息注册一个地图
     * \param reginfo 地图注册消息
     * \return 是否注册成功
     */
    bool SceneSession::reg(Cmd::Session::t_regScene_SceneSession *reginfo)
    {
      if (reginfo)
      {
        id=reginfo->dwID;
        tempid=reginfo->dwTempID;
        strncpy(name,(char *)reginfo->byName,MAX_NAMESIZE);
        file = reginfo->fileName;
        level = reginfo->byLevel;
        return true;
      }
      else
        return false;
    }

    ///对应的地图文件名
    std::string file;
};

/**
 * \brief 用户会话类
 *
 */
class UserSession:public zUser,public Session
{

  public:
    //std::set<DWORD> cartoonList;
    //std::set<DWORD> adoptList;

    char autoReply[MAX_CHATINFO];//自动回复

    //测试
    static DWORD user_count;

    //国家排序
    static std::map<DWORD,DWORD> country_map;

    ///帐号id
    DWORD accid;
    ///帮会id
    DWORD unionid;
    ///国家id
    DWORD country;
    /// 国家名称
    BYTE countryName[MAX_NAMESIZE+1];
    ///家族id
    DWORD septid;
    ///门派id
    DWORD schoolid;
    ///队伍临时id
    DWORD teamid;
    ///等级
    WORD  level;
    ///帮会职位
    WORD  occupation;
    /// 在线时间
    zRTime regTime;
    ///头像
    DWORD  face;
    
    // 功勋值
    DWORD dwExploit;

    // 换成职业
    DWORD dwUseJob;

    // 人物当前经验
    QWORD qwExp;

    ///系统设置信息
    BYTE sysSetting[20];//系统设置

    ///所在的场景会话
    SceneSession *scene;
    ///社会关系处理器
    CRelationManager relationManager;

    ///下次放烟火的时间
    zRTime nextBlessTime;

    //家族经验
    WORD septExp;


    UserSession(SessionTask *task);
    ~UserSession();

    /**
     * \brief 根据注册一个玩家
     * \param reginfo 存放玩家信息的消息
     * \return 是否注册成功
     */
    bool reg(Cmd::Session::t_regUser_GateSession *reginfo)
    {
      if (reginfo)
      {
        accid=reginfo->accid;
        id=reginfo->dwID;
        tempid=reginfo->dwTempID;
        //TODO septid 初始化
        level=reginfo->wdLevel;
        occupation=reginfo->wdOccupation;
        country = reginfo->wdCountry;
        std::map<DWORD,DWORD>::iterator iter = country_map.find(country);
        if (iter == country_map.end())
        {
          country_map[country] = 0;
        }
        country_map[country]++;
        strncpy(name,(char *)reginfo->byName,MAX_NAMESIZE);
        strncpy((char*)countryName,(char*)reginfo->byCountryName,MAX_NAMESIZE);
        relationManager.setUser(this);
        return true;
      }
      else
        return false;
    }
    static void getCountryUser(std::vector<std::pair<DWORD,DWORD> > &v)
    {
      std::map<DWORD,DWORD>::iterator iter;
      for( iter = country_map.begin() ; iter != country_map.end() ; iter ++)
      {
        v.push_back( std::make_pair(iter->first,iter->second) );
      }
    }

    /**
     * \brief 设置社会关系信息
     * \param regsuccess 注册成功的消息
     * \return 
     */
    bool setRelationData(const Cmd::Session::t_regUserSuccess_SceneSession *regsuccess)
    {
      if (regsuccess)
      {
        unionid  = regsuccess->dwUnionID;
        country = regsuccess->dwCountryID;
        septid = regsuccess->dwSeptID;
        schoolid = regsuccess->dwSchoolID;
        return true;
      }
      else
        return false;
    }

    /**
      * \brief 更新配偶信息到场景
      *
      */
    void updateConsort();
    
    /**
      * \brief 更新配偶信息到场景
      *
      */
    void updateCountryStar(); 

    bool checkChatCmd(const Cmd::stNullUserCmd *,const DWORD nCmdLen) const;
    void sendCmdToMe(const void *pstrCmd,const DWORD nCmdLen) const;
    void sendSysChat(int type,const char *pattern,...) const;
    void sendGmChat(int type,const char* pattern,...) const;
    void setFriendDegree(Cmd::Session::t_CountFriendDegree_SceneSession *);
    void sendFriendDegree(Cmd::Session::t_RequestFriendDegree_SceneSession *);
    bool forwardScene(const Cmd::stNullUserCmd *pNullCmd,const DWORD nCmdLen);
};

/**
 * \brief 用户会话管理器
 *
 */
class UserSessionManager:public zUserManager
{
  private:
    ///管理器实例
    static UserSessionManager *sm;

    ///是否初始化成功
    bool inited;

    UserSessionManager();
    ~UserSessionManager();
    inline bool getUniqeID(QWORD &tempid);
    inline void putUniqeID(const QWORD &tempid);

  public:
    static UserSessionManager *getInstance();
    static void delInstance();
    struct Compare
    {
      virtual bool operator ()(UserSession*) = 0;
      virtual ~Compare(){}
    };

    bool init();
    void final();
    UserSession *getUserSessionByName( const char * name);
    UserSession *getUserByTempID(DWORD tempid);
    UserSession *getUserByID(DWORD id);
    void sendGraceSort(UserSession* pUser);
    void sendExploitSort(UserSession* pUser);
    void sendCmdByCondition(const Cmd::stNullUserCmd *pstrCmd,const DWORD nCmdLen,Compare* compare);
	void removeAllUserByTask(SessionTask *task);
	void notifyOnlineToGate(); // [ranqd Add] 通知所有GateWay当前的国家在线情况，因资源消耗比较大，5分钟调用一次
};


/**
 * \brief 场景会话管理器
 *
 */
class SceneSessionManager:public zSceneManager
{
  private:
    ///管理器实例
    static SceneSessionManager *sm;

    ///是否初始化成功
    bool inited;

    SceneSessionManager();
    ~SceneSessionManager();
    bool getUniqeID(QWORD &tempid);
    void putUniqeID(const QWORD &tempid);

  public:
    static SceneSessionManager *getInstance();
    static void delInstance();

    bool init();
    void final();

    bool addScene(SceneSession *scene);
    SceneSession * getSceneByName(const char *name);
    SceneSession * getSceneByFile(const char *file);
    SceneSession * getSceneByID(DWORD id);
    SceneSession * getSceneByTempID(DWORD tempid);
    void removeAllSceneByTask(SessionTask *task);
    void removeScene(SceneSession *scene);
    void notifyCountryTax(DWORD dwCountry,BYTE byTax);

};

class zDBConnPool;
class DBMetaData;

/**
 * \brief 遍历每个用户会话给同一国家的角色发送到场景
 */
struct OneCountryScene: public execEntry<UserSession>
{
  DWORD country;
  DWORD cmdLen;
  Cmd::t_NullCmd* sendCmd;

  void init(Cmd::t_NullCmd * rev,DWORD len,DWORD countryID)
  {
    sendCmd = rev;
    cmdLen = len;

    country = countryID;
  }

  /**
   * \brief 遍历每个用户会话给同一国家的角色发送场景命令
   * \param su 用户会话
   * \return true 成功 false 失败
   */
  bool exec(UserSession *su)
  {
    if (country == su->country && su->scene)
    {
      if (sendCmd->para == Cmd::Session::PARA_ENTERWAR)
      {
        ((Cmd::Session::t_enterWar_SceneSession*)sendCmd)->dwUserID = su->id;
      }
      
      su->scene->sendCmd(sendCmd,cmdLen);
    }
    return true;
  }
};

struct worldMsg
{
  char msg[256];
  DWORD time;
  DWORD interval;
  DWORD count;
  DWORD country;
  DWORD mapID;
  char GM[32];
  worldMsg()
  {
    bzero(msg,sizeof(msg));
    time = 0;
    interval = 0;
    count = 0;
    country = 0;
    mapID = 0;
    bzero(GM,sizeof(GM));
  }
};

/**
 * \brief Session服务类
 *
 * 游戏全局的会话服务器
 *
 */
class SessionService : public zSubNetService
{

  public:

    bool msgParse_SuperService(const Cmd::t_NullCmd *pNullCmd,const DWORD nCmdLen);

    /**
     * \brief 纯虚析构函数
     *
     */
    ~SessionService()
    {
      instance = NULL;

      //关闭线程池
      if (taskPool)
      {
        taskPool->final();
        SAFE_DELETE(taskPool);
      }
    }

    const int getPoolSize() const
    {
      if(taskPool)
      {
        return taskPool->getSize();
      }
      else
      {
        return 0;
      }
    }

    /**
     * \brief 获取类的唯一实例
     *
     * 这个类使用了Singleton，保证一个进程中只有一个类的实例
     *
     * \return 类的唯一实例
     */
    static SessionService &getInstance()
    {
      if (NULL == instance)
        instance = new SessionService();

      return *instance;
    }

    /**
     * \brief 释放类的唯一实例
     *
     */
    static void delInstance()
    {
      SAFE_DELETE(instance);
    }

    void reloadConfig();
    bool isSequeueTerminate() 
    {
      return taskPool == NULL;
    }
    
    /**
     * \brief 指向数据库连接池实例的指针
     *
     */
    static zDBConnPool *dbConnPool;
    static DBMetaData* metaData;
    bool checkShutdown();
    //bool checkGumu();

    /**
     * \brief 检查国家强弱
     *
     */
    void checkCountry(struct tm &tmValue,bool donow = false);
    Cmd::Session::t_shutdown_SceneSession shutdown_time;
    
    static std::map<BYTE,worldMsg> wMsg;
    //static DWORD snCount;
    static std::map<DWORD,BYTE> userMap;
    DWORD countryLevel[13];
    bool uncheckCountryProcess;

    static bool reportGm(const char * fromName,const char *msg,...);

    static DWORD emperorForbid[10];//皇帝禁言过的玩家
    DWORD loadEmperorForbid();//从数据库读
    void saveEmperorForbid();//写数据库
    void clearEmperorForbid();//每天清除记录
  private:

    DWORD gumutime;
    /**
     * \brief 类的唯一实例指针
     *
     */
    static SessionService *instance;

    zTCPTaskPool *taskPool;        /**< TCP连接池的指针 */

    /**
     * \brief 构造函数
     *
     */
    SessionService() : zSubNetService("会话服务器",SESSIONSERVER)
    {
      taskPool = NULL;
      bzero(&shutdown_time,sizeof(shutdown_time));
      gumutime=0;
    }

    bool init();
    void newTCPTask(const SOCKET sock,const struct sockaddr_in *addr);
    void final();
};

//enum
//{
//  SILK_TECH=1, // '布料类服装'
//  SKIN_TECH=2, // '皮甲类服装'
//  LORICAE_TECH=3,  // '铠甲类服装'
//  SWORD_TECH=4,  // '刀盾类'
//  BOW_TECH=5,  // '弓类'
//  WAND_TECH=6,  // '棍类'
//  STAFF_TECH=7,  // '杖类'
//  FAN_TECH=8,  // '扇类'
//  NECKLACE_TECH=9,  // '项链类'
//  FINGER_TECH=10,  // '戒指类'
//  CUFF_TECH=11,  // '护腕类'
//  GIRDLE_TECH=12,  // '腰带类'
//  SHOES_TECH=13,  // '鞋子类'
//  ARMET_TECH=14,  // '头盔类'
//};

const int TECH_MAX_NUM = 15; // 科技的最大数目
const int COUNTRY_MATERIAL = 0; // 国家仓库中的物资
const int COUNTRY_STOCK = 1;  // 国家仓库中的原料 
const int COUNTRY_MONEY = 2; // 国家仓库中的银两
const int COUNTRY_ALLY_NPC_HORTATION_MONEY = 40 * 10000; // 40 锭
const int COUNTRY_ALLY_NPC_HORTATION_MATERIAL = 1000; // 1000个单位的物资
const DWORD NEUTRAL_COUNTRY_ID = 6; // 中立国ID

class CTech
{
  public:
    enum 
    {
      INIT_TECH, // 初始状态
      WAIT_TECH, // 投票选出的科技,等待国王选择官员
      ACTIVE_TECH,   // 正在进行升级
      FINISH_TECH, // 已经完成升级,可以打造相应装备(包括等级大于0的所有状态的科技)
    };
    
    CTech();
    ~CTech();

    void init(DBRecord* rec);
    void writeDatabase();
    void upLevel(UserSession* pUser);
    void setSearcher(UserSession* pUser);
    void clearSearcher(UserSession* pUser);
      
    DWORD state()
    {
      return this->dwStatus;
    }

    void state(DWORD newState)
    {
      rwlock.wrlock();
      this->dwStatus = newState;
      rwlock.unlock();
      this->writeDatabase();
    }

    DWORD type()
    {
      return this->dwType;
    }


    DWORD level()
    {
      return this->dwLevel;
    }

    DWORD dwUID;
    DWORD dwCountryID;
    DWORD dwType;
    char  szName[MAX_NAMESIZE + 1];
    DWORD dwProgress;
    DWORD dwResearchID;
    char  szResearchName[MAX_NAMESIZE + 1];
    DWORD dwStatus;
    DWORD dwLevel;
    DWORD dwLastUpTime;

    zRWLock rwlock;
};

class CCountry
{
  public:
    CCountry()
    {
      dwID = 0;
      dwKingUnionID = 0;
      dwLastDareTime = 0;
      dwLastDailyMoney = 0;
      dwDareTime = 0;
      dwDareCountryID = 0;
      bzero(name,sizeof(name));
      bzero(kingName,sizeof(kingName));
      dwFormalWin = 0;
      dwFormalFail  = 0;
      dwAnnoyWin = 0;
      dwAnnoyFail = 0;
      dwStar   = 0;
      dwTax = 0;  ///税率
      qwGold = 0;  ///国库
      isBeging = false;
      qwSilk  =  0;  // 丝线
      qwOre  =  0;  // 矿石
      qwBowlder  =  0;  // 玉石
      qwWood  =  0;  // 木材
      qwCoat  =  0;  // 皮毛
      qwHerbal  =  0;  // 草药
      qwMaterial  =  0; // 物资
      qwStock    =  0; // 原料
      forbidTalk  =  0; //禁言
      winner_exp = 0;
      winner_time = 0;
      bzero(note,sizeof(note));
      sendPrison = 0;
      gen_level = 0;
      gen_exp = 0;
      gen_maxexp = 0;
      gen_refreshTime = 0;
      calltimes = 0;
      kingtime = 0;
    }
    
    ~CCountry()
    {
    }
    
    void init(DBRecord* rec);
    void writeDatabase();
    void loadTechFromDB();

    bool insertDatabase();
    bool isMe(DWORD country);
    bool isKing(UserSession* pUser);
    bool isOfficial(UserSession* pUser);

    bool changeKing(UserSession* pUser);
    bool changeEmperor(DWORD dwCountryID);
    void updateKing(UserSession* pUser);
    bool changeDiplomat(UserSession* pUser);// 改变外交官
    bool cancelDiplomat(); // 罢免外交官
    
    bool changeCatcher(UserSession* pUser);// 改变捕头
    bool cancelCatcher(); // 罢免外交官

    void beginDare();
    void beginAntiDare(DWORD dwAttCountry);
    void endDare();


    void addTaxMoney(QWORD qwTaxMoney);
    
    /// 开始进行科技投票
    void beginTechVote();

    DWORD dwID;
    DWORD dwKingUnionID;
    DWORD dwDareTime;  // 上次发起挑战的时间
    DWORD dwLastDareTime;   // 上次接受挑战的时间
    DWORD dwLastDailyMoney; // 皇帝上次领取5D奖励的时间
    DWORD dwDareCountryID;
    bool  isBeging;

    char  name[MAX_NAMESIZE+1]; // 国家名称
    char  kingName[MAX_NAMESIZE+1]; // 国王名称
    char  diplomatName[MAX_NAMESIZE+1]; // 外交官名称
    char  catcherName[MAX_NAMESIZE+1]; // 捕头名称
    
    DWORD dwFormalWin;
    DWORD dwFormalFail;
    DWORD dwAnnoyWin;
    DWORD dwAnnoyFail;
    DWORD dwStar;
    DWORD dwTax;  ///税率
    QWORD qwGold;  ///国库
    QWORD qwSilk;  // 丝线
    QWORD qwOre;  // 矿石
    QWORD qwBowlder;  // 玉石
    QWORD qwWood;  // 木材
    QWORD qwCoat;  // 皮毛
    QWORD qwHerbal;  // 草药
    QWORD qwMaterial; // 物资
    QWORD qwStock;  // 原料
    DWORD forbidTalk; //国王禁言
    DWORD sendPrison; //国王关监狱
    DWORD gen_level; //大将军的等级
    DWORD gen_exp; //大将军的经验
    DWORD gen_maxexp; //大将军的最大经验
    DWORD gen_refreshTime;//大将军复活的时间
    DWORD calltimes;  //令牌使用次数
    DWORD kingtime;    //国王在位时间(小时)

    char note[256];

    void  changeStar(int star); // 改变量
    DWORD getStar();

    /// 改变指定类型物资的百分比,0为普通物资,1原料,2为银子
    /// 返回值为,具体的改变值
    int changeMaterialByPer(int type,float per);
    // 改变指定类型物资的数值
    void  changeMaterial(int type,int value);
    // 得到指定类型的物资
    QWORD getMaterial(int type);
    void swapMaterialByPer(CCountry* pToCountry,float per);

    /// 科技索引
    typedef std::map<DWORD,CTech*> CTechMap;
    CTechMap techIndex;
    CTech* getTech(DWORD dwType);
    void   addTech(DWORD dwType,CTech* pTech);
  
    zRWLock rwlock;
    void setWinnerExp();
    void checkWinnerExp();

    void addGeneralExp(DWORD num);
    void generalLevelDown();
    void refreshGeneral();
  private:
    bool winner_exp;
    DWORD winner_time;
};

class CCountryM : public Singleton<CCountryM>
{
  friend class SingletonFactory<CCountryM>;
  public:
    bool init();
    static void destroyMe();

    void timer();
    void timerPerHour();
    void save();
    void beginDare();
    void endDare();

    void resetCallTimes();
    void beginGem();
    bool load();
    bool refreshDB();
    bool processUserMessage(UserSession *pUser,const Cmd::stNullUserCmd *pNullCmd,const DWORD cmdLen);
    bool processSceneMessage(const Cmd::t_NullCmd *pNullCmd,const DWORD cmdLen);

    void processRequestDare(UserSession* pUser,Cmd::stRequestDareCountryCmd* rev);
    void processDareCountry(UserSession* pUser,Cmd::stDareCountryFormalCmd* rev);
    void processAntiDareCountry(UserSession* pUser,Cmd::stAntiDareCountryFormalCmd* rev);
    void processRequestTech(UserSession* pUser,Cmd::stReqTechUserCmd* rev);
    void processUpTech(UserSession* pUser,Cmd::stUpTechDegreeUserCmd* rev);
    void processSetTechSearch(UserSession* pUser,Cmd::stSetTechSearchUserCmd* rev);
    void processConfirmSearcher(UserSession* pUser,Cmd::stConfirmSearcherUserCmd* rev);
    void processReqWaitOfficial(UserSession* pUser,Cmd::stReqWaitOfficialUserCmd* rev);
    void processCancelTechSearch(UserSession* pUser,Cmd::stCancelTechSearchUserCmd* rev);
    void processReqDailyEmperorMoney(UserSession* pUser,Cmd::stReqDailyEmperorMoneyCmd* rev);
    void processSetDiplomat(UserSession* pUser,Cmd::stAppointDiplomatCmd* rev);
    void processSetCatcher(UserSession* pUser,Cmd::stAppointCatcherCmd* rev);
    void processCancelDiplomat(UserSession* pUser,Cmd::stCancelDiplomatCmd* rev);
    void processCancelCatcher(UserSession* pUser,Cmd::stCancelCatcherCmd* rev);
    
    CCountry* addNewCountry(DWORD country);

    CCountry* find(DWORD country,DWORD unionid);
    CCountry* find(DWORD country);
    CCountry* findByDare(DWORD country,bool findDare = true);

    struct countryCallback
    {
      virtual void exec(CCountry *)=0;
      virtual ~countryCallback(){};
    };
    void execEveryCountry(countryCallback &);//不包括无国籍国家
    void userOnline(UserSession * pUser);
    void refreshTax();
    void refreshTech(SessionTask* scene,DWORD dwCounryID);

    void broadcastTech(DWORD dwCountryID);

    bool isKing(UserSession* pUser);
    bool isEmperor(UserSession* pUser);
    bool isOfficial(UserSession* pUser);

    void refreshGeneral(DWORD country);
  private:
    void clearForbid();
    void clearDiplomat();
    void clearCatcher();
    DWORD clearForbidTime;
    CCountryM();
    std::vector<CCountry*> countries;
    bool isBeging;
      
    zRWLock rwlock;
};

using namespace UnionDef;

class CUnionM:public zEntryMgr<zEntryID,zEntryName>,
        public Singleton<CUnionM>
{
  friend class SingletonFactory<CUnionM>;
  private:
    /// 成员索引
    std::map<std::string,CUnionMember*> memberIndex;

    /// 类型定义
    typedef std::map<std::string,CUnionMember*>::value_type memberIndexValueType;

    /// 读写锁
    zRWLock rwlock;

    CUnion *  createUnionAndAddMaster(const stUnionInfo&);
    bool     initAddUnionMember(const DWORD &,const stUnionMemberInfo &,bool notify = false);
    bool    createUnionDBRecord(stUnionInfo &info);
    void    removeEntryByName(const char * name);
    CUnion*    createUnionByDBRecord(const stUnionInfo & info);
    inline std::map<std::string,CUnionMember *>::iterator  findMemberIndex(const char *pName);
    CUnionM();

  public:
    ~CUnionM();
    template <class YourEntry>
    bool execEveryOne(execEntry<YourEntry> &exec)
    {
      rwlock.rdlock();
      bool ret=execEveryEntry<>(exec);
      rwlock.unlock();
      return ret;
    }

    template <class YourEntry>
    void removeOne_if(removeEntry_Pred<YourEntry> &pred)
    {
      rwlock.wrlock();
      removeEntry_if<>(pred);
      rwlock.unlock();
    }

    CUnion * getUnionByName( const char * pName);
    CUnion* getUnionByID(DWORD dwUnionID);

    bool init();
    static void destroyMe();

    void fireUnionMember(UserSession*,const char *);

    /**
      * \brief 删除帮会成员
      *
      * 如果该角色不是帮会会长，则踢除他，如果是，则保留，不做处理
      *
      * \param dwUserID 角色ID
      * \param find     是否为查找
      *
      * \return 如果该角色不在任何帮会中，则返回2
      *         如果该角色是帮主，则返回0
      *         如果该角色是帮众，并删除成功，则返回1
      *
      */
    int  fireUnionMember(DWORD dwUserID,bool find);

    bool addNewMemberToUnion(const DWORD dwUnionID,const stUnionMemberInfo&);
    void addNewSeptToUnion(const DWORD dwUnionID,const DWORD dwSeptID);
    
    void userOnline(UserSession *);
    void userOffline(const UserSession *);
    void createNewUnion(Cmd::Session::t_addUnion_SceneSession *data);
    bool addMemberIndex(const char *,CUnionMember *);
    bool removeMemberIndex(const char *);
    bool processUserMessage(UserSession *pUser,const Cmd::stNullUserCmd *pNullCmd,const DWORD cmdLen);
    void processUnionSortMessage(UserSession* pUser,const Cmd::stReqUnionSort* ptCmd);
    void processAppointCityCatcherMessage(UserSession* pUser,const Cmd::stAppointCityCatcherCmd* ptCmd);
    void processCancelCityCatcherMessage(UserSession* pUser,const Cmd::stCancelCityCatcherCmd* ptCmd);

    bool processSceneMessage(const Cmd::t_NullCmd *pNullCmd,const DWORD cmdLen);
    bool processSceneUnionMessage(const Cmd::t_NullCmd *pNullCmd,const DWORD cmdLen);
    
    bool processGateMessage(const Cmd::t_NullCmd *cmd,const DWORD cmdLen);
    void delUnion(const DWORD dwUnionID);
    void processMemberLeave(const DWORD dwUnionID,const DWORD dwCharID);
    void processMemberPower(UserSession* pUser,const Cmd::stUnionMemberPower* ptCmd);
    bool havePowerByName(const char* name,const int power);

    void sendUnionNotify(const DWORD unionID,const char* message,...);

    void sendUnionChatMessages(const UserSession *pUser,const Cmd::stChannelChatUserCmd *,const DWORD cmdLen);
    void sendUnionPrivateChatMessages(const UserSession *pUser,const Cmd::stChannelChatUserCmd *,const DWORD cmdLen);
    void sendVoteListToUser(const UserSession *pUser);
    void sendListToUser(const UserSession *pUser);
    void sendDareListToUser(const UserSession* pUser);
    
    void userVote(const UserSession *pUser,const char *pName);
    void userAboutVote(const UserSession *pUser,const char *pName);
    void addVoteMemberToUnion(const UserSession *pUser,const char *pName);
    void setUnionNote(UserSession *pUser,Cmd::stNoteUnionCmd *pCmd);


    /**
     * \brief 更改别名
     *
     * \param pUser 请求更名者(目前只能是帮主)
     *
     * \param pCmd 更名命令
     *
     * \return 
     */
    void change_aliasname(UserSession *pUser,Cmd::stChangeUnionMemberAliasName* pCmd);
    void delAllUnion(DWORD id);


    /**
     * \brief 时间回调函数
     */
    void timer();
    char * getUnionNameByUserName(char *Name);
    DWORD getCountryIDByUserName(char *Name);
};

class CUnion:public zEntryMgr<zEntryID,zEntryName>,public zEntry
{
  private:
    /// 帮会级别
    WORD                  level;

    /// 帮会经验
    DWORD                 exp;

    /// 毁灭状态不再执行写库等操作
    bool          destroy;

    /// 是否还处于投票期间，1为是0为否
    BYTE          byVote;

  
       /// 读写锁
    zRWLock rwlock;

  public:
    /// 帮会会长
    CUnionMember          *master;
    /// 创立时间
    DWORD          dwCreateTime;
    /// 介绍
    char    note[255];

    /// 帮会所属国家ID
    DWORD dwCountryID;

    /// 帮会威望
    DWORD dwMana;

    // 当前行动力
    DWORD dwActionPoint;

    // 帮会资金（银两）
    DWORD dwMoney;
    DWORD calltimes;

    DWORD getActionPoint();//得到行动力
    bool  changeActionPoint(int repute);//改变行动力
    
    DWORD getMoney();//得到帮会资金
    bool  changeMoney(int money);//改变帮会资金

    void sendUnionDare(UserSession* pUser,const char* fromName,DWORD dwWarID);

    template <class YourEntry>
    bool execEveryOne(execEntry<YourEntry> &exec)
    {
      rwlock.rdlock();
      bool ret=execEveryEntry<>(exec);
      rwlock.unlock();
      return ret;
    }

    template <class YourEntry>
    void removeOne_if(removeEntry_Pred<YourEntry> &pred)
    {
      rwlock.wrlock();
      removeEntry_if<>(pred);
      rwlock.unlock();
    }

    CUnion();
    ~CUnion();
    void      removeEntryByName(const char * name);
    DWORD      getID() {return id;}
    void      init(const stUnionInfo & info);
    CUnionMember *  addUnionMember(const stUnionMemberInfo&);
    CUnionMember *  addUnionMaster(const stUnionInfo& info);
    void      changeMaster(CUnionMember* pMember);
    void      sendUserUnionData(const char *pName);
    void      fireUnionMember(const char *,const char *);
    int      fireUnionMemberDirect(const DWORD dwCharID,const bool checksept=true);
    void       fireSeptFromUnion(const DWORD dwSeptID);

    void      sendCmdToAllMember(const Cmd::stNullUserCmd * ptCmd,const DWORD nCmdLen );
    void       sendCmdToAllMemberScene(Cmd::Session::t_enterWar_SceneSession* ptEnterWarCmd,const DWORD cmdLen);
    void      sendCallCmdToAllMemberScene(Cmd::Session::t_GoTo_Leader_Check_SceneSession* ptEnterWarCmd,const DWORD cmdLen,DWORD expect);
    void      notifyMemberFire(const char *,const char *);
    void                notifyWarResult(const char* msg,...);
    void      writeDatabase();
    void      sendUnionMemberList(UserSession *pUser);
    void      sendUnionInfoToUser(UserSession *pUser);
    bool      deleteMeFromDB();
    void       sendUnionNotify(const char* message,...);

    bool      isMember(DWORD dwUserID);

    void      disbandUnion();
    void      delUnion(const DWORD dwUnionID);
    bool      loadUnionMemberFromDB();
    DWORD      size();
    bool      isVote();
    void      letVoteOver();    
    void      setNote(Cmd::stNoteUnionCmd *pCmd);
  
    void      sendUnionInfoToAll();
    void      sendUnionManaToAll();
    // 判断能否解散帮会
    bool      isDel();

    // 统计本帮有几个家族
    DWORD       septSize();

    void       changeAllSeptRepute(int repute);
  
    // 刷新该帮会所有家族经验领取标志  
    void       refreshSeptExp();


    // 获得帮会威望
    DWORD      getMana();
    
    // 更新所有成员数据到场景  
    void       update_all_data();

    // 处理一个成员的直接离开
    void    fireUnionMemberLeave(DWORD dwUserID);  
};

struct CUnionMember:public zEntry
{
public:

    /// 会员别名
    char  aliasname[MAX_NAMESIZE+1];
    /// 会员权限
    BYTE  byPower[2];

    /// 会员状态
    BYTE  byStatus;

    /// 会员职业
    WORD  wdOccupation;

    /// 会员所属家族
    DWORD septid;

    /// 用户的会话对象
    //UserSession * user;

    /// 帮会管理器对象指针
    CUnion *myUnion;

    /// 毁灭状态不再执行写库等操作
    bool  destroy;
    
    /// 互斥锁
    zRWLock rwlock;

    /// 在线标志枚举
    enum {
          Offline,
          Online
    };


    void init(const stUnionMemberInfo&);
    void getMemberBaseInfo(struct Cmd::stUnionRember& info);
    void sendUserUnionPrivateData();
    void sendUnionDare(UserSession* pDareUser,const char* fromName,DWORD dwWarID);
    void sendCmdToMe(const Cmd::stNullUserCmd *pstrCmd,const DWORD nCmdLen);
    void writeDatabase();
    void insertDatabase();
    void setUnion(CUnion * pUnion);
    void online(const DWORD status = Cmd::UNION_MEMBER_STATUS_ONLINE);
    bool isOnline();
    void offline();
    bool havePower(const int power);
    void setPower(const int power);
    void sendMessageToMe(const char *);
    void fireMe(const bool notify = true,const bool checksept = true);
    bool deleteMeFromDB();
    void sendUserUnionData();
    void change_aliasname(const char* aliasname);
    void update_data();
      
    CUnionMember();
    ~CUnionMember();
    
};

class DBRecord;
class SessionTask;
const int CREATE_ALLY_NEED_MONEY = 200000; // 20锭

class CAlly
{
  public:
    CAlly();
    ~CAlly();

    void init(DBRecord* rec);
    void writeDatabase();
    bool insertDatabase();
    bool deleteMeFromDB();

    bool changeFriendDegree(int degree);
    void refreshAlly(bool isFire = false);
    void refreshAllyToAllUser(bool isFire = false);

    DWORD friendDegree()
    {
      return this->dwFriendDegree;
    }

    DWORD dwCountryID; // ID1
    DWORD dwAllyCountryID; // ID2
    DWORD dwFriendDegree;
    DWORD dwCreateTime;
    DWORD dwLastUpTime; // 每日自动扣减友好度的最后一次更新时间

    BYTE  byStatus; // 2已建立,1等待建立

    zRWLock rwlock;
};

class CAllyM : public Singleton<CAllyM>
{
  friend class SingletonFactory<CAllyM>;
  public:
    bool init();
    static void destroyMe();

    void timer();
    void save();

    bool loadAllyFromDB();
    bool processUserMessage(UserSession* pUser,const Cmd::stNullUserCmd* pNullCmd,const DWORD cmdLen);
                bool processSceneMessage(const Cmd::t_NullCmd *pNullCmd,const DWORD cmdLen);

    void processReqCountryAlly(UserSession* pUser,Cmd::stReqCountryAlly* rev);
    void processCancelCountryAlly(UserSession* pUser,Cmd::stCancelCountryAlly* rev);
    void processReqCountryAllyInfo(UserSession* pUser,Cmd::stReqCountryAllyInfo* rev);

    void refreshAlly(SessionTask* scene);
    void userOnline(UserSession* pUser);

    CAlly*  findAlly(DWORD dwCountryID1,DWORD dwCountryID2);
    CAlly*  findAlly(DWORD dwCountryID1);
    bool   addNewAlly(DWORD dwCountryID1,DWORD dwCountryID2);
    void   addReadyAlly(DWORD dwCountryID1,DWORD dwCountryID2);
    bool    fireAlly(DWORD dwCountryID1,DWORD dwCountryID2);
    void    removeAlly(DWORD dwCountryID1,DWORD dwCountryID2);
  private:
    std::vector<CAlly*> allies;
    zRWLock rwlock;
};

using namespace School;

/**
 * \brief 操作成员列表的类
 *
 */
class CSchoolMemberListCallback
{
private:
  /**
   * \brief 受影响的成员列表
   */
  std::list<CSchoolMember * > memberList;
public:

  /**
   * \brief 清除无效节点关系
   */
  void clearInValidNodeRelation();

  /**
   * \brief 遍历
   * \param member 当前节点
   */
  void exec(CSchoolMember *member);

  /**
   * \brief 发送通知给受影响的成员
   */
  void sendNotifyToMember();
};

/**
 * \brief 向成员发送其他成员信息的回调
 *
 */
class CSendSchoolCallback
{
private:
  ///成员列表
  std::list<struct Cmd::stSchoolMember> memberList;
public:
  void exec(CSchoolMember *member,const BYTE tag);
  void sendListToMember(CSchoolMember *member);
};

/**
 * \brief 门派管理器
 *
 */
class CSchoolM : public zEntryMgr<zEntryID,zEntryName>
{
private:
    /// 成员索引表
    std::map<std::string,CSchoolMember*> memberIndex;

    /// 类型定义
    typedef std::map<std::string,CSchoolMember*>::value_type memberIndexValueType;

    /// 唯一实例
    static CSchoolM * sm;
    ///读写锁
    zRWLock rwlock;
    inline std::map<std::string,CSchoolMember *>::iterator  findMemberIndex(const char *pName);

public:
    
    /**
     * \brief 析构函数
     */
    ~CSchoolM();
    
    /**
     * \brief 初始化师门门派管理器容器
     * \return true 为成功,false为失败
     */
    bool init();

    template <class YourEntry>
    bool execEveryOne(execEntry<YourEntry> &exec)
    {
      rwlock.rdlock();
      bool ret=execEveryEntry<>(exec);
      rwlock.unlock();
      return ret;
    }

    /**
     * \brief 获取唯一对象实例
     * \return 唯一对象实例
     */
    static CSchoolM &getMe();

    /**
     * \brief 摧毁师门门派管理器容器,做善后工作
     */
    static void destroyMe();

    /**
     * \brief 角色上线通知,管理器中对应的节点进行上线处理关联UserSession并且对左邻右舍进行通知
     * \param pUser 上线角色的会话对象
     */
    void userOnline(UserSession *pUser);

    /**
     * \brief 角色下线通知,管理器中对应的节点进行下线处理,并且对左邻右舍进行通知
     * \param pUser 下线的角色
     */
    void userOffline(UserSession * pUser);

    /**
     * \brief 在索引表中填加指定角色的索引
     * \param name 指定角色的名称
     * \param member 角色的节点对象
     * \return 失败返回false,成功返回true
     */
    bool addMemberIndex(const char *name,CSchoolMember *member);

    /**
     * \brief 在索引表中删除指定的角色的索引
     * \param name 指定角色的名称
     * \return 失败返回false,成功返回true
     */
    bool removeMemberIndex(const char *name);

    /**
     * \brief 处理客户端送过来的消息（也有可能是其他服务器转发过来的客户端消息）
     * \param pUser 发送消息的角色
     * \param pNullCmd 消息结构
     * \param cmdLen 消息长度
     * \return 失败返回-1,没有物品被创建返回0,包裹满返回1,成功添加所有创建的物品返回2
     */
    bool processUserMessage(UserSession *pUser,const Cmd::stNullUserCmd *pNullCmd,const DWORD cmdLen);

    /**
     * \brief 处理场景服务器送过来的消息
     * \param pNullCmd 消息结构
     * \param cmdLen 消息长度
     * \return 失败返回-1,没有物品被创建返回0,包裹满返回1,成功添加所有创建的物品返回2
     */
    bool processSceneMessage(const Cmd::t_NullCmd *pNullCmd,const DWORD cmdLen);

    /**
     * \brief 处理家族门派聊天消息转发
     * \param pUser 聊天消息发送者
     * \param rev 消息结构体
     * \param cmdLen 消息长度
     */
    void sendSchoolChatMessages(const UserSession *pUser,const Cmd::stChannelChatUserCmd *rev,const DWORD cmdLen);

    /**
     * \brief 处理家族门派聊天消息转发
     * \param pUser 聊天消息发送者
     * \param rev 消息结构体
     * \param cmdLen 消息长度
     */
    void sendSchoolPrivateChatMessages(const UserSession *pUser,const Cmd::stChannelChatUserCmd *rev,const DWORD cmdLen);

    /**
     * \brief 判断用户的徒弟是否满,
     * \param master 被检查的角色名称
     * \param schoolName 门派名称,如果此人的徒弟未满且此人是有门派的那么门派名称通过这里返回
     * \return 返回true表示master的徒弟没收满,返回false表示master的徒弟已经招收满了
     */
    bool getUserPrenticeInfo(const char *master,char *schoolName);

    /**
     * \brief 判断某个人是否为干净的,意思是他没有师傅和徒弟的关系,即他不在此管理器中
     * \param name 被检查的角色的名称
     * \return true为干净的,false 为已经有师或徒弟关系
     */
    bool isClean(const char *name);

    /**
     * \brief 为 master 增加一个徒弟 prentice,
     *
     * 在函数中会根据两人的情况进行具体的操作,如果不成功会给对应角色发送消息
     *
     * \param master 师傅
     * \param prentice 徒弟
     */
    void addMember(UserSession *master,UserSession *prentice);

    /**
     * \brief master 开除一个徒弟 prentice,
     *
     * 在函数中会根据两人的情况进行具体的操作,如果不成功会给对应角色发送消息
     *
     * \param master 师傅
     * \param prentice 徒弟
     */
    void frieMember(UserSession *master,const char *prentice);

    /**
     * \brief 从师门从开除一个角色
     *
     * \param roleName 角色名称
     * \param find 是否只是进行判断
     *
     * \return 如果该角色不在任何师门中,则返回2
     *         如果该角色是族长,则返回0
     *         如果该角色是族员,并删除成功,则返回1
     *
     */
    int fireSchoolMember(const char* roleName,bool find);

    /**
     * \brief 初始化的时候根据数据库中load的记录创建一个门派管理器
     * \param info 门派的信息结构
     * \return 成功返回true,失败返回false
     */
    bool createSchoolFromDB(const stSchoolInfo &info);

    /**
     * \brief 从数据库中加载门派的信息建立门派管理器
     * \return true为成功,false为失败
     */
    bool loadSchoolFromDB();

    /**
     * \brief 从数据库中加载所有门派的成员
     * \return true为成功,false为失败
     */
    bool loadSchoolMemberFromDB();

    /**
     * \brief 检查指定的角色是否具备创建门派的条件
     * \param pUser 被检查的角色
     * \return true为具备,false为不具备
     */
    bool checkSchoolCreateCondition(const UserSession *pUser);

    /**
     * \brief 创建一个新的门派
     * \param userName 师尊的名字
     * \param schoolName 门派的名称
     * \return true 为创建成功,false 为创建失败
     */
    bool createNewSchool(const char *userName,const char *schoolName);

    /**
     * \brief 响应公告功能设置公告或者读取公告
     * \param pUser 公告者
     * \param rev 公告消息
     */
    void processBulletin(const UserSession *pUser,const Cmd::stSchoolBulletinCmd *rev);

    /**
     * \brief 获取名称所指定的节点对象
     * \param pName 名称
     * \return 获取指定的节点对象,如果不存在该名称的对象则返回NULL
     */
    CSchoolMember *getMember(const char *pName);

    /**
     * \brief 处理成员退出门派或者师门
     * \param pUser 退出者的UserSession对象
     */
    void processLeaveGroup(UserSession *pUser);

    /**
     * \brief 处理成员退出门派或者师门
     * \param roleName 角色名称
     */
    void processLeaveGroupDirect(const char* roleName);

    /**
     * \brief 解散门派,如果条件符合pName所领导的门派将被解散,所有的人员关系回复到原始的师门关系
     * \param pName 解散门派者的名字
     * \return true 解散成功 false 解散失败
     */
    bool destroySchool(const char *pName);

    /**
     * \brief 根据ID获得对应的管理器
     * \param id 管理器ID
     * \return 如果成功返回管理器对象,失败返回NULL
     */
    CSchool *getSchool(DWORD id);

    /**
     * \brief 设置指定用户的级别
     * \param pName 用户名称
     * \param level 新级别
     */
    void setUserLevel(const char *pName,const WORD &level);

    CSchool * getSchoolByName( const char * name);
    
};

class CSchool : public zEntryMgr<zEntryID,zEntryName>,public zEntry
{
private:
    /**
     * \师尊的ID
     */
    DWORD dwMasterSerialID;

    /**
     * \公告
     */
    std::string bulletin;

    /**
     * \brief 对象有效标志,一般判断依据是是否还存在数据库中
     */
    bool destroy;

    /**
     * \brief 管理器读写锁
     */
    zRWLock rwlock;

public:
/*
    bool getUniqeID(QWORD &tempid){return true;};
    void putUniqeID(const QWORD &tempid){};
*/

    /**
     * \brief 遍历模板定义
     */
    template <class YourEntry>
                bool execEveryOne(execEntry<YourEntry> &exec)
    {
      rwlock.rdlock();
      bool ret=execEveryEntry<>(exec);
      rwlock.unlock();
      return ret;
         }
                
         template <class YourEntry>
         void removeOne_if(removeEntry_Pred<YourEntry> &pred)
         {
                rwlock.wrlock();
                removeEntry_if<>(pred);
                rwlock.unlock();
         }


    /**
     * \brief 构造函数
     */
    CSchool();

    /**
     * \brief 析构函数
     */
    ~CSchool();



    /**
     * \brief 获取门派名称
     * \return 门派名称
     */
    char *getSchoolName();

    /**
     * \brief 设置门派名称未加锁
     * \param pName 门派名称
     */
    void setSchoolName(const char *pName);

    /**
     * \brief 设置师尊的节点ID
     * \param id 师尊的节点ID
     */
    void setMasterSerialID(const DWORD &id);

    /**
     * \brief 添加一个师门的根节点
     * \param master 角色对象
     * \return 新加的节点对象,失败返回NULL
     */
    CSchoolMember *  addTeacher(UserSession *master);

    /**
     * \brief 向从管理器中增加指定的节点,并将其加入索引表
     * \param member 指定的节点
     */
    bool addMember(CSchoolMember *member);

    /**
     * \brief 从管理器中删除指定的节点,并将其从索引表中去除
     * \param member 指定的节点
     */
    void removeMember(CSchoolMember *member);
  
    /**
     * \brief 将管理器初始化成师门关系管理器
     * \return 返回NULL表示添加徒弟失败,否则返回徒弟的节点对象
     */
    void initToNoneSchool();

    /**
     * \brief 初始化管理器,根据信息结构,从数据库初始化的时候用
     * \param info 管理器信息结构
     */
    void initSchool(const stSchoolInfo &info);

    /**
     * \brief 从数据库加载本管理器内的所有节点信息
     * \return 返回true 表示加载成功,返回false表示加载失败
     */
    bool loadSchoolMemberFromDB();

    /**
     * \brief 更新门派的信息到数据库
     * \return 返回true 表示加载成功,返回false表示加载失败
     */
    bool updateSchoolInDB();

    /**
     * \brief 增加一个节点,数据库初始化的时候调用本方法,通常调用本方法的时候节点数据都是有序的,节点序列号由小到大
     * \param info 节点信息
     */
    bool addNode(const stSchoolMemberInfo &info);

    /**
     * \brief 发送命令到整个School里的角色
     * \param pNullCmd 消息结构
     * \param cmdLen 消息长度
     */
    void sendCmdToSchool(const Cmd::stNullUserCmd *pNullCmd,const DWORD cmdLen);

    /**
     * \brief 插入门派记录到数据库中
     * \return true 插入成功 false 插入失败
     */
    bool insertSchoolToDB();

    /**
     * \brief 将本节点管理器从数据库中删除
     * \return true 删除成功 false 删除失败
     */
    bool deleteSchoolFromDB();

    /**
     * \brief userName创建了一个新的帮会pSchool将门派中的所有userName的徒子徒孙归到新School管理起pSchool中,这个方法只适用于门派管理器
     * \param userName 新的师尊的名字
     * \param pSchool 新的管理器对象指针
     * \return true 成功 false 失败
     */
    bool moveMemberToNewSchool(const char *userName,CSchool *pSchool);


    /**
     * \brief 判断一个角色是不是该师门成员
     * 
     * \param memberName 玩家名字
     *
     * \return true 是师门成员,FALSE不是师门成员
     */
    bool  isMember(const char* memberName);
    
    /**
     * \brief 给所有师门成员发送转发到场景的命令
     *
     * \param ptEnterWarCmd 待转发的命令
     * \param cmdLen 命令长度
     *
     */
    void sendCmdToAllMemberScene(Cmd::Session::t_enterWar_SceneSession* ptEnterWarCmd,const DWORD cmdLen);

    /**
     * \brief 直接添加一个节点,该节点已经存在于索引表之中了
     * \param member 被添加的节点
     */
    void directAdddMember(CSchoolMember *member);

    /**
     * \brief 直接删除一个节点,不不在索引表中删除该节点
     * \param member 被添加的节点
     */
    void directRemoveMember(CSchoolMember *member);

    /**
     * \brief 直接删除一个节点,不不在索引表中删除该节点
     * \return 正常返回门派的节点对象,异常返回NULL
     */
    CSchoolMember * getMasterNode();

    /**
     * \brief 设置公告
     * \param buf 公告内容
     */
    void setBulletin(const char *buf);

    /**
     * \brief 获得公告
     * \return 公告内容或者NULL
     */
    const char * getBulletin();

    /**
     * \brief 获得指定的成员
     * \param pName 指定的名称
     * \return 找到的成员对象或者NULL
     */
    CSchoolMember *getMember(const char *pName);

    /**
     * \brief 处理指定成员的关系断绝（在门派中是完全退出,在师门中是断绝与师傅的关系
     * \param member 要退出成员的节点对象
     * \param deleteTeacher是否删除师傅节点,此标志用于防止在函数内删除调用对象,此标志在门派中不起作用,意思是不能在门派成员对象中调用此函数
     * \return true 为成功 false为失败
     */
    bool processLeaveSchool(CSchoolMember * member,bool deleteTeacher = true);

    /**
     * \brief 将本门派解散所有成员关系转移到师门管理器管理
     * \return true 为成功 false为失败
     */
    bool moveMemberToTeacherGroup();

    void notifyWarResult(const char* msg,...);

    DWORD getID(){return id;}
};

class CSchoolMember : public zEntry
{
private:

    /**
     * \brief 对象有效标志,一般判断依据是是否还存在数据库中
     */
    bool destroy;

    /**
     * \brief 当前角色的UserSession对象
     */
    DWORD dwCharID;

    /**
     * \brief 当前角色的职业
     */
    DWORD wdOccupation;

    /**
     * \brief 当前角色的UserSession对象
     */
    UserSession    *user;

    /**
     * \brief 师傅节点
     */
    CSchoolMember  *preLevelNode;

    /**
     * \brief 排序
     */
    struct ltword
    {
      bool operator()(const DWORD s1,const DWORD s2) const
      {
        return s1<s2;
      }
    };
    /**
     * \brief 徒弟列表
     */
    std::map<DWORD,CSchoolMember*,ltword> prenticeList;

    /// 类型定义
    typedef std::map<DWORD,CSchoolMember*,ltword>::value_type prenticeListValueType;

    /**
     * \brief 所在的门派管理器（无门派的归结为一个门派）
     */
    CSchool      *school;

    /**
     * \brief 师傅节点的ID
     */
    DWORD dwMasterID;

    /**
     * \brief 前一个节点的序列号
     */
    DWORD dwPreSerialID;

    /**
     * \brief 角色当前级别
     */
    DWORD wdLevel;

    /**
     * \brief 拜师时间
     */
    DWORD dwJoinTime;

    /**
     * \brief 与师傅间的友好度
     */
    WORD  wdDegree;

    /**
     * \brief 最后组队时间
     */
    DWORD dwLastTime;

    /**
     * \brief 所属门派ID如果无门派为0
     */
    DWORD dwSchoolID;

    /**
     * \brief 节点有效标记,1为有效,0为无效,无效的节点只存在于门派之中起上下连接之用
     */
    BYTE  byTag;
    
  
    /**
     * \brief 本节点的读写锁
     */
    zRWLock rwlock;

public:
    /**
     * \brief 将本节点的信息插入数据库,节点初创的时候用
     * \return true为成功,false 为失败
     */
    bool insertRecord(); // 将自己插入数据库

    /**
     * \brief 更新数据库中的节点信息
     * \param locked 是否已经加锁 默认为否
     * \return true为成功,false 为失败
     */
    bool updateRecord(bool locked = false); // 将自己插入数据库

    /**
     * \brief 将自己的数据库记录删除
     * \return true为成功,false 为失败
     */
    bool deleteRecord();

    /**
     * \brief 构造函数,对节点进行部分初始化
     * \param pSchool 本节点所在的管理器对象
     * \param pUser 节点的拥有者
     */
    CSchoolMember(CSchool *pSchool,UserSession *pUser);

    /**
     * \brief 析构函数
     */
    ~CSchoolMember();

    /**
     * \brief 获取节点对应的角色ID
     * \return 角色ID
     */
    DWORD getCharID();

    /**
     * \brief 获取节点序列号
     * \return 节点序列号
     */
    DWORD getSerialID();

    /**
     * \brief 获取节点所在门派的ID
     * \return 门派ID
     */
    DWORD getSchoolID();

    /**
     * \brief 获取友好度
     * \return 友好度
     */
    WORD getDegree();

    /**
     * \brief 设置友好度
     * \param degree 友好度
     */
    void setDegree(const WORD &degree);

    /**
     * \brief 设置最后组队时间
     * \param lasttime 最后组队时间
     */
    void setLastTime(const DWORD &lasttime);

    /**
     * \brief 获取本节点的门派名称
     * \return 门派名称
     */
    char *getSchoolName();

    /**
     * \brief 获得当前节点的徒弟记数（有效节点数）
     * \return 当前节点的徒弟记数
     */
    BYTE getPrenticeCount();

    /**
     * \brief 获得拜师时间
     * \return 拜师时间
     */
    DWORD getJoinTime();

    /**
     * \brief 获得最后组队时间
     * \return 最后组队时间
     */
    DWORD getLastTime();

    /**
     * \brief 获得角色级别
     * \return 角色级别
     */
    WORD getLevel();
    
    /**
     * \brief 为本节点添加一个徒弟
     * \param pUser 徒弟的UserSession对象
     * \return 返回NULL表示添加徒弟失败,否则返回徒弟的节点对象
     */
    CSchoolMember *addPrentice(UserSession *pUser);

    /**
     * \brief 添加一个纯粹的师傅节点,只适用于那些从未招收过徒弟的人第一次招收徒弟时在管理器中初始化自己
     */
    void initRootMember();

    /**
     * \brief 对徒弟节点进行初始化
     * \param master 师傅节点的节点对象
     */
    void initGeneralMember(CSchoolMember * master);

    /**
     * \brief 将无效节点初始化成有效节点
     * \param master 师傅节点的节点对象
     */
    void initInValidNode(CSchoolMember * master);
    /**
     * \brief 判断节点是否还存在关联的上级节点或者下级节点
     * \return true为本节点已经与其他节点断绝一切关系,false 为本节点与其他节点还存在关系
     */
    bool isClean();

    /**
     * \brief 获得本节点所在的管理器对象
     * \return 成功返回管理器对象,失败返回NULL
     */
    CSchool * getSchool();

    /**
     * \brief 将自己从门派中删除掉,并删除对应的数据库记录
     */
    void deleteMe();

    /**
     * \brief 上线处理
     */
    void online(UserSession *pUser);

    /**
     * \brief 下线处理
     */
    void offline();


    /**
     * \brief 找到排位在member之前的师兄
     * \param member 被检查的节点
     * \param name 师兄的名称
     */
    void getMyBigBrother(CSchoolMember *member,char *name);

    /**
     * \brief 通知周遍成员我的加入并发送初始化消息给自己
     */
    void notifyNewMemberAdd();

    /**
     * \brief 发送个人的师徒门派信息给客户端进行初始化
     * \param callback 门派信息的回调对象,可以在外面事先获得门派信息适合对门派多数人广播门派信息默认为空
     */
    void sendInfomationToMe(CSendSchoolCallback *callback = NULL);

    /**
     * \brief 徒弟请求发送师傅和兄弟的信息
     * \param count 计数器,累计当前已经有多少信息被放如buf
     * \param point 信息存放buf的指针
     * \param me 请求信息的角色的节点对象
     * \return true为干净的,false 为已经有师或徒弟关系
     */
    void prenticeRequestMemberInfo(DWORD &count,Cmd::stTeacherMember *point,CSchoolMember *me);

    /**
     * \brief 根据数据库记录初始化节点
     * \param info 数据库记录信息结构
     */
    void initByDBRecord(const stSchoolMemberInfo &info);

    /**
     * \brief 判断节点是否存在师傅,根据info属性内容判断
     * \return true为有师傅,false 为没有师傅
     */
    bool haveTeacher();

    /**
     * \brief 判断节点是否存在前一节点,在门派中一个人可能没有师傅但是会有前一节点
     * \return true为有节点,false 当前节点为根节点（师尊）
     */
    bool havePreNode();

    /**
     * \brief 添加一个下一级节点,不会有通知动作,用在数据库初始化的时候
     * \param member 下一级节点
     */
    bool addNextLevelNode(CSchoolMember *member);

    /**
     * \brief 设置本节点的上层节点
     * \param pPreNode 上层节点
     */
    void setPreLevelNode(CSchoolMember *pPreNode);

    /**
     * \brief 开除指定名字的徒弟
     * \param PrenticeName 被开除人的名字
     * \return true 为开除成功,false为没有此人
     */
    bool firePrentice(const char *PrenticeName);

    /**
      * \brief 开除所有徒弟
      *
      */
    bool fireAllPrentice();

    /**
     * \brief 核对本节点是不是名称对应的节点
     * \param pName 指定的名称
     * \return true 这个节点就是要找的节点,false 节点不叫这个名字
     */
    bool isMe(const char *pName);

    /**
     * \brief 节点对应角色是否在线
     * \return true 角色在线,false 角色不在线
     */
    bool isOnline();

    /**
     * \brief 判断节点是否是有效的,判断依据为tag是否为1
     * \return true 有效的,false 无效的
     */
    bool isValid();

    /**
     * \brief 获得节点在树中的度
     * \param layer 度
     */
    void getMyLayer(DWORD &layer);

    /**
     * \brief 通知该节点及其所有徒弟,更新自己的师门列表
     */
    void notifyTeacherGroup();

    /**
     * \brief 发送命令到节点对应的角色
     * \param pNullCmd 消息结构
     * \param cmdLen 消息长度
     */
       void sendCmdToMe(const Cmd::stNullUserCmd *pNullCmd,const DWORD cmdLen);

    /**
     * \brief 发送聊天消息到节点对应的对象
     * \param type 系统消息的类型 
     * \param pattern 消息
     * \param ... 参数
     */
    void sendSysChat(int type,const char *pattern,...);

    /**
     * \brief 清除师徒关系,preLevelNode指针置空,师傅信息清0
     */
    void clearTeacherRelation();

    /**
     * \brief 检查此人的徒弟徒孙的数目和级别是否达到成立门派的条件
     * \return true 为条件满足 false 为条件不满足
     */
    bool checkSchoolCreateCondition();

    /**
     * \brief 检查节点自己和徒弟的条件是否达到师傅成立门派的要求
     * \return true 为条件满足 false 为条件不满足
     */
    bool checkMeAndPrenticeNumberAndLevel();

    /**
     * \brief 将节点自己及其所有的徒弟都挪到管理器pSchool之中
     * \param pSchool 节点移动的目标管理器
     * \param memberSet 成员处理回调对象,如果不需要对被移动成员进行处理可以设置为NULL,默认为NULL
     */
    void moveAllToSchool(CSchool *pSchool,CSchoolMemberListCallback *memberSet = NULL);

    /**
     * \brief 通知本派系所有的节点重新发送初始化消息给客户端
     * \param callback 门派信息回调对象,用来发送门派的组织结构初始化信息给客户端
     */
    void notifyAllReSendInitData(CSendSchoolCallback *callback);

    /**
     * \brief 获得门派的所有成员列表（有序的）
     * \param callback 回调类
     */
    void getSchoolTree(CSendSchoolCallback &callback);

    /**
     * \brief 获得门派的所有成员列表（有序的）
     * \param level 当前层
     * \param tgLevel 此次调用的目标层
     * \param condition 到底标志,如果已经到了树的底部那么就返回 false
     * \param callback 回调对象
     * \param tag 换行换层标志 参见enum SCHOOL_LAYER
     */
    void schoolTreeCallback(DWORD level,DWORD tgLevel,bool &condition,CSendSchoolCallback &callback,BYTE &tag);

    /**
     * \brief 将公告内容发送给节点对应的角色
     */
    void sendBulletinToMe();

    /**
     * \brief 设置本门派的公告内容,当然节点必须是师尊才行
     * \param buf 公告内容
     */
    void setBulletin(const char *buf);

    /**
     * \brief 向节点及其徒弟发送消息
     * \param pNullCmd 消息结构
     * \param cmdLen 消息长度
     * \param exceptMe 是否包括本节点,默认为包括
     */
    void sendCmdToTeacherGroup(const Cmd::stNullUserCmd *pNullCmd,const DWORD cmdLen,bool exceptMe = false);

    /**
     * \brief 向团体通知我的在线状态
     * \param onlineStatus 节点对应角色的在线状态
     */
    void sendOnlineStatusMessage(BYTE onlineStatus);

    /**
     * \brief 获得上级节点对象指针
     * \return 上级节点的对象,有可能为NULL
     */
    CSchoolMember * getPreLevelNode();

    /**
     * \brief 获得师傅节点,上级节点不一定是师傅节点,他们之间可能并不存在关系所以获得师傅节点不能使用getPreLevelNode
     * \return 如果有直接师傅返回师傅节点的对象,否则为NULL
     */
    CSchoolMember * getTeacher();

    /**
     * \brief 将节点设置成无效的.
     */
    void setInValid();

    /**
     * \brief 断绝和师傅之间的关系
     */
    void clearMaster();

    /**
     * \brief 发送退出门派的消息给客户端
     */
    void sendDestroyNotifyToMe();

    /**
     * \brief 直接在本节点的下层节点列表中删除指定的节点关系
     * \param member 关系需要删除的节点对象。
     */
    void directRemovePrentice(const CSchoolMember *member);

    /**
     * \brief 通知整个门派的客户端删除本节点对应的角色
     */
    void notifySchoolMemberRemove();

    /**
     * \brief 获得第一个无效的下级节点对象
     * \return 下级无效节点对象,如果没有合适的对象可能会返回NULL
     */
    CSchoolMember* getFirstInValideNode();

    /**
     * \brief 设置有效节点关联的UserSession对象
     * \param pUser 角色对应的UserSession对象
     */
    void setUser(UserSession *pUser);

    /**
     * \brief 获得本节点的直接下级节点总数不区分有效无效
     * \return 直接下级节点数
     */
    BYTE getNextLevelNodeCount();

    /**
     * \brief 清掉本节点与前一节点的关系属性,将相关的指针和属性置空或置0
     */
    void clearPreLevelNode();

    /**
     * \brief 清掉本节点与后一级节点的关系属性,将后一级节点相关的指针和属性置空或置0并将后级节点列表清空
     */
    void clearAllNextLevelRelation();

    /**
     * \brief 组队完毕对友好度进行保存
     * \param rev 友好度结算消息体
     */
    void setFriendDegree(const Cmd::Session::t_CountFriendDegree_SceneSession *rev);

    /**
     * \brief 转发聊天消息
     * \param rev 聊天消息结构体
     * \param cmdLen 消息长度
     */
    void sendChatMessages(const Cmd::stChannelChatUserCmd *rev,const DWORD cmdLen);

    /**
     * \brief 转发聊天消息
     * \return 获取角色对应的UserSession 对象如果角色不在线会返回NULL
     */
    UserSession *getUser();

    /**
     * \brief 设置级别
     * \param level 新的角色等级
     */
    void setLevel(const WORD level);

    /**
     * \brief 获取角色的职业
     * \param 职业
     */
    WORD getOccupation();

    /**
     * \brief 查询当前可以进贡的金额
     * \param 金额
     */
    DWORD queryBounty();

    /**
     * \brief 进贡
     */
    bool putBounty();

    /**
     * \brief 发送社会关系更新通知给场景
     */
    void sendNotifyToScene();

    /**
     * \brief 做为师傅累计收到的进贡,单位:文
     */
    DWORD  master_total;
    
    /**
     * \brief 做为师傅当前可以领取的进贡金额,单位:文
     */
    DWORD  master_balance;
    
    /**
     * \brief 做为徒弟累计进贡的金额,单位:文
     */
    DWORD  prentice_total;

    /**
     * \brief 做为徒弟上次进贡时的等级
     */
    DWORD  prentice_lastlevel;

};

using namespace SeptDef;

class CSeptM:public zEntryMgr<zEntryID,zEntryName>
{
  private:
    /// 成员索引
    std::map<std::string,CSeptMember*> memberIndex;

    /// 类型定义
    typedef std::map<std::string,CSeptMember*>::value_type memberIndexValueType;

    /// 唯一实例指针
    static CSeptM * um;

    /// 读写锁
    zRWLock rwlock;

    CSept *  createSeptAndAddMaster(const stSeptInfo&);
    bool     initAddSeptMember(const DWORD &,const stSeptMemberInfo &,bool notify = false);
    bool    createSeptDBRecord(stSeptInfo &info);
    void    removeEntryByName(const char * name);
    CSept*    createSeptByDBRecord(const stSeptInfo & info);
    inline std::map<std::string,CSeptMember *>::iterator  findMemberIndex(const char *pName);
    CSeptM();
    ~CSeptM();

  public:
    template <class YourEntry>
    bool execEveryOne(execEntry<YourEntry> &exec)
    {
      rwlock.rdlock();
      bool ret=execEveryEntry<>(exec);
      rwlock.unlock();
      return ret;
    }

    template <class YourEntry>
    void removeOne_if(removeEntry_Pred<YourEntry> &pred)
    {
      rwlock.wrlock();
      removeEntry_if<>(pred);
      rwlock.unlock();
    }

    CSept * getSeptByName( const char * name);
    
    CSept* getSeptByID(DWORD dwSeptID);
    CSeptMember * getMemberByName(const char * name);

    bool init();
    static CSeptM &getMe();
    static void destroyMe();

    void fireSeptMember(UserSession*,const char *);
    void notifyNpcHoldData(DWORD septid);

    /**
      * \brief 删除家族成员
      *
      * 如果该角色不是家族族长,则踢除他,如果是,则保留,不做处理
      *
      * \param dwUserID 角色ID
      * \param find     为TRUE表示查找,为FALSE为删除
      *
      * \return 如果该角色不在任何家族中,则返回2
      *         如果该角色是族长,则返回0
      *         如果该角色是族员,并删除成功,则返回1
      *
      */
    int  fireSeptMember(DWORD dwUserID,bool find);

    bool addNewMemberToSept(const DWORD dwSeptID,const stSeptMemberInfo&);
    void userOnline(UserSession *);
    void userOffline(const UserSession *);
    void createNewSept(Cmd::Session::t_addSept_SceneSession *data);
    bool addMemberIndex(const char *,CSeptMember *);
    bool removeMemberIndex(const char *);
    bool processUserMessage(UserSession *pUser,const Cmd::stNullUserCmd *pNullCmd,const DWORD cmdLen);
    
    void processSeptSortMessage(UserSession* pUser,
        const Cmd::stReqSeptSort* ptCmd);
    
    void processRequestSeptExpMessage(UserSession* pUser,const Cmd::stRequestSeptExpCmd* ptCmd);
    void processRequestSeptNormalExpMessage(UserSession* pUser,const Cmd::stRequestSeptNormalExpCmd* ptCmd);
    
    bool processSceneMessage(const Cmd::t_NullCmd *pNullCmd,const DWORD cmdLen);
    bool processSceneSeptMessage(const Cmd::t_NullCmd *pNullCmd,const DWORD cmdLen);
    bool processGateMessage(const Cmd::t_NullCmd *cmd,const DWORD cmdLen);
    void delSept(const DWORD dwSeptID);
    void processMemberLeave(const DWORD dwSeptID,const DWORD dwCharID);
    void sendSeptNotify(const DWORD septID,const char* message,...);
    void sendNpcDareCmdToScene(const DWORD septID,Cmd::Session::t_NpcDare_NotifyScene_SceneSession* ptCmd,DWORD nCmdLen);
    void sendSeptChatMessages(const UserSession *pUser,const Cmd::stChannelChatUserCmd *rev,const DWORD cmdLen);
    void sendSeptPrivateChatMessages(const UserSession *pUser,const Cmd::stChannelChatUserCmd *rev,const DWORD cmdLen);
    void sendVoteListToUser(const UserSession *pUser);
    void sendListToUser(const UserSession *pUser);
    void sendDareListToUser(const UserSession *pUser);
    void userVote(const UserSession *pUser,const char *pName);
    void userAboutVote(const UserSession *pUser,const char *pName);
    void addVoteMemberToSept(const UserSession *pUser,const char *pName);
    void disributeExp(Cmd::Session::t_distributeSeptExp_SceneSession *cmd);
    void setSeptNote(UserSession *pUser,Cmd::stNoteSeptCmd *pCmd);
    DWORD findUserSept(DWORD dwUserID);
    void delSeptAllMember();

    /**
     * \brief 更改别名
     *
     * \param pUser 请求更名者(目前只能是帮主)
     *
     * \param pCmd 更名命令
     *
     * \return 
     */
    void change_aliasname(UserSession *pUser,Cmd::stChangeSeptMemberAliasName* pCmd);
    void changeAllRepute(DWORD countryid,int repute);
    DWORD getRepute(DWORD dwSeptID);//得到声威值
    void changeRepute(DWORD dwSeptID,int repute);//改变声威值
    void changeLevel(DWORD dwSeptID,int level);
    char * getSeptNameByUserName(char *Name);
    DWORD getSeptIDByUserName(char *Name);    
};

class CSept:public zEntryMgr<zEntryID,zEntryName>,public zEntry
{
  private:
    /// 毁灭状态不再执行写库等操作
    bool          destroy;
    
    /// 读写锁
    zRWLock rwlock;

  public:
    /// 是否还处于投票期间,1为是0为否
    BYTE          byVote;

    /// 家族会长
    CSeptMember          *master;

    /// 创立时间
    DWORD          dwCreateTime;

    /// 介绍
    char          note[255];

    /// 家族所属国家
    DWORD dwCountryID;

    /// 家族所属帮会
    DWORD dwUnionID;

    /// 
    void clearUnion()
    {
      this->rwlock.wrlock();
      this->dwUnionID = 0;
      this->rwlock.unlock();
    }
    

    /// 家族等级
    DWORD dwLevel;

    /// 家族声望
    DWORD dwRepute;

    /// 家族消费金币
    DWORD dwSpendGold;
    
    /// 家族是否领取经验
    DWORD dwIsExp;

    /// 令牌使用次数
    DWORD calltimes;
    /// 令牌使用时间
    DWORD calldaytime;
    /// 上次领取普通家族经验的时间
    DWORD normal_exp_time;

	struct stStepRight
	{
		char RightName[MAX_NAMESIZE + 1];
		DWORD dwRight;
	} RightList[10];
	
    template <class YourEntry>
    bool execEveryOne(execEntry<YourEntry> &exec)
    {
      rwlock.rdlock();
      bool ret=execEveryEntry<>(exec);
      rwlock.unlock();
      return ret;
    }

    template <class YourEntry>
    void removeOne_if(removeEntry_Pred<YourEntry> &pred)
    {
      rwlock.wrlock();
      removeEntry_if<>(pred);
      rwlock.unlock();
    }

    CSept();
    ~CSept();
    void      removeEntryByName(const char * name);
    DWORD      getID() {return id;}
    void      init(const stSeptInfo & info);
    CSeptMember *addSeptMember(const stSeptMemberInfo&);
    CSeptMember *addSeptMaster(const stSeptInfo& info);
    CSeptMember *getMemberByName(const char* pName);
    void      sendUserSeptData(const char *pName);
    void      fireSeptMember(const char *,const char *);
    int      fireSeptMemberDirect(const DWORD dwCharID,const bool checkunion=true);

    void      sendCmdToAllMember(const Cmd::stNullUserCmd * ptCmd,const DWORD nCmdLen );
    void      sendCmdToAllMemberExcept(const Cmd::stNullUserCmd * ptCmd,const DWORD nCmdLen,const char * except);
    bool      isMember(DWORD dwUserID);
    void      sendSeptNotify(const char* message,...);

    void      sendCmdToAllMemberScene(Cmd::Session::t_enterWar_SceneSession* ptEnterWarCmd,const DWORD cmdLen);
    void      sendCallCmdToAllMemberScene(Cmd::Session::t_GoTo_Leader_Check_SceneSession* ptEnterWarCmd,const DWORD cmdLen,DWORD expect);
    void      sendNpcDareCmdToScene(Cmd::Session::t_NpcDare_NotifyScene_SceneSession* pCmd,DWORD cmdLen);

    void      sendDistributeSeptExpToScene(const DWORD dwUserID,const Cmd::Session::t_distributeSeptExp_SceneSession * ptCmd);
    void      notifyMemberFire(const char *);
    void      writeDatabase();
    void      sendSeptMemberList(UserSession *pUser);
    void      full_SeptMember_Data(Cmd::stUnionRember*& tempPoint,DWORD& count);
    void      sendSeptInfoToUser(UserSession *pUser);
    bool      deleteMeFromDB();
    void      disbandSept();
    void      delSept(const DWORD dwSeptID);
    bool      loadSeptMemberFromDB();
    DWORD      size();
    bool      isVote();
    void      letVoteOver();
    
    void  setExp()
    {
      rwlock.wrlock();
      this->dwIsExp = 1;
      rwlock.unlock();
      this->writeDatabase();
    }
    
    void  clearExp()
    {
      rwlock.wrlock();
      this->dwIsExp = 0;
      rwlock.unlock();
      this->writeDatabase();
    }

    DWORD getExp()
    {
      return this->dwIsExp;
    }

    void      setNote(Cmd::stNoteSeptCmd *pCmd);
    void                    notifyWarResult(const char* msg,...);
    void       delSeptAllMember();
    DWORD       getRepute();//得到声威值
    void                    changeRepute(int repute);//改变声威值
    void      changeLevel(int level);
    void      sendSeptInfoToAll(); // 重新通知家族信息
    void      sendSeptReputeToAll(); // 通知所有家族成员声望的改变
    void      notifyNpcHoldData();
    void      sendGoldToMember(DWORD userID,DWORD num);
};

struct CSeptMember:public zEntry
{
public:
    /// 族员状态
    BYTE  byStatus;
    
    /// 族员别名
    char  aliasname[MAX_NAMESIZE+1];

    /// 族员职业
    WORD  wdOccupation;

    /// 用户的会话对象
    //UserSession * user;

    /// 家族管理器对象指针
    CSept *mySept;

    /// 毁灭状态不再执行写库等操作
    bool  destroy;
    
    /// 互斥锁
    zRWLock rwlock;

	WORD	mnRight; //会员权限;
    /// 再线状态枚举
    enum {
          Offline,
          Online
    };


    void init(const stSeptMemberInfo&);
    void getMemberBaseInfo(struct Cmd::stSeptRember& info);
    void sendCmdToMe(const Cmd::stNullUserCmd *pstrCmd,const DWORD nCmdLen);
    void writeDatabase();
    void insertDatabase();
    void setSept(CSept * pSept);
    void online(const DWORD status = Cmd::SEPT_MEMBER_STATUS_ONLINE);
    void offline();
    bool isOnline();
    void sendMessageToMe(const char *);
    void sendMessageToMe(int type,const char *);
    void fireMe(const bool notify = true,const bool checkunion=true);
    bool deleteMeFromDB();
    void sendUserSeptData();
    void change_aliasname(const char* aliasname);
    void update_data();
    void update_normal_data();
    void notifyNpcHoldData();
    void sendGoldToMember(DWORD userID,DWORD num);
    CSeptMember();
    ~CSeptMember();
    
};

extern DWORD dare_active_time;
extern DWORD dare_ready_time;
extern int dare_need_gold;
extern int dare_winner_gold;

extern int dare_need_gold_sept;
extern int dare_winner_gold_sept;

typedef zUniqueID<QWORD> zUniqueDWORDID;

/**
 * \brief 对战记录管理类
 *
 * 管理对战记录的容器,使用Singleton模式
 */
class CDareM:public zEntryMgr<zEntryTempID>,
       public Singleton<CDareM>
{
  friend class SingletonFactory<CDareM>;

  private:
    zUniqueDWORDID *channelUniqeID;
    zRWLock rwlock;

    CDareM();

  public:
    ~CDareM();

    bool getUniqeID(QWORD &tempid);
    void putUniqeID(const QWORD &tempid);

    template <class YourEntry>
      bool execEveryOne(execEntry<YourEntry> &exec)
      {
        rwlock.rdlock();
        bool ret=execEveryEntry<>(exec);
        rwlock.unlock();
        return ret;
      }

    template <class YourEntry>
      void removeOne_if(removeEntry_Pred<YourEntry> &pred)
      {
        rwlock.wrlock();
        removeEntry_if<>(pred);
        rwlock.unlock();
      }

    bool init();
    static void destroyMe();

    /**
     * \brief 对战管理器的定时器回调函数
     *
     * 定时遍历所有对战记录,删除无效记录,结束达到时间的对战等相关处理。
     */
    void timer();


    /**
     * \brief 处理用户的对战命令
     *
     * \param pUser 发送该命令的玩家相对应的UserSession对象
     * \param pNullCmd 收到的命令
     * \param cmdLen 命令长度
     * \return 是对战命令,并得到相应处理,返回为true,否则为false
     *
     */
    bool processUserMessage(UserSession *pUser,const Cmd::stNullUserCmd *pNullCmd,const DWORD cmdLen);

    
    /**
     * \brief 处理用户的家族随意战对战命令
     *
     * \param pUser 发送该命令的玩家相对应的UserSession对象
     * \param pNullCmd 收到的命令
     * \param cmdLen 命令长度
     * \return 是对战命令,并得到相应处理,返回为true,否则为false
     *
     */
    bool processSeptDare(UserSession *pUser,Cmd::stActiveDareCmd *pCmd,const DWORD cmdLen);

    /**
     * \brief 处理用户的帮会随意战对战命令
     *
     * \param pUser 发送该命令的玩家相对应的UserSession对象
     * \param pNullCmd 收到的命令
     * \param cmdLen 命令长度
     * \return 是对战命令,并得到相应处理,返回为true,否则为false
     *
     */
    bool processUnionDare(UserSession *pUser,Cmd::stActiveDareCmd *pCmd,const DWORD cmdLen);


    /**
     * \brief 处理场景发送过来的服务器间消息
     *
     * \param cmd 场景服务器发送过来的命令指令
     * \param cmdLen 命令长度
     *
     * \return 是已定义的服务器间命令,并得到相应处理,返回true,否则为false.
     *
     */
    bool processSceneMessage(const Cmd::t_NullCmd *cmd,const DWORD cmdLen);

    /**
     * \brief 查找符合条件的对战记录
     *
     *  当ID2为0时,查找是否有ID1参战的记录。dwType参数必须输入。
     *
     * \param dwType 对战类型:Cmd:UNION_DARE,Cmd:SCHOOL_DARE,Cmd:SEPT_DARE
     * \param dwID1  攻方ID
     * \param dwID2  守方ID
     *
     * \return 找到则返回对应对战记录的指针
     */
    CDare * findDareRecord(DWORD dwType,DWORD dwID1,DWORD dwID2);
    CDare*  findDareRecordByFull(DWORD dwType,DWORD dwDefID,std::vector<DWORD>& vDareList);

    /**
     * \brief 查找该社会关系指定的的对战记录,不管该社会关系处于攻方还是守方
     *
     * \param dwType 对战类型:Cmd:UNION_DARE,Cmd:SCHOOL_DARE,Cmd:SEPT_DARE
     * \param dwID  社会关系ID
     *
     * \return 找到则返回对应对战记录的指针
     */
    CDare*  findDareRecordByID(DWORD dwType,DWORD dwID);
    
    /**
     * \brief 查找符合条件的对战记录
     *
     *  r1,r2没有顺序限制,不区别哪一个r是挑战方的名称
     *  当r2为NULL时,查找是否有r1参战的记录。dwType参数必须输入。
     *
     * \param dwType 对战类型:Cmd:UNION_DARE,Cmd:SCHOOL_DARE,Cmd:SEPT_DARE
     * \param r1  社会关系名称1
     * \param r2  社会关系名称2
     *
     * \return 找到则返回对应对战记录的指针
     */

    CDare * findDareRecordByRelationName(DWORD dwType,const char* r1,const char* r2);

    /**
     * \brief 查找符合条件的对战记录
     *
     *  ID1,ID2没有顺序限制,不区别哪一个ID是挑战方的ID。
     *  当ID2为0时,查找是否有ID1参战的记录。dwType参数必须输入。
     *
     * \param dwType 对战类型:Cmd:UNION_DARE,Cmd:SCHOOL_DARE,Cmd:SEPT_DARE
     * \param dwUserID1  玩家ID1
     * \param dwUserID2  玩家ID2
     *
     * \return 找到则返回对应对战记录的指针
     */
    CDare*  findDareRecordByUser(DWORD dwType,DWORD dwUserID1,DWORD dwUserID2);


    /**
     * \brief 加入新的对战记录
     *
     * \param pCmd 对战请求命令
     * \param dwType 对战类型
     * \param dwID1 挑战者社会关系ID
     * \param dwID2 应战者社会关系ID
     * \param dwUserID 挑战者ID
     *
     * \return 没有重复记录,并加入成功,返回true,否则返回false
     *
     */
    bool addNewDareRecord(Cmd::stActiveDareCmd *pCmd,DWORD dwType,DWORD dwID1,DWORD dwID2,DWORD dwUserID);

    /**
      * \brief 用户上线处理
      *
      * 用户上线时,同时判断该用户的对战状态,并做相应处理
      *
      * \param pUser 上线用户
      *
      */
    void userOnline(UserSession* pUser);

    void userOnlineCountry(UserSession* pUser);

    /**
     * \brief 处理场景回复的t_activeDare命令
     *
     * \param cmd 对战记录
     */
    void activeDare_sceneSession(Cmd::Session::t_activeDare_SceneSession* cmd);

    /**
     * \brief 处理场景发过来的战斗时的PK战果命令
     *
     * \param cmd 命令指针
     */
    void darePk_sceneSession(Cmd::Session::t_darePk_SceneSession* cmd);
    
    /**
     * \brief 处理场景发过来的新建对战的命令
     *
     * \param pCmd 命令指针
     */

    void createDare_sceneSession(Cmd::Session::t_createDare_SceneSession* pCmd,std::vector<DWORD>& dare_list);
    

    void createUnionCityDare_sceneSession(Cmd::Session::t_UnionCity_Dare_SceneSession* pCmd);
};

class CDare:public zEntry
{
  protected:
    zRWLock rwlock;                             // 读写锁

    /**
     * \brief 计算并发送奖金
     *
     *  该函数目前只被setWaitBountyState函数调用
     *
     * \return 发送奖金成功,返回TRUE,否则返回失败。
     */
    virtual bool computeResult();

    virtual char* getFirstName(){return NULL;}      // 挑战者社会关系的名字
    virtual DWORD getSecondUserID(){return 0;}    // 应战者玩家的ID

    /// 对战进行时间
    DWORD active_time;

    /// 对战前的等待时间
    DWORD ready_time;

    // 对战开始时间
    time_t  start_time;

  public:
    enum{
      DARE_READY,   // 邀请等待状态
      DARE_READY_QUESTION,   // 等待被挑战者回应状态      
      DARE_READY_ACTIVE,     // 等待扣除应战者金币,如果失败,则进入DARE_RETURN_GOLD
      DARE_RETURN_GOLD,      // 如果金币不够,则把预先扣除的挑战方的金钱返还给他。并进入DARE_OVER状态。
      DARE_ACTIVE,   // 交战状态
      DARE_DATAPROCESS, // 数据处理状态,暂时未用
      DARE_READY_OVER,       // 结束对战,通知场景取消所有人的对战状态,并计算输赢,
      DARE_WAIT_BOUNTY,      // 如果赢方帮主不在线,处于这个状态,该玩家上线后,把奖励发放给他
      DARE_OVER    // 结束清除状态
    };

    CDare(DWORD active_time,DWORD ready_time); 
        
    virtual ~CDare();

    /**
     * \brief 时间事件处理回调函数,由TimeTick.cpp中函数回调
     *
     *  当对战处于DARE_READY状态五分钟,则取消对战,并进入DARE_RETURN_GOLD状态
     *  当对战处于DARE_READY_QUESTION  当对战处于DARE_READY
     *
     *
     */
    virtual void timer();  //时间事件处理回调


    // 以下为设置对战状态的处理方法。对战状态具体查看对战系统状态转换图
    // 状态转换函数默认情况,皆不需要重载。只需重载指定的几个方法。
    // 如果你想实现一个与默认行为不同的状态转换过程。可能需要重载所有状态转换方法
    
    virtual void setReadyState();
    virtual void setReadyQuestionState();
    virtual void setReadyActiveState(UserSession* pUser);
    virtual void setReturnGoldState();
    virtual void setActiveState();
    virtual void setReadyOverState();
    virtual void setWaitBountyState();
    virtual void setOverState();
    virtual void sendAntiAtt(){};

    virtual void setSecondID(DWORD dwID)=0;
    virtual void addFirstID(DWORD dwID)=0;
    virtual bool isInvalid() {return false; }
    
    // 该社会关系是否属于该对战记录的攻方
    virtual bool isAtt(DWORD dwID);
    
    virtual void notifyWarResult(int winner_type) = 0;

    /**
     * \brief 发送对战进行状态给场景
     *
     *  场景对相应玩家添加对战记录,在sendNineToMe时,进行对战状态的计算,该
     *  函数只在用户上线处理时被调用。
     *
     */
    virtual void sendActiveStateToScene(UserSession* pUser);


    /**
      * \brief 发送命令给所有参与该对战的玩家
      *
      * 发送对战命令给场景。由setActiveState和setReadyOverState函数调用
      *
      */
    virtual void 
    sendCmdToAllDarePlayer(Cmd::Session::t_enterWar_SceneSession* cmd,
        DWORD cmdLen,DWORD relationID) = 0;

    /**
      * \brief 判断是否仍在对战时期
      *
      * \return 如果仍在对战时期,返回TRUE,否则返回FALSE
      */
    virtual bool isActivePeriod()
    {
      time_t cur_time = time(NULL);
      return (cur_time-start_time)<this->active_time ? true : false;
    }

    /**
      * \brief 判断是否仍在准备期
      *
      * \return 如果仍在准备期时期,返回TRUE,否则返回FALSE
      */
    virtual bool isReadyPeriod()
    {
      return this->count<this->ready_time ? true : false;
    }

    /**
      * \brief 更新计数器
      *
      */
    virtual void updateTime()
    {
      rwlock.wrlock();
      this->count += 5;
      rwlock.unlock();
    }

    /**
     * \brief 战斗加分
     *
     *  调用一次,给相应的社会团队加上PK人数一人。得分公式如下：
     *  grade = grade + user.level/10;
     *
     * \param pAtt 攻击方
     * \param pDef 防守方
     */
    virtual void addGrade(UserSession* pAtt,UserSession* pDef) = 0;

    void  printState();


    DWORD type;    // 战斗类型:Cmd::UNION_DARE,Cmd::SCHOOL_DARE,Cmd::SEPT_DARE
    
    //DWORD firstID;    // 挑战方社会关系ID1
    std::vector<DWORD> attList;  // 挑战方列表
    DWORD secondID;    // 防守方社会关系ID2

    DWORD userid1;       // 挑战者ID
    DWORD userid2;       // 应战者ID
    DWORD grade1;           // 对战团体1的所得分数
    DWORD grade2;    // 对战团体2的所得分数
    DWORD pk1;              // 社会关系1PK人数
    DWORD pk2;              // 社会关系2PK人数
    DWORD count;    // 记数单位为秒
    BYTE  state;         // 所处状态
    DWORD dwWinnerID;  // 最终的赢家ID,用于多个攻方时使用
    bool  isAntiAtt;  // 设置反攻标志
};


class CDareUnion : public CDare
{
  public:
    CDareUnion();
    CDareUnion(DWORD active_time,DWORD ready_time);
    virtual ~CDareUnion();

  public:    
    // 以下为设置对战状态的处理方法。对战状态具体查看对战系统状态转换图
    virtual void setSecondID(DWORD dwID);
    virtual void addFirstID(DWORD dwID);

    virtual void sendCmdToAllDarePlayer(Cmd::Session::t_enterWar_SceneSession* cmd,DWORD cmdLen,DWORD relationID);
    virtual void sendActiveStateToScene(UserSession* pUser);
    virtual void notifyWarResult(int winner_type);

    /**
     * \brief 战斗加分
     *
     *  调用一次,给相应的社会团队加上PK人数一人。得分公式如下：
     *  grade = grade + user.level/10;
     *
     * \param pAtt 攻击方
     * \param pDef 防守方
     */
    virtual void addGrade(UserSession* pAtt,UserSession* pDef);

    virtual void timer();
    virtual bool isInvalid();

  protected:    
    virtual char* getFirstName();
    virtual DWORD getSecondUserID();
};

class CDareSchool : public CDare
{
  public:
    CDareSchool();
    virtual ~CDareSchool();

  public:    
    // 以下为设置对战状态的处理方法。对战状态具体查看对战系统状态转换图
    virtual void setSecondID(DWORD dwID);
    virtual void addFirstID(DWORD dwID);
    
    virtual void sendCmdToAllDarePlayer(Cmd::Session::t_enterWar_SceneSession* cmd,DWORD cmdLen,DWORD relationID);
    virtual void sendActiveStateToScene(UserSession* pUser);
    virtual void notifyWarResult(int winner_type);

    /**
     * \brief 战斗加分
     *
     *  调用一次,给相应的社会团队加上PK人数一人。得分公式如下：
     *  grade = grade + user.level/10;
     *
     * \param pAtt 攻击方
     * \param pDef 防守方
     */
    virtual void addGrade(UserSession* pAtt,UserSession* pDef);

  protected:    
    virtual char* getFirstName();
    virtual DWORD getSecondUserID();

//    CSchool* pFirst;
//    CSchool* pSecond;
};

class CDareUnionCity : public CDareUnion
{
  public:
    CDareUnionCity(DWORD active_time,DWORD ready_time);
    virtual ~CDareUnionCity();

  public:    
    virtual void setSecondID(DWORD dwID){CDareUnion::setSecondID(dwID);}
    virtual void addFirstID(DWORD dwID){CDareUnion::addFirstID(dwID);}
    
    virtual void sendCmdToAllDarePlayer(Cmd::Session::t_enterWar_SceneSession* cmd,
        DWORD cmdLen,DWORD relationID)
    {
      CDareUnion::sendCmdToAllDarePlayer(cmd,cmdLen,relationID);
    }
    
    virtual void sendActiveStateToScene(UserSession* pUser)
    {
      CDareUnion::sendActiveStateToScene(pUser);
    }
    
    virtual void setReadyState();
    virtual void setReadyOverState();

    /**
        * \brief 对战结果通知
      *
      * \param winner_type 结果类型:0 挑战者胜,1 应战者胜,2 战平
      *      
      */
     virtual void notifyWarResult(int winner_type){};

    virtual void timer();  //时间事件处理回调

    /**
     * \brief 战斗加分
     *
     *  调用一次,给相应的社会团队加上PK人数一人。得分公式如下：
     *  grade = grade + user.level/10;
     *
     * \param pAtt 攻击方
     * \param pDef 防守方
     */
    virtual void addGrade(UserSession* pAtt,UserSession* pDef){};
    int last_fulltime;
};

class CDareCountry : public CDare
{
  public:
    CDareCountry();
    CDareCountry(DWORD active_time,DWORD ready_time);
    virtual ~CDareCountry();

  public:    
    // 以下为设置对战状态的处理方法。对战状态具体查看对战系统状态转换图
    virtual void setSecondID(DWORD dwID);
    virtual void addFirstID(DWORD dwID);
    virtual void sendCmdToAllDarePlayer(Cmd::Session::t_enterWar_SceneSession* cmd,DWORD cmdLen,DWORD relationID);

    virtual bool isInvalid();

    virtual void setActiveState();
    virtual void setReadyOverState();
    virtual void notifyWarResult(int winner_type) {};
    virtual void addGrade(UserSession* pAtt,UserSession* pDef){};

    virtual void sendAntiAtt();
    virtual void sendActiveStateToScene(UserSession* pUser);
    
    virtual void timer();
};

class CDareAntiCountry : public CDareCountry
{
  public:
    CDareAntiCountry();
    CDareAntiCountry(DWORD active_time,DWORD ready_time);
    virtual ~CDareAntiCountry();

  public:    
    // 只重载结束处理.
    virtual void setReadyOverState();
};


class CDareSept : public CDare
{
  public:
    CDareSept();
    CDareSept(DWORD active_time,DWORD ready_time);
    virtual ~CDareSept();

  public:    
    // 以下为设置对战状态的处理方法。对战状态具体查看对战系统状态转换图
    virtual void setSecondID(DWORD dwID);
    virtual void addFirstID(DWORD dwID);
    virtual bool isInvalid();

    virtual void setReadyQuestionState();
    virtual void setReadyActiveState(UserSession* pUser);
    virtual void setReturnGoldState();
    virtual void setReadyOverState();
    
    virtual void sendCmdToAllDarePlayer(Cmd::Session::t_enterWar_SceneSession* cmd,DWORD cmdLen,DWORD relationID);
    virtual void sendActiveStateToScene(UserSession* pUser);
     virtual void notifyWarResult(int winner_type);

    /**
     * \brief 战斗加分
     *
     *  调用一次,给相应的社会团队加上PK人数一人。得分公式如下：
     *  grade = grade + user.level/10;
     *
     * \param pAtt 攻击方
     * \param pDef 防守方
     */
    virtual void addGrade(UserSession* pAtt,UserSession* pDef);
    virtual void timer();

    int dwDareRepute;
  protected:    
    virtual char* getFirstName();
    virtual DWORD getSecondUserID();

};


/**
 * \brief 家族NPC争夺战 
 *
 */
class CDareSeptNpc : public CDareSept
{
  public:
    CDareSeptNpc(DWORD active_time,DWORD ready_time);
    virtual ~CDareSeptNpc();

  public:    
    virtual void setSecondID(DWORD dwID){CDareSept::setSecondID(dwID);}
    virtual void addFirstID(DWORD dwID){CDareSept::addFirstID(dwID);}
    
    virtual void sendCmdToAllDarePlayer(Cmd::Session::t_enterWar_SceneSession* cmd,DWORD cmdLen,DWORD relationID)
    {
      CDareSept::sendCmdToAllDarePlayer(cmd,cmdLen,relationID);
    }
    
    virtual void sendActiveStateToScene(UserSession* pUser)
    {
      CDareSept::sendActiveStateToScene(pUser);
    }

    /**
        * \brief 对战结果通知
      *
      * \param winner_type 结果类型:0 挑战者胜， 1 应战者胜， 2 战平
      *      
      */
     virtual void notifyWarResult(int winner_type){};

    /**
     * \brief 战斗加分
     *
     *  调用一次，给相应的社会团队加上PK人数一人。得分公式如下：
     *  grade = grade + user.level/10;
     *
     * \param pAtt 攻击方
     * \param pDef 防守方
     */
    virtual void addGrade(UserSession* pAtt,UserSession* pDef){};
    
    virtual void setReadyOverState();
};

class CDareEmperor : public CDare
{
  public:
    CDareEmperor();
    CDareEmperor(DWORD active_time,DWORD ready_time);
    virtual ~CDareEmperor();

  public:    
    // 以下为设置对战状态的处理方法。对战状态具体查看对战系统状态转换图
    virtual void setSecondID(DWORD dwID);
    virtual void addFirstID(DWORD dwID);
    virtual bool isInvalid();

    virtual void setActiveState();
    virtual void setReadyOverState();
    
    virtual void sendCmdToAllDarePlayer(Cmd::Session::t_enterWar_SceneSession* cmd,DWORD cmdLen,DWORD relationID)
    {}

    virtual void addGrade(UserSession* pAtt,UserSession* pDef){};
    virtual void notifyWarResult(int winner_type) {};

    virtual void timer();
};

class CDareRecord
{
  public:
    CDareRecord()
    {
      dwTime = 0;
      dwAttCountryID = 0;
      dwDefCountryID = 0;
      dwResult = 0;
      bzero(attKingName,sizeof(attKingName));
      bzero(defKingName,sizeof(defKingName));
    }
    
    ~CDareRecord()
    {
    }
    
    void init(DBRecord* rec);
    //void writeDatabase();
    bool insertDatabase();
    //bool isMe(DWORD country,DWORD cityid,DWORD unionid);
    //bool changeUnion(DWORD unionid);

    DWORD  dwTime;
    DWORD  dwAttCountryID;
    DWORD  dwDefCountryID;
    DWORD  dwResult;
    char    attKingName[MAX_NAMESIZE+1];
    char    defKingName[MAX_NAMESIZE+1];

    zRWLock rwlock;

};

class CDareRecordM : public Singleton<CDareRecordM>
{
  friend class SingletonFactory<CDareRecordM>;
  
  public:
    bool init();
    void timer();
    void destoryMe()
    {
      delMe();
    };

    bool load();
    bool addNewDareRecord(DWORD dwAttCountry,DWORD dwDefCountry,DWORD dwResult);
    bool processUserMessage(UserSession *pUser,const Cmd::stNullUserCmd *pNullCmd,const DWORD cmdLen);
    CDareRecord* findLastRecord(DWORD dwAttCountry,DWORD dwDefCountry);

  private:
    CDareRecordM(){}
    std::vector<CDareRecord*> vDareRecord;
    zRWLock rwlock;
};

class CNpcDareM
{
  public:
    CNpcDareM();
    bool init();
    static CNpcDareM &getMe();
    static void destroyMe();

    bool load();
    bool refreshDB();
    void timer();
    bool processUserMessage(UserSession *pUser,const Cmd::stNullUserCmd *pNullCmd,const DWORD cmdLen);
    bool processSceneMessage(const Cmd::t_NullCmd *pNullCmd,const DWORD cmdLen);
    void processRequest(Cmd::Session::t_NpcDare_Dare_SceneSession * rev);
    CNpcDareObj* findObject(DWORD country,DWORD mapid,DWORD npcid);
    bool searchSept(DWORD septid);
    CNpcDareObj* searchRecord(DWORD dwCountryID,DWORD dwMapID,DWORD dwNpcID);
    void doDare();
    void doResult();
    CNpcDareObj* getNpcDareObjBySept(DWORD septid);
    void processGetGold(Cmd::Session::t_NpcDare_GetGold_SceneSession *rev);
    void notifyDareReady();
    void forceProcessResult();
    void sendUserData(UserSession *pUser);
    CNpcDareObj* searchSeptHold(DWORD septid);
    template <class YourEntry>
    bool execEveryOne(execEntry<YourEntry> &exec)
    {
      std::vector<CNpcDareObj*>::iterator iter;
      for(iter = _objList.begin() ; iter != _objList.end() ; iter ++)
      {
        exec.exec((YourEntry*)*iter);
      }
      return true;
    }
  private:
    static CNpcDareM * um;
    std::vector<CNpcDareObj*> _objList;
    bool _notDare;
    bool _notifyDareMessage;
};

using namespace NpcDareDef;

class CNpcDareObj
{
  public:
    void create(NpcDareDef::NpcDareRecord &);
    void writeDatabase();
    bool isMe(DWORD country,DWORD mapid,DWORD npcid);
    void dareRequest(DWORD userId);
    bool doDare();
    void processResult(DWORD septid);
    void processGetGold(UserSession *pUser,DWORD septid,DWORD dwNpcID,DWORD dwMapID,DWORD dwCountryID);
    static void itemBack(UserSession *pUser);
    void doResult();
    bool notifyDareReady();
    void forceProcessResult();
    DWORD get_country();
    DWORD get_mapid();
    DWORD get_npcid();
    DWORD get_holdseptid();
    DWORD get_dareseptid();
    DWORD get_gold();
    DWORD get_posx();
    DWORD get_posy();

    void abandon_npc();

  private:
    DWORD _dwCountry;
    DWORD _dwMapID;
    DWORD _dwNpcID;
    DWORD _dwHoldSeptID;
    DWORD _dwDareSeptID;
    DWORD _dwGold;
    DWORD _dwPosX;
    DWORD _dwPosY;
    DWORD _dwResultHold;
    DWORD _dwResultDare;
    BYTE  _dareStep;
    zRTime resultTime;
};

extern DWORD quiz_active_time;
extern DWORD quiz_ready_time;
typedef zUniqueID<QWORD> zUniqueDWORDID;

/**
 * \brief 答题记录管理类
 *
 * 管理答题记录的容器,使用Singleton模式
 */
class CQuizM : public zEntryMgr<zEntryTempID>,
         public Singleton<CQuizM>
{
  friend class SingletonFactory<CQuizM>;

  private:
    zUniqueDWORDID *channelUniqeID;
    zRWLock rwlock;
    CQuizM();

  public:
    bool getUniqeID(QWORD &tempid);
    void putUniqeID(const QWORD &tempid);

    template <class YourEntry>
      bool execEveryOne(execEntry<YourEntry> &exec)
      {
        rwlock.rdlock();
        bool ret=execEveryEntry<>(exec);
        rwlock.unlock();
        return ret;
      }

    template <class YourEntry>
      void removeOne_if(removeEntry_Pred<YourEntry> &pred)
      {
        rwlock.wrlock();
        removeEntry_if<>(pred);
        rwlock.unlock();
      }

    ~CQuizM();
    bool init();
    static void destroyMe();

    /**
     * \brief 对战管理器的定时器回调函数
     *
     * 定时遍历所有对战记录,删除无效记录,结束达到时间的对战等相关处理。
     */
    void timer();
    void printSize();


          


    /**
     * \brief 处理用户的对战命令
     *
     * \param pUser 发送该命令的玩家相对应的UserSession对象
     * \param pNullCmd 收到的命令
     * \param cmdLen 命令长度
     * \return 是对战命令,并得到相应处理,返回为true,否则为false
     *
     */
    bool processUserMessage(UserSession *pUser,const Cmd::stNullUserCmd *pNullCmd,const DWORD cmdLen);

    /**
     * \brief 处理场景发送过来的服务器间消息
     *
     * \param cmd 场景服务器发送过来的命令指令
     * \param cmdLen 命令长度
     *
     * \return 是已定义的服务器间命令,并得到相应处理,返回true,否则为false.
     *
     */
    bool processSceneMessage(const Cmd::t_NullCmd *cmd,const DWORD cmdLen);

    /**
     * \brief 加入新的竞赛记录
     *
     * \param pCmd 命令指针
     * \return 没有重复记录,并加入成功,返回true,否则返回false
     *
     */
    bool addNewQuiz_sceneSession(Cmd::Session::t_createQuiz_SceneSession* pCmd);



    /**
     * \brief 查找全区竞赛记录
     *
     * \return 如果找到,返回对应指针,如果没有,返回NULL
     */
    CQuiz* findWorldQuiz();

    /**
     * \brief 查找个人问答记录
     *
     * \return 如果找到,返回对应指针,如果没有,返回NULL
     */
    CQuiz* findPersonalQuiz(DWORD dwUserID);
    
    /**
      * \brief 用户上线处理
      *
      * 用户上线时,同时判断该用户的竞赛状态,并做相应处理
      *
      * \param pUser 上线用户
      *
      */
    void userOnline(UserSession* pUser);
    
    /**
      * \brief 用户下线处理
      *
      * 用户下线时,同时判断该用户的竞赛状态,并做相应处理
      *
      * \param pUser 上线用户
      *
      */
    void userOffline(UserSession* pUser);
};


/**
 * \brief 参赛者
 *
 */
class CPothunter
{
  public:
    DWORD dwUserID;   // 参赛者ID
    int dwScore;    // 得分
    DWORD dwGrace;    // 本次文采得分
    int dwLuck;  // 幸运星使用次数

    int dwAnswerStatus; // 本次答题状态
    
    CPothunter()
    {
      dwUserID = 0;
      dwScore = 0;
      dwGrace = 0;
      dwLuck = 0;

      dwAnswerStatus = -1;
    }
    /*bool operator ==(CPothunter& ref)
    {
      return ref.dwUserID==this->dwUserID;
    }*/
    
    ~CPothunter(){}
};



class CSubject
{
  public:
    /*std::string title;
    std::string answer_a;
    std::string answer_b;
    std::string answer_c;
    std::string answer_d;
    */
    char title[256];
    char answer_a[56];
    char answer_b[56];
    char answer_c[56];
    char answer_d[56];
    char answer_e[56];
    char answer_f[56];

    DWORD answer;
    int  quiz_type; // 0为全国,1为个人,2为２０级

    CSubject(const CSubject& ref)
    {
      strcpy_s(this->title,ref.title);
      strcpy_s(this->answer_a,ref.answer_a);
      strcpy_s(this->answer_b,ref.answer_b);
      strcpy_s(this->answer_c,ref.answer_c);
      strcpy_s(this->answer_d,ref.answer_d);
      strcpy_s(this->answer_e,ref.answer_e);
      strcpy_s(this->answer_f,ref.answer_f);

      this->answer = ref.answer;
      this->quiz_type = ref.quiz_type;
    }

    CSubject()
    {
      answer=0;
      bzero(title,sizeof(title));
      bzero(answer_a,sizeof(answer_a));
      bzero(answer_b,sizeof(answer_b));
      bzero(answer_c,sizeof(answer_c));
      bzero(answer_d,sizeof(answer_d));
      bzero(answer_e,sizeof(answer_e));
      bzero(answer_f,sizeof(answer_f));
      quiz_type = 0;
    }

    const CSubject & operator= (const CSubject &ref)
    {
      strcpy_s(this->title,ref.title);
      strcpy_s(this->answer_a,ref.answer_a);
      strcpy_s(this->answer_b,ref.answer_b);
      strcpy_s(this->answer_c,ref.answer_c);
      strcpy_s(this->answer_d,ref.answer_d);
      strcpy_s(this->answer_e,ref.answer_e);
      strcpy_s(this->answer_f,ref.answer_f);
      
      this->answer = ref.answer;
      this->quiz_type = ref.quiz_type;
      return *this;
    }

    ~CSubject()
    {
#ifdef _DEBUG      
      Zebra::logger->debug("~CSubject:%s",this->title);
#endif        
    }
    
};

class CSubjectM : public Singleton<CSubjectM>
{
  public:
    ~CSubjectM();
    bool init();
    static void destroyMe();
    
    std::vector<CSubject> gsubjects;
    std::vector<CSubject> levels;
    std::vector<CSubject> personals;
    CSubjectM();
};

class CQuiz:public zEntry
{
  protected:
    zRWLock rwlock;                             // 读写锁

    /// 答题前的等待时间
    DWORD ready_time;

    /// ready_question持续时间,默认10秒
    DWORD ready_question_time;
    

    /// 竞赛当前状态
    BYTE state;

    /// 竞赛类型
    BYTE type;
    
    virtual void sendExitToAll(){};
    std::set<int> answered;


  public:
    /// 竞赛计时,从ready_question结束时重新置零后,再进行计时,默认进行30分钟
    DWORD count;

    /// 题库类型
    BYTE subject_type;

    DWORD active_time;

    /// 当前已答题目数
    DWORD cur_subject;

    /// 本次答题的总题数
    DWORD total_subject;

    /// 答题计时
    DWORD question_count;

    enum{
      QUIZ_READY,  // 邀请等待状态
      QUIZ_READY_QUESTION,  // 等待被邀应者回应状态,保持10秒
      QUIZ_SEND_QUESTION,// 发题状态
      QUIZ_ACTIVE_QUESTION,// 答题状态
      QUIZ_END_QUESTION,    // 结束本轮问答,并做相应处理(全区竞赛时,进行排序处理并发送排名与得分,
            // 个人问答仅进行得分和文采的发送)
      QUIZ_READY_OVER,      // 结束竞赛,通知场景取消所有人的对战状态,并计算输赢,重置查看排名时间
      QUIZ_READ_SORT,  // 该状态只用于全国,等待五秒时间后,在此状态再发送一次结束
      QUIZ_RETURN_GOLD,// 个人问答结束,但还未进行奖励
      QUIZ_OVER    // 结束清除状态
    };

    CQuiz();
    CQuiz(DWORD active_time,DWORD ready_time); 
        
    virtual ~CQuiz();

    /**
     * \brief 时间事件处理回调函数,由TimeTick.cpp中函数回调
     *
     *
     */
    void timer();  //时间事件处理回调


    // 以下为设置对战状态的处理方法。对战状态具体查看对战系统状态转换图
    // 状态转换函数默认情况,皆不需要重载。只需重载指定的几个方法。
    // 如果你想实现一个与默认行为不同的状态转换过程。可能需要重载所有状态转换方法
    
    virtual void setReadyState();
    virtual void setReadyQuestionState();
    virtual void setSendQuestionState();
    virtual void setActiveQuestionState();
    virtual void setEndQuestionState();
    virtual void setReadyOverState();
    virtual void setReturnGoldState();
    virtual void setReadSortState();
    virtual void setOverState();

    virtual bool addPothunters(UserSession* pUser) = 0;

    /**
     * \brief 打出竞赛当前状态
     *
     */
    void printState();

    /**
      * \brief 用户上线处理
      *
      * 用户上线时,同时判断该用户的竞赛状态,并做相应处理,个人问答上线不需处理。
      * 世界竞赛时,需要判断其是否已经参加了竞赛,如果没有参加,则发出询问,如果已经参加,则不再处理
      *
      * \param pUser 上线用户
      *
      */
    virtual void userOnline(UserSession* pUser) = 0;
    
    /**
      * \brief 用户下线处理
      *
      * 用户下线时,同时判断该用户的竞赛状态,并做相应处理,个人问答下线时,进入setReadyOver状态,全国竞赛时不做处理
      *
      * \param pUser 上线用户
      *
      */
    virtual void userOffline(UserSession* pUser) = 0;

    /**
      * \brief 判断是否仍在竞赛期间
      *
      * \return 如果仍在对战时期,返回TRUE,否则返回FALSE
      */
    virtual bool isActivePeriod()=0;

    /**
      * \brief 判断是否仍在准备期
      *
      * \return 如果仍在准备期时期,返回TRUE,否则返回FALSE
      */
    virtual bool isReadyPeriod()
    {
      return this->count<this->ready_time ? true : false;
    }
    
    /**
      * \brief 判断是否仍在准备期
      *
      * \return 如果仍在准备期时期,返回TRUE,否则返回FALSE
      */
    virtual bool isReadyQuestionPeriod()
    {
      return this->count<ready_question_time ? true : false;
    }


    /**
     * \brief  判断是否仍在查看排名期
     *
     */
    virtual bool isReadSortPeriod()
    {
      return this->count<5?true:false;
    }
    
    virtual bool isActiveQuestionPeriod()
    {
      return this->question_count<=20 ? true : false;
    }

    virtual bool isEndQuestionPeriod()
    {
      return this->question_count<=25 ? true : false;
    }
    
    /**
      * \brief 判断是否仍在准备期
      *
      * \return 如果仍在准备期时期,返回TRUE,否则返回FALSE
      */
    virtual void updateTime()
    {
      rwlock.wrlock();
      this->count += 1;
      this->question_count += 1;
      rwlock.unlock();
    }

    virtual BYTE getType()
    {
      return this->type;
    }

    virtual BYTE getState()
    {
      return this->state;
    }

    virtual int answer(Cmd::stAnswerQuiz* pCmd,DWORD dwUserID) = 0;
    virtual void exitQuiz(DWORD dwUserID) = 0;

    /// 本次竞赛的题目
    std::vector<CSubject>   subjects;
//    CSubject subjects[1];
//    int subjects[100];
};


class CQuizPersonal : public CQuiz
{
  public:
    CQuizPersonal();
    CQuizPersonal(DWORD active_time,DWORD ready_time);
    virtual ~CQuizPersonal();
    
    bool isActivePeriod()
    {
      return this->cur_subject<=total_subject;
    }
    
    void setSendQuestionState();
    void setEndQuestionState();
    void setReadyOverState();
    void setReturnGoldState();

    int answer(Cmd::stAnswerQuiz* pCmd,DWORD dwUserID);
    bool addPothunters(UserSession* pUser);
    void exitQuiz(DWORD dwUserID);
    
    /**
      * \brief 用户上线处理
      *
      * 用户上线时,同时判断该用户的竞赛状态,并做相应处理
      *
      * \param pUser 上线用户
      *
      */
    void userOnline(UserSession* pUser);
    void userOffline(UserSession* pUser);
    CPothunter pothunter;
  protected:
    bool award();
    UserSession* user;
};

class CQuizWorld : public CQuiz
{
  public:
    CQuizWorld();
    CQuizWorld(DWORD active_time,DWORD ready_time,BYTE subject_type=0);
    virtual ~CQuizWorld();

    void setSendQuestionState();
    void setEndQuestionState();
    void setReadyOverState();
    
    bool addPothunters(UserSession* pUser);
    int answer(Cmd::stAnswerQuiz* pCmd,DWORD dwUserID);
    
    void exitQuiz(DWORD dwUserID);

    bool isActivePeriod()
    {
      return this->cur_subject<=total_subject;
    }

    /**
      * \brief 用户上线处理
      *
      * 用户上线时,同时判断该用户的竞赛状态,并做相应处理
      *
      * \param pUser 上线用户
      *
      */
    void userOnline(UserSession* pUser);
    void userOffline(UserSession* pUser);
  public:    
    /// 参赛人员列表
    std::vector<CPothunter> pothunters;
//    int valid_pothunter; // 本轮有效人数
  private:
    virtual void sendExitToAll();

};

class RecordClient : public zTCPClient,public MessageQueue
{

  public:

    /**
     * \brief 构造函数
     * 由于档案数据已经是压缩过的，故在底层传输的时候就不需要压缩了
     * \param name 名称
     * \param ip 地址
     * \param port 端口
     */
    RecordClient(
        const std::string &name,
        const std::string &ip,
        const WORD port)
      : zTCPClient(name,ip,port,false) {};

    bool connectToRecordServer();

    void run();
    bool msgParse(const Cmd::t_NullCmd *pNullCmd,const DWORD nCmdLen);
    bool cmdMsgParse(const Cmd::t_NullCmd *,const DWORD);

};

extern RecordClient *recordClient;

class CSortM
{
  private:

    CSortM();

    static CSortM *csm;
    //WORD leveltable[MAX_LEVEL+10];

    /**
     * \brief 排序
     */
    struct ltqword
    {
      bool operator()(const QWORD s1,const QWORD s2) const
      {
        return s1>s2;
      }
    };
    std::multimap<QWORD,DWORD,ltqword> _sortKey;
    std::map<DWORD,QWORD> _sortMap;

    typedef std::multimap<QWORD,DWORD,ltqword>::value_type keyValueType;
    typedef std::map<DWORD,QWORD>::value_type mapValueType;

  public:
    ~CSortM();
    static CSortM &getMe();
    bool init();
    static void destroyMe();
    void onlineCount(UserSession *pUser);
    void onlineCount(DWORD dwCharID,WORD wdLevel,QWORD qwExp);
    void offlineCount(UserSession *pUser);
    WORD getLevelDegree(UserSession *pUser);
    void upLevel(UserSession *pUser);
    bool createDBRecord();
    bool clearDBTable();

};

class CVoteItem
{
  public:
    DWORD dwOption;
    char szOptionDesc[MAX_NAMESIZE + 1];
    DWORD dwBallot;
    DWORD dwVoteID;
    void init(DBRecord* rec);
    void writeDatabase();
    bool insertDatabase();
    bool deleteMeFromDB();
    CVoteItem();
    ~CVoteItem();
};

class CVote
{
  friend class CVoteM;
  public:
    enum
    {
      VOTE_READY,           // 准备状态
      VOTE_ACTIVE,          // 正在投票状态
      VOTE_READY_OVER,      // 结束投票，修改对应国家科技状态
      VOTE_OVER               // 结束清除状态
    };
    
    void init(DBRecord* rec);
    void writeDatabase();
    bool insertDatabase();
    bool deleteMeFromDB();
    bool loadItemFromDB();
    bool loadItemFromVec(std::vector<CTech*>& itemset);
    
    virtual void setReadyState();
    virtual void setActiveState();  
    virtual void setReadyOverState();
    virtual void setOverState();    
    virtual bool isActiveState();
    
    DWORD   getState()
    {
      return this->dwStatus;
    }

    DWORD   getType()
    {
      return this->dwType;
    }
    
    virtual void vote(UserSession* pUser,DWORD dwOption);
    bool addVoted(DWORD dwCharID);
    bool clearVoted();
    
    CVote();  
    virtual ~CVote();

  protected:
    DWORD dwID;
    DWORD dwCountryID;
    DWORD dwType;
    DWORD dwStatus;

    zRWLock rwlock;
    std::vector<CVoteItem*> items;
};

class CVoteM :   public Singleton<CVoteM>
{
  friend class SingletonFactory<CVoteM>;
  public:
    bool init();
    static void destroyMe();
    void timer();
    bool load();

    bool processUserMessage(UserSession *pUser,const Cmd::stNullUserCmd *pNullCmd,const DWORD cmdLen);
                bool processSceneMessage(const Cmd::t_NullCmd *pNullCmd,const DWORD cmdLen);

    CVote* find(DWORD dwCountryID,DWORD dwType);
    CVote* findByID(DWORD dwVoteID);
    
    ~CVoteM();
    
    bool createNewVote(DWORD dwCountry,DWORD dwType,std::vector<CTech*>& items);
    void removeVote(DWORD dwCountry,DWORD dwType);
    void removeVoteByID(DWORD dwID);
    void force_close_vote(DWORD dwCountryID,DWORD dwType);
    
  protected:
    CVoteM();
    std::vector<CVote*> votes;
    void addNewVote();
    zRWLock rwlock;
};


typedef zUniqueID<QWORD> zUniqueDWORDID;

struct ArhatMapPoint
{
  DWORD dwMapID;
  DWORD x;
  DWORD y;
};
const int mappoint_num = 10;

/**
 * \brief 护宝任务记录管理类
 *
 * 管理对战记录的容器,使用Singleton模式
 */
class CGemM:public zEntryMgr<zEntryTempID>,
      public Singleton<CGemM>
{
  friend class SingletonFactory<CGemM>;

  private:
  zUniqueDWORDID *channelUniqeID;
  zRWLock rwlock;

  CGemM();

  public:
  ~CGemM();

  bool getUniqeID(QWORD &tempid);
  void putUniqeID(const QWORD &tempid);

  template <class YourEntry>
    bool execEveryOne(execEntry<YourEntry> &exec)
    {
      rwlock.rdlock();
      bool ret=execEveryEntry<>(exec);
      rwlock.unlock();
      return ret;
    }

  template <class YourEntry>
    void removeOne_if(removeEntry_Pred<YourEntry> &pred)
    {
      rwlock.wrlock();
      removeEntry_if<>(pred);
      rwlock.unlock();
    }

  ArhatMapPoint wait_point[mappoint_num];
  bool init();
  static void destroyMe();

  /**
   * \brief 护宝任务管理器的定时器回调函数
   *
   * 定时遍历所有对战记录,删除无效记录,结束达到时间的对战等相关处理。
   */
  void timer();


  /**
   * \brief 处理用户的对战命令
   *
   * \param pUser 发送该命令的玩家相对应的UserSession对象
   * \param pNullCmd 收到的命令
   * \param cmdLen 命令长度
   * \return 是护宝任务相关命令,并得到相应处理,返回为true,否则为false
   *
   */
  bool processUserMessage(UserSession *pUser,const Cmd::stNullUserCmd *pNullCmd,const DWORD cmdLen);

  /**
   * \brief 处理场景发送过来的服务器间消息
   *
   * \param cmd 场景服务器发送过来的命令指令
   * \param cmdLen 命令长度
   *
   * \return 是已定义的服务器间命令,并得到相应处理,返回true,否则为false.
   *
   */
  bool processSceneMessage(const Cmd::t_NullCmd *cmd,const DWORD cmdLen);

  /**
   * \brief 查找符合条件的护宝任务
   *
   *  当ID2为0时,查找是否有ID1参战的记录。dwType参数必须输入。
   *
   * \param dwType 对战类型:Cmd:UNION_DARE,Cmd:SCHOOL_DARE,Cmd:SEPT_DARE
   * \param dwID1  攻方ID
   * \param dwID2  守方ID
   *
   * \return 找到则返回对应对战记录的指针
   */
  CGem * findGem(DWORD dwCountryID);

  /**
   * \brief 根据ID查找护宝任务
   *
   * \param dwID  GEM ID
   *
   * \return 找到则返回对应护宝任务记录的指针
   */
  CGem*  findGemByID(DWORD dwID);

  /**
   * \brief 加入新的对战记录
   *
   * \param dwCountryID 任务所属国家
   *
   * \return 没有重复记录,并加入成功,返回true,否则返回false
   *
   */
  bool addNewGem(DWORD dwCountryID);
        

  void forceEnd();

  /**
   * \brief 用户上线处理
   *
   * 用户上线时,同时判断该用户的对战状态,并做相应处理
   *
   * \param pUser 上线用户
   *
   */
  void userOnline(UserSession* pUser);
  
  /**
   * \brief 用户下线处理
   *
   * 用户下线时,同时状态他所处的护宝状态,并做相应处理
   *
   * \param pUser 下线用户
   *
   */
  void userOffline(UserSession* pUser);
};

/// 罗汉
class CArhat
{
  public:
  DWORD x;
  DWORD y;
  DWORD dwCountryID;
  DWORD dwMapRealID;
  BYTE  byState; // 状态,0为道具未被人获取,1为道具已被人获取
  DWORD dwHoldUserID; // 道具目前所属玩家ID
  DWORD dwID;  // 罗汉的ID

  CArhat()
  {
    x = 0;
    y = 0;
    dwCountryID = 0;
    dwMapRealID = 0;
    byState = 0;
    dwHoldUserID = 0;
    dwID = 0;
  }

  bool refreshNPC();
  bool clearNPC();
};

class CGem : public zEntry
{
  protected:
    zRWLock rwlock;                             // 读写锁
    time_t tmStart;            // 开始时间

  public:
    enum{
      GEM_READY,  // 护宝任务准备状态
      GEM_ACTIVE,  // 护宝任务进行状态
      GEM_READY_OVER,      // 护宝任务准备结束状态
      GEM_OVER    // 结束清除状态
    };

    CGem();

    virtual ~CGem();

    /**
     * \brief 时间事件处理回调函数,由TimeTick.cpp中函数回调
     *
     *  当对战处于DARE_READY状态五分钟,则取消对战,并进入DARE_RETURN_GOLD状态
     *  当对战处于DARE_READY_QUESTION  当对战处于DARE_READY
     *
     *
     */
    virtual void timer();  //时间事件处理回调


    // 状态处理方法,由timer做状态变迁的处理
    virtual void setReadyState();
    virtual void setActiveState();
    virtual void setReadyOverState();
    virtual void setOverState();

    /**
     * \brief 发送对战进行状态给场景
     *
     *  场景对相应玩家添加对战记录,在sendNineToMe时,进行对战状态的计算,该
     *  函数只在用户上线处理时被调用。
     *
     */
    virtual void sendActiveStateToScene(UserSession* pUser);

    /**
     * \brief 判断是否仍在护宝任务时期
     *
     * \return 如果仍在护宝任务时期,返回TRUE,否则返回FALSE
     */
    virtual bool isActivePeriod();

    void  printState();

    void    holdDragon(UserSession* pUser);
    void    holdTiger(UserSession* pUser);

    void    resetDragon();
    void    resetTiger();

    CArhat dragon; // 龙精
    CArhat tiger;   // 虎魄
    BYTE   state;         // 所处状态
    DWORD  dwCountryID;  // 护宝任务所属国家
};


class CCaptain
{//队长
  public:
    DWORD dwArmyID; // 军队ID
    DWORD dwCharID; // 队长ID
    char  szCapName[MAX_NAMESIZE + 1]; // 队长姓名
    DWORD dwNpcNum; // 队长带领的NPC数，暂时未用
    CArmy* myArmy;
    
    void init(DBRecord* rec);
    void writeDatabase();
    bool insertDatabase();
    bool deleteMeFromDB();
    void update_scene();
    void fireMe();

    CCaptain();
    ~CCaptain();
};

class CArmy
{
  friend class CArmyM;
  friend class CCaptain;
  public:
    void init(DBRecord* rec);
    void writeDatabase();
    bool insertDatabase();
    bool deleteMeFromDB();
    bool loadCaptainFromDB();

    bool fireCaptain(DWORD dwUserID);
    bool hireCaptain(DWORD dwUserID);
    void changeName(const char* newname);
    void update_all_captain();
    bool canAddCaptain();
    
    CArmy();
    ~CArmy();
    enum
    {
      WAIT_CREATE = 1,
      FINISH_CREATE = 2,
    };

    void status(BYTE value)
    {
      rwlock.wrlock();
      byStatus = value;
      rwlock.unlock();
    }

  protected:
    DWORD dwID; // 军队ID
    DWORD dwCountryID; // 所属国家ID
    DWORD dwCityID;  // 所属城市ID
    
    char  name[MAX_NAMESIZE + 1]; // 军队名称
    DWORD  dwGenID; // 军队将军角色ID
    char  genName[MAX_NAMESIZE + 1]; // 军队将军名字

    BYTE  byStatus;
    DWORD dwCreateTime;

    zRWLock rwlock;
    std::vector<CCaptain*> captains;
};

class CArmyM : public Singleton<CArmyM>
{
  friend class SingletonFactory<CArmyM>;
  public:
    bool init();
    static void destroyMe();
    void timer();
    bool load();
    
    bool processUserMessage(UserSession *pUser,const Cmd::stNullUserCmd *pNullCmd,const DWORD cmdLen);
    bool processSceneMessage(const Cmd::t_NullCmd *pNullCmd,const DWORD cmdLen);

    void processReqWaitGen(UserSession* pUser,Cmd::stReqWaitGenUserCmd* rev);
    void processCreateArmy(UserSession* pUser,Cmd::stCreateArmyUserCmd* rev);
    void processChangeArmyName(UserSession* pUser,Cmd::stChangeArmyNameUserCmd* rev);
    
    void processReqArmyList(Cmd::Session::t_ReqArmyList_SceneSession* rev);
    void processReqArmySpec(UserSession* pUser,Cmd::stReqArmySpecUserCmd* rev);
    void processExitArmy(UserSession* pUser,Cmd::stExitArmyUserCmd* rev);
    void processRemoveArmy(UserSession* pUser,Cmd::stRemoveArmyUserCmd* rev);
    void processAddCaptain(UserSession* pUser,Cmd::stAddArmyCaptainUserCmd* rev);
    void processFireCaptain(UserSession* pUser,Cmd::stFireArmyCaptainUserCmd* rev);
    
    void userOnline(UserSession *pUser);
    
    //CArmy* find(DWORD dwCountryID,DWORD dwCityID);
    int    countByCity(DWORD dwCountryID,DWORD dwCityID);
    CArmy* findByID(DWORD dwArmyID);
    CArmy* findByGenID(DWORD dwGenID);
    CArmy* findByName(const char* value);

    bool  addCaptain(DWORD dwUserID,CCaptain* pCaptain);
    bool  removeCaptain(DWORD dwUserID);
    bool    isCaptain(DWORD dwUserID);

    ~CArmyM();
    void removeArmyByID(DWORD dwArmyID);
    void removeArmyByGenID(DWORD dwGenID);

    std::vector<CArmy*> armys;
    /// 类型定义
    typedef std::map<DWORD,CCaptain*>::value_type captainIndexValueType;
        
    typedef std::map<DWORD,CCaptain *>::iterator capIter;
    std::map<DWORD,CCaptain*> captainIndex;
    

  protected:
    CArmyM();
    zRWLock rwlock;
};


class RecommendSub
{
  public:
    char name[MAX_NAMESIZE + 1]; // 被推荐人姓名
    DWORD id; // 被推荐人用户ID
    DWORD lastLevel; // 最后一次提取奖励的等级
    DWORD recommendid; // 推荐人ID
    DWORD dwTotal; // 累计已领取的金额

    Recommend*  myRecommend; // 我的推荐人
    void init(DBRecord* rec);
    void writeDatabase();
    bool insertDatabase();
    bool deleteMeFromDB();
    bool fireMe();
    void pickupBounty(UserSession* pUser);
    DWORD queryBounty();
    DWORD queryTotal()
    {
      return dwTotal;
    }

    RecommendSub();
    ~RecommendSub();
};

class Recommend
{
  friend class RecommendM;
  friend class RecommendSub;

  public:
    void init(DBRecord* rec);
    void writeDatabase();
    bool insertDatabase();
    bool deleteMeFromDB();
    bool loadRecommendSubFromDB();

    bool addRecommended(DWORD dwUserID);
    void rmRecommended(DWORD dwUserID);
    void processQuery(UserSession* pUser);

    void pickupBounty(UserSession* pUser);
    DWORD queryBounty()
    {
      return this->dwBalance;
    }

    DWORD queryTotal()
    {
      return this->dwTotal;
    }
    

    Recommend();
    ~Recommend();
      
  protected:
    DWORD id; // 推荐人ID
    char  name[MAX_NAMESIZE + 1]; // 推荐人名字
    DWORD dwBalance;  // 推荐人可以提取的奖励
    DWORD dwTotal;    // 累积领取的奖励
    std::vector<RecommendSub*> subs; // 被推荐人列表
    zRWLock rwlock;
};

class RecommendM : public Singleton<RecommendM>
{
  friend class SingletonFactory<RecommendM>;
  public:
    bool init();
    static void destroyMe();
    void timer();
    bool load();

    bool processUserMessage(UserSession *pUser,const Cmd::stNullUserCmd *pNullCmd,const DWORD cmdLen);
    bool processSceneMessage(const Cmd::t_NullCmd *pNullCmd,const DWORD cmdLen);
    void processAddRecommended(const Cmd::Record::t_chkUserExist_SessionRecord* cmd);

    Recommend* findByID(DWORD dwUserID);
    RecommendSub* findSubByID(DWORD dwUserID);

    bool addRecommend(DWORD dwUserID,Recommend* r);
    bool addRecommendSub(DWORD dwUserID,RecommendSub* rs);
    void removeRecommend(DWORD dwUserID);
    bool removeRecommendSub(DWORD dwUserID);

    void fireRecommendSub(DWORD dwUserID);

    ~RecommendM();
    
    typedef std::map<DWORD,Recommend*>::value_type recommendValueType;
    typedef std::map<DWORD,Recommend*>::iterator recommendIter;
    std::map<DWORD,Recommend*> recommends;
    /// 类型定义
    typedef std::map<DWORD,RecommendSub*>::value_type recommendsubIndexValueType;
        
    typedef std::map<DWORD,RecommendSub *>::iterator resubIter;
    std::map<DWORD,RecommendSub*> recommendsubIndex;
  protected:
    RecommendM();
    zRWLock rwlock;
};

#pragma pack(1)
struct actInfo
{
  DWORD id;
  char name[MAX_NAMESIZE + 1];
  BYTE state;
  char text[MAX_CHATINFO + 1];
};
#pragma pack()

class Gift : public Singleton<Gift>
{
  friend class SingletonFactory<Gift>;
  private:
    Gift();

    static std::vector<actInfo> actList;
    static std::multimap<DWORD,Cmd::Session::giftInfo> giftList;
    static std::multimap<DWORD,std::string> winnerList;
    static DWORD loadActList();
    static DWORD loadGiftList();
  public:
    ~Gift();
    bool init();

    bool doGiftCmd(UserSession * pUser,const Cmd::stNullUserCmd *cmd,const DWORD cmdLen);
};

class EmperorForbid : public Singleton<EmperorForbid>
{
  friend class SingletonFactory<EmperorForbid>;
  private:
    std::vector<DWORD> list;

    void loadDB();
    void writeDB();

    EmperorForbid();

    void clear();
    bool find(DWORD);
  public:
    ~EmperorForbid();

    void timer();
    DWORD count();
    bool add(DWORD);
};

struct forbidInfo
{
  char name[MAX_NAMESIZE+1];
  QWORD startTime;
  int delay;
  WORD operation;
  char reason[256];
  char gm[MAX_NAMESIZE+1];
  WORD isValid;
};

class ForbidTalkManager
{
  private:
    static ForbidTalkManager *ftm;
    ForbidTalkManager();
    ~ForbidTalkManager();
  public:
    static ForbidTalkManager& getMe();
    static void delMe();

    static void checkDB();
};

using namespace std;


/**
* \sky 队伍场景遍历方法
*/
struct TeamSceneExec
{
	virtual ~TeamSceneExec(){};
	virtual bool exec(SceneSession * scene) = 0;
};

/**
* \sky 队伍遍历场景通知跟换队长消息
*/
struct TeamChangeLeaberSceneExec : public TeamSceneExec
{
	Cmd::Session::t_Team_ChangeLeader rev;

	TeamChangeLeaberSceneExec(DWORD TeamThisID, char * NewName)
	{
		rev.dwTeam_tempid = TeamThisID;
		strncpy(rev.NewLeaderName, NewName, MAX_NAMESIZE);
	}

	bool exec(SceneSession * scene)
	{
		scene->sendCmd(&rev, sizeof(Cmd::Session::t_Team_ChangeLeader));
		return true;
	}


};

/**
* \sky 队伍遍历场景通知增加队员消息
*/
struct TeamAddMemberSceneExec : public TeamSceneExec
{
	Cmd::Session::t_Team_AddMember rev;

	TeamAddMemberSceneExec(DWORD leaberID, DWORD TeamThisID, char * AddMemberName, DWORD dwID, DWORD face)
	{
		rev.dwLeaderID = leaberID;
		rev.dwTeam_tempid = TeamThisID;
		strncpy(rev.AddMember.name, AddMemberName, MAX_NAMESIZE);
		rev.AddMember.dwID = dwID;
		rev.AddMember.face = face;
	}

	bool exec(SceneSession * scene)
	{
		scene->sendCmd(&rev, sizeof(Cmd::Session::t_Team_AddMember));
		return true;
	}
};

/**
* \sky 队伍遍历场景通知删除队员消息
*/
struct TeamDelMemberSceneExec : public TeamSceneExec
{
	Cmd::Session::t_Team_DelMember rev;

	TeamDelMemberSceneExec(DWORD TeamID, char * DelName)
	{
		rev.dwTeam_tempid = TeamID;
		strncpy(rev.MemberNeam, DelName,MAX_NAMESIZE);
	}

	bool exec(SceneSession * scene)
	{
		scene->sendCmd(&rev, sizeof(Cmd::Session::t_Team_DelMember));
		return true;
	}
};

/**
/* \sky 队伍遍历场景通知删除队伍消息                                                                      
*/
struct TeamDelTeamSceneExec : public TeamSceneExec
{
	Cmd::Session::t_Team_DelTeam rev;

	TeamDelTeamSceneExec(DWORD TeamThisID)
	{
		rev.TeamThisID = TeamThisID;
	}

	bool exec(SceneSession * scene)
	{
		scene->sendCmd(&rev, sizeof(Cmd::Session::t_Team_DelTeam));
		return true;
	}
};

/**
 * \brief Session的队伍信息
 *
 */
struct Team
{
  Team():leaderid(0){};
  typedef set<DWORD> MemberSet;
  typedef set<SceneSession *> MapIDSet;
  typedef MemberSet::iterator MemberSet_iter;
  typedef MemberSet::const_iterator MemberSet_const_iter;

  //Sky 队伍跨越的场景的ID容器
  MapIDSet	MapID;

  private:
  MemberSet member;
  DWORD leaderid; //sky 队长ID
  DWORD dwTeam_tempid; //sky 队伍唯一ID
  

  
  public:
  bool addMember(const DWORD userid);
  bool delMember(const DWORD userid);
  bool setLeader(const DWORD leader);
  DWORD GetLeader();
  bool delTeam();
  //sky设置队伍的唯一ID
  void SetTeamThisID(DWORD TeamThisID);

  //sky 每当一个队伍成员跨场景的时候,都把他所移动到的地图放到场景容器中来
  //并且通知该场景跟新他的队伍管理器
  //还有发送给新场景队伍数据
  bool MemberMoveScen(SceneSession * scene);

  //sky新加跟换队长函数
  bool ChangeLeader(const char * leaberName=NULL);

  //sky遍历队伍所在的全部场景
  bool execEvery(TeamSceneExec &callback);

  //sky 跟新MapID容器
  void UpDataMapID(DWORD useID);

  //sky 获取特定队员ID
  DWORD GetMemberID(int i);

  //sky 获取队员数目
  DWORD GetMemberNum();
};

/**
 * \brief Session队伍管理器
 *
 */
class GlobalTeamIndex
{
private:
	GlobalTeamIndex(){};
	~GlobalTeamIndex(){};
	static GlobalTeamIndex *instance;

	typedef map<DWORD,Team> TeamMap;
	typedef TeamMap::value_type TeamMap_value_type;
	typedef TeamMap::iterator TeamMap_iterator;
	typedef TeamMap::const_iterator TeamMap_const_iterator;
	TeamMap team;
	zMutex mlock;

public:
	static GlobalTeamIndex *getInstance();
	static void delInstance();
	bool addMember(const DWORD tempid, const DWORD leaderid,const DWORD userid);
	bool delMember(const DWORD tempid,const char * userName);
	bool ChangeLeader( DWORD tempid, const char * leaberName=NULL);

	//sky 每当一个队伍成员跨场景的时候,都把他所移动到的地图放到场景容器中来
	//并且通知该场景跟新他的队伍管理器
	bool MemberMoveScen(const DWORD tempid, SceneSession * scene);

	//sky 根据队伍唯一ID返回一个队伍对象指针
	Team * GetpTeam(const DWORD tempid);

	//sky 删除队伍
	bool DelTeam(DWORD TeamThisID);

	//sky 跟新MapID容器
	void UpDataMapID(DWORD useID, DWORD TeamThisID);
};

//sky 队伍排队的结构
struct QueueTeamData
{
	QueueTeamData()
	{
		TeamID = 0;
		AddTime = 0;
	}

	DWORD	TeamID;		//ID
	QWORD	AddTime;	//排队的时间
};

//sky 排队管理类
class CQueueManager
{
private:
	std::vector<QueueTeamData>	WaitTeamID;		//sky 等待的队伍队列
	std::vector<DWORD>			WaitUserID;		//sky 等待的用户队列

public:
	CQueueManager();
	~CQueueManager();

	//sky 用户排队锁
	zMutex QueueUserLock;
	//sky 队伍排队锁
	zMutex QueueTeamLock;
	void Queue_AddUser(DWORD UserID);					//sky 将要排队的用户添加到排队序列中
	void Queue_AddTeam(DWORD UserID);		//sky 将要排队的队伍添加到排队序列中
	bool Queue_RemoveUser(DWORD * UserID, int num);		//sky 返回num个可以操作的用户ID并从排队序列中删除
	bool Queue_RemoveTeam(DWORD * UserID, int num);		//sky 返回num个可以操作的用户ID并从队伍排队序列中删除
	bool IfUserInWait(BYTE type, DWORD UserID);			//sky 用户是否已经存在当前队列中
};

struct CampData
{
	WORD Teamnum;			//sky 阵营成员数
	std::vector<DWORD> UserID;	//sky 分配好的成员
};

struct SceneMapData
{
	DWORD SceneID;
	Cmd::Session::CampPos pos[20];
};

typedef std::vector<CampData> tyCamp;

class CQueuingManager
{
private:
	//sky 按等级划分的排队序列
	std::map<DWORD, CQueueManager*> Queuing;

	//sky 已经创建好的战场ID
	std::vector<SceneMapData> sceneMapID;

	//sky 阵营保存容器,当场景申请成功并且满足MaxCampNum送入场景
	std::map<DWORD, tyCamp> Camp;
public:
	//sky 场景下标偏移值
	int MapIDMove;
	//sky 地图申请锁(避免因为场景的延迟处理导致不停申请)
	bool NewMapLock;
	//sky 对应的_ArenaMap的key(发送new地图消息需要用到)
	DWORD ManagerKey;
	//sky 关联地图ID
	DWORD MapBaseID;
	//sky 阵营最大人数
	WORD MaxTeamnum;
	//sky 战场需求阵营数
	WORD MaxCampNum;
	//sky 标志(false:从单身玩家队列中取 true:从队排玩家中取)
	bool bAccess;
public:
	CQueuingManager();
	~CQueuingManager();

	//sky 将要排队的用户添加到排队序列中
	void Queuing_AddUser(DWORD UserID, BYTE UserType);
	//sky 执行查询分配任务(主操作函数)
	void Queuing_Main();
	//sky 分配用户到已经生成好的地图中
	bool DistributionUser(int index);
	//sky 通知战场或者竞技场创建一个地图
	bool SendSceneNewMap(int index);
	//sky 将一个创建好的战场地图的放到战场容器里
	bool Queuing_AddScene(Cmd::Session::t_Sports_ReturnMapID * cmd);
	//sky 用户是否已经存在当前战场队列中
	bool IfUserInWaits(BYTE type, DWORD UserID);
};

//sky 战场竞技场队列管理类
class CArenaManager
{
private:
	std::map<DWORD,CQueuingManager*> _ArenaMap;		//sky 3c战场队列管理类
public:
	CArenaManager();
	~CArenaManager();

	//sky 将场景连接放到列表容器中
	void InsertBattleTask(SessionTask * pTask);
	//sky 将要排队的用户添加到相应的战场排队序列中
	void Arena_AddUser(Cmd::Session::t_Sports_AddMeToQueuing * cmd);
	void Arena_timer();
	//sky 读取配置文件构建战场队列
	bool LoadXmlToArena();
	//sky 把具体战场放到index索引的队列管理类下
	bool AddMapToQueuing(Cmd::Session::t_Sports_ReturnMapID * cmd);
	//sky 设置特定队列管理类的场景申请锁
	void NewMap_Lock(DWORD index, bool block);
	//sky 移动特定队列管理类的场景偏移
	void MoveSceneM(DWORD index);
	//sky 用户是否已经存在队列管理器中
	bool IfUserInQueuing(BYTE type, DWORD UserID);

	//sky 获取或者创建类的唯一实例
	static CArenaManager &getInstance()
	{
		if (NULL == instance)
			instance = new CArenaManager();

		return *instance;
	}

	//sky 释放类的唯一实例
	static void delInstance()
	{
		SAFE_DELETE(instance);
	}

private:
	//sky 类的唯一实例指针
	static CArenaManager *instance;
};

struct zMutex;
class zRTime;
/**
 * \brief 临时档案数据结构
 *
 */
struct TempArchive 
{
  TempArchive() 
  {
    id = 0;
    createtime = 0;
    dwSize = 0;
  }
  DWORD id;
  zRTime createtime;
  DWORD dwSize;
  char data[0];
};

/**
 * \brief 临时档案管理器
 *
 */
class GlobalTempArchiveIndex//:private zEntryManager< zEntryID >
{
  private:
    static GlobalTempArchiveIndex *_instance;
    typedef std::map<DWORD,TempArchive *> TempArchive_map;
    typedef TempArchive_map::iterator TempArchive_iterator;
    typedef TempArchive_map::value_type TempArchive_value_type;
    TempArchive_map tempArchive;
    zMutex mlock;

    GlobalTempArchiveIndex();
    ~GlobalTempArchiveIndex();
    void remove(TempArchive_iterator del_iter);
  public:
    static GlobalTempArchiveIndex *getInstance();
    static void delInstance();
    bool readTempArchive(DWORD id,char *out,DWORD &outSize);
    void checkOverdue();
    bool writeTempArchive(DWORD id,char *data,DWORD  dwSize);
};

class SessionTimeTick : public zThread
{

  public:

    static zRTime currentTime;

    ~SessionTimeTick() {};

    static SessionTimeTick &getInstance()
    {
      if (NULL == instance)
        instance = new SessionTimeTick();

      return *instance;
    }

    /**
     * \brief 释放类的唯一实例
     *
     */
    static void delInstance()
    {
      SAFE_DELETE(instance);
    }

    void run();

  private:
    Timer _five_sec;
    Timer _one_sec;
    Timer _one_min;
    Timer _ten_min;
    Timer _one_hour;
    Timer _five_min; // [ranqd Add] 五分钟定时器
    static SessionTimeTick *instance;

    SessionTimeTick() : zThread("TimeTick"),_five_sec(5),_one_sec(1),_one_min(60),_five_min(300),_ten_min(60*10),_one_hour(3480) {};

};

extern NFilterModuleArray g_nFMA;
