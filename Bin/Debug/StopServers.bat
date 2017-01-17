taskkill /F /IM GatewayServer.exe
ping 127.0.0.1 -n 1 >nul
taskkill /F /IM LoginServer.exe
ping 127.0.0.1 -n 1 >nul
taskkill /F /IM GameServer.exe
ping 127.0.0.1 -n 1 >nul
taskkill /F /IM WorldServer.exe
ping 127.0.0.1 -n 1 >nul
taskkill /F /IM DBServer.exe
