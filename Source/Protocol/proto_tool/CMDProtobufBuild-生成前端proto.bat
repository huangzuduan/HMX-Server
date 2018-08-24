
del cmd.proto

del cmdmanager\*.proto

copy ..\protobuf\comdef.proto cmdmanager
copy ..\protobuf\msg_*.proto cmdmanager

python removepack.py ../protobuf cmdmanager

type cmdmanager\*.proto >> cmd.proto

findstr /iv "import" cmd.proto>cmd1.proto&move cmd1.proto cmd.proto

findstr /iv "package" cmd.proto>cmd1.proto&move cmd1.proto cmd.proto

findstr /iv "syntax" cmd.proto>cmd1.proto&move cmd1.proto cmd.proto


pause