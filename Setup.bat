
set PROTOC=%~dp0\Plugins\InfraworldRuntime\GrpcPrograms\Win64\protoc.exe

%PROTOC% -I %~dp0\Proto --grpc_out=%~dp0\Plugins\InfraworldRuntime\Source\InfraworldRuntime\Layton --plugin=protoc-gen-grpc=%~dp0\Plugins\InfraworldRuntime\GrpcPrograms\Win64\grpc_cpp_plugin.exe layton.proto
%PROTOC% -I %~dp0\Proto --cpp_out=%~dp0\Plugins\InfraworldRuntime\Source\InfraworldRuntime\Layton layton.proto
java -jar %~dp0\Cornerstone\target\infraworld-cornerstone.jar
python %~dp0\disable_warnings.py