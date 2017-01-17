@echo off


echo 开始生成
CALL protoc.exe  itemslots.proto --cpp_out=.
CALL protoc.exe  character.proto --cpp_out=.
CALL protoc.exe  sorlists.proto --cpp_out=.
CALL protoc.exe  chatmsg.proto --cpp_out=.

echo 生成文件完成
pause
