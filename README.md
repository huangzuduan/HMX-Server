Welcome to the HMX-Server wiki!
# HMX-Server
HMX-Server分步式服务器框架，主要分为网关、登录、世界、场景、数据服务器，适用于大中小型项目

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
![数据服](https://github.com/huangzuduan/HMX-Server/blob/master/Pics/ss.png?raw=true)

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
   11. LibProtocol/ Protocol协议类目录
   12. LibSrvcore/ 本项目共用类库
   13. LoginServer/ 登录服务器
   14. LogServer/ 日志服务器（数据库日志、暂未实现）
   15. MQServer/ 消息队列服务器（处理外部可延时事件，持久例事件处理，如充值、后台调用等；暂未实现）
   16. ShiftServer/ 区域管理服务器（暂未实现）
   17. sql/ 数据库更新记录目录
   18. WorldServer/ 世界服务器
4. vc14/ 这个是用cmake 生成的文件目录（名字自定）

# 服务器层级介绍
                                平台服                       <-----------平台服-------->Mysql(管理后台数据库)
                                  |
                               /      \
                           区域服1   区域服2
                                |
                             /     \                               世界服、数据服、登录服
                          世界服1  世界服N                    <------------------------>Mysql（游戏数据库）
                         / | \  \
                        /  |  \  | \
                       /   |   \ |   \
                   场景服1 场景服N \ <-> 数据服 <-> 登录服 
                       \   \     |     ---       /
                            \    |(世界服)       /
                             \   |             /
                            网关服1         网关服N

# NetSerivce.cpp 总管理器文件
1. 聚合了大部分该服务器的管理类，所有资源都需要从NetSerivce中获得，这样做的目的是将资源都聚合在一起，提供统一接口，方便记忆与管理，比如：你所找要的资源->NetSerivces实例对象->get各个资源类->get所需要的资源
2. NetSerivce也包括了main函数，启动程序的入口
3. serivces.xml配置文件以WorldServer/目录下的为准，当重新编译WorldServer时，会自动将它拷贝到Bin/Debug和vs项目调度目录下

 
