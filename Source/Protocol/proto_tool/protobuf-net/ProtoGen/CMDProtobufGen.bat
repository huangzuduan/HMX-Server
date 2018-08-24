protoc -I. Cmd.proto -o Cmd.bin

protogen -i:Cmd.bin -o:Cmd.cs

pause