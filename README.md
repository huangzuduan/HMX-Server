# HMX-Server
HMX-Server分步式服务器框架，主要分为网关、登录、世界、场景、数据服务器，适用于大中小型项目

<b>安装步骤</b>：</br>
一、下载后，将Source/dependence/下的boost,protobuf里面的lib.rar解压到当前目录</br>
二、安装Cmake-3.4 x64以上版本,vs2015 x64 ,mysql5.6 x64
三、用Cmake进行创建方案然后并整个解决方案编译
四、导入Source/sql/下的hmx-data.sql数据，数据密码配置在Source/WorldServer/serices.xml文件中</br>
五、在vs中按顺序启动WorldServer.exe、BServer.exe、GameServer.exe、LoginServer.exe、GatewayServer.exe或在Bin/Debug/中双击RunServers.bat启动服务器。</br>
六、在vs中启动Client.exe或在Bin/Debug/双击Client.exe启动客户端进行测试



