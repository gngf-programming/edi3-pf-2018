/**
* Copyright (c) 2016 Giuliano Decesares <giulianodecesares@gmail.com>. All rights reserved.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

#include <string>
#include <iostream>

#include <assert.h>
#include <regex>
#include <stack>

#include "DocumentGeneratorInterface.h"
#include "XMLTesterInterface.h"

#include "Component.h"

void RunCompleteTest(Component<DocumentGeneratorInterface>& xmlGenerator, DifficultyLevel level);

int main()
{
	// 1 - Components creation (RAII approves)
	Component<DocumentGeneratorInterface> xmlGenerator("DocumentGeneratorInterface", "./XmlDocumentGenerator");

	// 2 - Run comlete test of XML generator
	RunCompleteTest(xmlGenerator, BABY_STEPS);

	return 0;
}

void RunCompleteTest(Component<DocumentGeneratorInterface>& xmlGenerator, DifficultyLevel level)
{
	Component<XMLTesterInterface> xmlTester("XMLTesterInterface", "./XMLTester");

	xmlGenerator->setContent(xmlTester->GenerateTestContent(level));

	std::cout << "Checking XML file header" << std::endl << std::endl;

	if (xmlTester->CheckXMLHeader(xmlGenerator->getDocument()) == true)
	{
		std::cout << "Header syntax is correct" << std::endl << std::endl;
	}
	else
	{
		std::cout << "Header bad syntax" << std::endl << std::endl;
	}

	std::cout << "Checking XML file body" << std::endl << std::endl;

	std::cout << "Printing document ... " << std::endl << std::endl;

	std::cout << xmlGenerator->getDocument() << std::endl << std::endl;

	if (xmlTester->CheckXMLBody(xmlGenerator->getDocument()) == true)
	{
		std::cout << "Body syntax is correct" << std::endl << std::endl;
	}
	else
	{
		std::cout << "Body bad syntax" << std::endl << std::endl;
	}
}