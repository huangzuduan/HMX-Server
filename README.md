Welcome to the HMX-Server wiki!
# HMX-Server
HMX-Server分步式服务器框架，主要分为网关、登录、世界、场景、数据服务器，适用于大中小型项目

版本更新记录：

1. 2017-01-17 更新所有文件，实现有基本的从登录到帐号数据保存的功能
2. 2017-03-19 优化了Socket、管理器方面的功能，实现二进制数据存储到mysql的功能
3. 2018-08-24 主要更新有：WebSocket的实现以及运用、在linux编译运行成功、作为房卡麻将游戏的服务器作了大量的测试，目前安全稳定。
	3-1. 增加了一个完整服务器的房卡麻将代码（后台、前端代码暂未能开源）。
	3-2. 登录服务器实现与后台网站的交互实现登录。
	3-3. 登录服记录登录的信息同步到世界服待用。
	3-4. 网关服实现麻将机器人自动托管打卡功能。
	3-5. 世界服管理离线在线用户的数据，及全服排行榜等等功能。
	3-6. 场景实现了用户数据管理，麻将逻辑的具体实现。
	3-7. 数据服实现玩家数据的缓存，以及其它数据的写读。


# 安装步骤
1. 下载后，将Source/dependence/下的boost,protobuf里面的lib.rar解压到当前目录
2. 安装Cmake-3.4 x64以上版本,vs2015 x64 ,mysql5.6 x64
3. 用Cmake进行创建方案然后并整个解决方案编译
4. 导入Source/sql/下的hmx-data.sql数据，数据密码配置在Source/WorldServer/serices.xml文件中
5. 在vs中按顺序启动WorldServer.exe、BServer.exe、GameServer.exe、LoginServer.exe、GatewayServer.exe或在Bin/Debug/中双击RunServers.bat启动服务器
5. 在vs中启动Client.exe或在Bin/Debug/双击Client.exe启动客户端进行测试

***
# 运行示例图

**世界服启动**
![世界服启动](https://github.com/huangzuduan/HMX-Server/blob/master/Pics/ws.png?raw=true)

**数据服**
![数据服](https://github.com/huangzuduan/HMX-Server/blob/master/Pics/dp.png?raw=true)

**场景服**
![场景服](https://github.com/huangzuduan/HMX-Server/blob/master/Pics/ss.png?raw=true)

**登录服**
![登录服](https://github.com/huangzuduan/HMX-Server/blob/master/Pics/ls.png?raw=true)

**网关服**
![网关服](https://github.com/huangzuduan/HMX-Server/blob/master/Pics/fep.png?raw=true)

**客户端**
![客户端](https://github.com/huangzuduan/HMX-Server/blob/master/Pics/client.png?raw=true)

# 目录介绍
1. Bin/Debug/ 编译存放目录
2. Resource/ 配置及资源目录
3. Source/ 源代码文件
   1. Client/ 测试客户端
   2. DBServer/ 数据库处理服
   3. dependence/ 第三方依赖库
   4. FlatServer/ 平台方案服（跨平台转发协议用，暂未实现）
   5. GameServer/ 场景服务器
   6. GatewayServer/ 网关服务器
   7. HelpTools/ 工具项目（用于生成数据、处理数据辅助开发用）
   8. Include/ 共用引入文件
   9. LibNetMysql/ Mysql数据库封装类库
   10. LibNetSocket/ Socket封装类库
   11. LibProto/ Protocol协议类目录
   12. LibCommon/ 本项目共用类库
   13. LoginServer/ 登录服务器
   14. LogServer/ 日志服务器（数据库日志、暂未实现）
   15. MQServer/ 消息队列服务器（处理外部可延时事件，持久例事件处理，如充值、后台调用等；暂未实现）
   16. ShiftServer/ 区域管理服务器（暂未实现）
   17. sql/ 数据库更新记录目录
   18. WorldServer/ 世界服务器
   19. Conf/ 配置文件，服务器ip、id、数据库配置
   20. shell/ linux的启动脚本
   21. makeall.sh 编译脚本
4. vc14/ 这个是用cmake 生成的文件目录（名字自定）

# 服务器层级介绍
                                平台服               <-----------平台服-------->Mysql(管理后台数据库)
                                  |
                               /      \
                           区域服1   区域服2
                                |
                             /     \                               世界服、数据服、登录服
                          世界服1  世界服N           <------------------------>Mysql（游戏数据库）
                         / | \  \
                        /  |  \  | \
                       /   |   \ |   \
                   场景服1 场景服N \ <-> 数据服 <-> 登录服  <--------------(1)---------->Client
                       \   \     |     ---       /											/
                            \    |(世界服)       /										/
                             \   |             /										/
                            网关服1         网关服N  		<--------------(2)----------

# GameService.cpp 总管理器文件
1. 聚合了大部分该服务器的管理类，所有资源都需要从NetSerivce中获得，这样做的目的是将资源都聚合在一起，提供统一接口，方便记忆与管理，比如：你所找要的资源->NetSerivces实例对象->get各个资源类->get所需要的资源
2. GameService也包括了main函数，启动程序的入口
3. 本框架最大优点是根据业务量的大小，可以扩展网关、登录服、场景服、数据服的数量，是一个分布式的框架。


 
