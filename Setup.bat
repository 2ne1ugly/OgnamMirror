
protoc -I Proto --grpc_out=.\Source\Ognam\Layton\layton --plugin=protoc-gen-grpc=%~dp0\Proto\grpc_cpp_plugin.exe layton.proto
protoc -I Proto --cpp_out=.\Source\Ognam\Layton\layton layton.proto
java -jar %~dp0\cornerstone\target\infraworld-cornerstone.jar
