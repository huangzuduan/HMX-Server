del Cmd.cs

del Cmd.dll

del CmdSerializer.dll

del Cmd.bin

del Cmd.proto
copy ..\protobuf\*.proto cmdmanager

python removepack.py ../protobuf cmdmanager

type cmdmanager\*.proto >> Cmd.proto

findstr /iv "import" Cmd.proto>Cmd1.proto&move Cmd1.proto Cmd.proto

findstr /iv "package" Cmd.proto>Cmd1.proto&move Cmd1.proto Cmd.proto

copy /y Cmd.proto protobuf-net\ProtoGen

protobuf-net\ProtoGen\protoc -I. Cmd.proto -o Cmd.bin

protobuf-net\ProtoGen\protogen -i:Cmd.bin -o:Cmd.cs

copy /y Cmd.cs Cmd\Cmd\

pause