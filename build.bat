:: Borro el directorio si ya existiera
::del /f /q bin;

:: Creo los directorios para el binario y las bibliotecas
MD .\web\backend\
MD .\web\backend\lib\
MD .\web\backend\lib\actions\

:: compilo el binario
g++ -Wall -std=c++11 -I./include/ main.cpp -o ./web/backend/main.exe

:: compilo las bibliotecas
g++ -shared -Wall -std=c++11 -I./include/ ./src/Application/Application.cpp -o ./web/backend/lib/Application.dll

g++ -shared -Wall -std=c++11 -I./include/ ./src/RequestHandler/RequestHandler.cpp -o ./web/backend/lib/RequestHandler.dll

g++ -shared -Wall -std=c++11 -I./include/ ./src/ResponseHandler/ResponseHandler.cpp -o ./web/backend/lib/ResponseHandler.dll

g++ -shared -Wall -std=c++11 -I./include/ ./src/JsonDocumentGenerator/JsonDocumentGenerator.cpp -o ./web/backend/lib/JsonDocumentGenerator.dll

gcc --shared -Wall ./src/PortableEnviromentVariable/PortableEnviromentVariable.c -o ./web/backend/lib/PortableEnviromentVariable.dll

g++ -shared -Wall -std=c++11 -I./include/ ./src/Actions/TestRequestResponse/TestRequestResponse.cpp -o ./web/backend/lib/Actions/TestRequestResponse.dll

:: copio
copy .\LICENSE .\web\backend\

:: creo un readme para entender como probar la aplicación
echo COMPSET TEST: > ./web/backend/Readme.txt
echo 	-exec params: "action=TestRequestResponse&greeting=Hello" >> ./web/backend/Readme.txt
