@echo off


start "世界服" WorldServer.exe
ping 127.0.0.1 -n 1 >nul

start "数据库服" DBServer.exe
ping 127.0.0.1 -n 1 >nul

start "场景服" GameServer.exe
ping 127.0.0.1 -n 1 >nul

start "登录服" LoginServer.exe
ping 127.0.0.1 -n 1 >nul

start "网关服" GatewayServer.exe
ping 127.0.0.1 -n 1 >nul


