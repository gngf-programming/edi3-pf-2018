#!/bin/bash

##Borro el directorio si ya existiera
if [ -d "./web/backend" ];
	then rm -r ./web/backend;
fi
##Creo los directorios para el Binario y las bibliotecas
mkdir ./web/backend/
mkdir ./web/backend/lib/
mkdir ./web/backend/lib/Actions/

##compilo el Binario
g++ -Wall -std=c++11 -ldl -I./include/ main.cpp -o ./web/backend/main.exe

##compilo las bibliotecas
g++ -shared -Wall -std=c++11 -fPIC -I./include/ \
./src/Application/Application.cpp -o ./web/backend/lib/Application.so

g++ -shared -Wall -std=c++11 -fPIC -I./include/ \
./src/RequestHandler/RequestHandler.cpp -o ./web/backend/lib/RequestHandler.so

g++ -shared -Wall -std=c++11 -fPIC -I./include/ \
./src/ResponseHandler/ResponseHandler.cpp -o ./web/backend/lib/ResponseHandler.so

g++ -shared -Wall -std=c++11 -fPIC -I./include/ \
./src/JsonDocumentGenerator/JsonDocumentGenerator.cpp -o ./web/backend/lib/JsonDocumentGenerator.so

gcc --shared -Wall -fPIC ./src/PortableEnviromentVariable/PortableEnviromentVariable.c \
-o ./web/backend/lib/PortableEnviromentVariable.so

g++ -shared -Wall -std=c++11 -fPIC -I./include/ \
./src/Actions/TestRequestResponse/TestRequestResponse.cpp -o ./web/backend/lib/Actions/TestRequestResponse.so

##copio la licencia
cp ./LICENSE ./web/backend/

##otorgo permisos de escritura a los ejecutables
chmod +x ./web/backend/main.exe

##creo un Readme para entender como probar la aplicación
echo -e "COMPSET TEST:" > ./web/backend/Readme.txt
echo -e "\t -exec params: \"action=TestRequestResponse&greeting=Hello\"" >> ./web/backend/Readme.txt
