/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of COMPSET.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/
#ifndef INIREADER_H
#define INIREADER_H

#include <string>
#include <fstream>
#include <sstream>

using namespace std;


class IniReader
{
    public:
        IniReader();
        virtual ~IniReader();
        bool open( std::string fileName);
        IniReader* selectSection( std::string section );
        std::string getValue( std::string key );
        void close();


    private:
        ifstream _fileInput;
        std::string  _dataSection ;
        std::string _BufferData ;

        void ReadFile();
};

IniReader::IniReader()
{
    //ctor
}

bool IniReader::open( std::string fileName )
{
   _fileInput.open(fileName.c_str());
    return  !_fileInput ? false : true;
}

IniReader* IniReader::selectSection( std::string section )
{

    ReadFile();
    std::string _buffer;
    size_t posInitialBuffer = _BufferData.find("["+section+"]");

    if (_BufferData.find("["+section+"]") == (std::string::npos))
    {
        return this;
    }
    else
    {
        _buffer = _BufferData.substr(posInitialBuffer);
        size_t posInitial = _buffer.find("["+section+"]");
        size_t posEnd = _buffer.find_first_of("[",posInitial+1);

        size_t sizeOfString = posEnd-posInitial;
        _dataSection = _buffer.substr(posInitial,sizeOfString );

        return this;
    }
}

std::string IniReader::getValue(std::string key)
{
    unsigned int pos ;
    pos  = _dataSection.find(key);

    if ((pos==std::string::npos) || (_dataSection == ""))
    {
        return "";
    }
    else
    {
        int posValue = (_dataSection.find_first_of("=",pos) + 2);
        int posEndValue = _dataSection.find_first_of(" ",posValue);
        size_t sizeOfString = posEndValue-posValue;

        std::string value = _dataSection.substr(posValue,sizeOfString);

        return value ;
    }
}


void IniReader::close()
{
    _fileInput.close();
}


void IniReader::ReadFile()
{
    while( !_fileInput.eof())
    {
        std::string _buffer;

       _fileInput >> _buffer;
       _BufferData += " " + std::string(_buffer);
    }
}

IniReader::~IniReader()
{
    //dtor
}

#endif // INIREADER_H
