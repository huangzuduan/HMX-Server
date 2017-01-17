@echo off


#start "数据服2" DBServer.exe -c dp_cfg_1.xml
#ping 127.0.0.1 -n 1 >nul



#start "登录服2" LoginServer.exe -c ls_cfg_1.xml
#ping 127.0.0.1 -n 1 >nul



start "场景服2" GameServer.exe -c ss_cfg_1.xml
ping 127.0.0.1 -n 1 >nul




#start "网关服2" GatewayServer.exe -c fep_cfg_1.xml

#ping 127.0.0.1 -n 1 >nul



