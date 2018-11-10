/**
* Copyright (c) 2016 Giuliano Decesares <giulianodecesares@gmail.com>. All rights reserved.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

#ifndef XML_TESTER_INTERFACE_H
#define XML_TESTER_INTERFACE_H

#include <iostream>
#include <vector>
#include <unordered_map>

enum DifficultyLevel { BABY_STEPS, NORMAL, TAKE_IT_EASY_BRO, NIGHTMARE };

class XMLTesterInterface
{
public:
	virtual ~XMLTesterInterface() { }

	virtual std::vector<std::unordered_map<std::string, std::string>> GenerateTestContent(DifficultyLevel level) = 0;

	virtual bool CheckXMLHeader(std::string xmlContent) = 0;
	virtual bool CheckXMLBody(std::string xmlContent) = 0;

	virtual bool EquivalentLabels(std::string openingLabel, std::string closingLabel, bool silent = false) = 0;
};

#endif // XML_TESTER_INTERFACE_H
