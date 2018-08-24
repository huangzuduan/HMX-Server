@echo off
echo 开始生成

rem 麻将协议文件
CALL protoc.exe  comdef.proto --cpp_out=./../maj/
CALL protoc.exe  idip.proto --cpp_out=./../maj/
CALL protoc.exe  msg_base.proto --cpp_out=./../maj/
CALL protoc.exe  msg_maj.proto --cpp_out=./../maj/
CALL protoc.exe  msg_login.proto --cpp_out=./../maj/
CALL protoc.exe  msg_role.proto --cpp_out=./../maj/
CALL protoc.exe  msg_room.proto --cpp_out=./../maj/
CALL protoc.exe  msg_mail.proto --cpp_out=./../maj/
CALL protoc.exe  msg_event.proto --cpp_out=./../maj/
CALL protoc.exe  msg_history.proto --cpp_out=./../maj/
CALL protoc.exe  msg_rank.proto --cpp_out=./../maj/
CALL protoc.exe  msg_gm.proto --cpp_out=./../maj/
CALL protoc.exe  server_config.proto --cpp_out=./../maj/
CALL protoc.exe  server.proto --cpp_out=./../maj/
CALL protoc.exe  server_data.proto --cpp_out=./../maj/
CALL protoc.exe  server_log.proto --cpp_out=./../maj/
CALL protoc.exe  msg_activity.proto --cpp_out=./../maj/
CALL protoc.exe  msg_ss.proto --cpp_out=./../maj/
CALL protoc.exe  msg_shop.proto --cpp_out=./../maj/

rem hmx协议文件
CALL protoc.exe  hmx_data.proto --cpp_out=./../base/
CALL protoc.exe  hmx_config.proto --cpp_out=./../base/
CALL protoc.exe  hmx_sorlists.proto --cpp_out=./../base/
CALL protoc.exe  hmx_cmd.proto --cpp_out=./../base/
CALL protoc.exe  hmx_msg_login.proto --cpp_out=./../base/

echo 生成文件完成
pause
