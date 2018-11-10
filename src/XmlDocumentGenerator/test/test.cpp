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
#include "Component.h"

DataType GenerateTestXMLContent(void);

bool CheckXMLContent(std::string xmlContent);

bool CheckXMLHeader(std::string xmlContent);
bool CheckXMLBodyBalancedLabeling(std::string xmlContent);
bool EquivalentLabels(std::string openingLabel, std::string closingLabel);

void PrintXMLContent(Component<DocumentGeneratorInterface>& xmlGenerator);
void XMLGeneratorPlayground(Component<DocumentGeneratorInterface>& xmlGenerator);

void CheckAndPush(std::string content, const std::regex regex, std::vector<std::string>& container);

// "Encapsulation" for the regex ugly complexity (The terrifying part is all here)
struct XmlRegex
{
	const std::regex* openingLabel;
	const std::regex* closingLabel;
	const std::regex* openingAndClosingLabels;
	const std::regex* dataRow;
	const std::regex* data;

	XmlRegex()
	{
		// Any string that starts with < then anything with letters, numbers or underscore, and then >
		this->openingLabel = new std::regex("<([\\w:]*)( [^<>]*)?>");

		// Any string that starts with </ then anything with letters, numbers or underscore, and then >
		this->closingLabel = new std::regex("\\<(/[a-zA-Z_0-9]*)\\>");

		// Combination of both opening and closing label's regular expressions
		this->openingAndClosingLabels = new std::regex("\\<(/[a-zA-Z_0-9]*)\\>|\\<([a-zA-Z_0-9]*)\\>");

		// A complete xml data row. 1 -> tag, 2 -> parameters, 3 -> value
		this->dataRow = new std::regex("<([\\w:]*)( [^<>]*)?>([^<>]*)</\\1>");
		
		// Data between > and <
		this->data = new std::regex(">([^<>]*)<");
	}
};

int main()
{
	// 1 - Component creation (RAII approves)
	Component<DocumentGeneratorInterface> xmlGenerator("DocumentGeneratorInterface", "./XmlDocumentGenerator");

	// 2 - XML generator test method
	XMLGeneratorPlayground(xmlGenerator);

	return 0;
}

DataType GenerateTestXMLContent(void)
{
	DataType returnContent;
	DatumType fieldContent;

	fieldContent["last_name"] = "Doe and Joe";

	returnContent.push_back(fieldContent);

	return returnContent;
}

bool CheckXMLContent(std::string xmlContent)
{
	bool result = true;

	if (CheckXMLHeader(xmlContent))
	{
		std::cout << "XML header is correct!" << std::endl << std::endl;
	}
	else
	{
		std::cout << "XML header bad syntax" << std::endl << std::endl;
		result = false;
	}

	std::cout << "<-------------------------------------------->" << std::endl << std::endl;

	if (CheckXMLBodyBalancedLabeling(xmlContent))
	{
		std::cout << std::endl;
		std::cout << "XML body is correct!" << std::endl << std::endl;
	}
	else
	{
		std::cout << std::endl;
		std::cout << "XML body bad syntax" << std::endl << std::endl;
		result = false;
	}

	return result;
}

bool CheckXMLHeader(std::string xmlContent)
{
	std::cout << "Checking XML file header" << std::endl << std::endl;

	bool result = false;

	// Any string that starts with <? then anything less than ?> and then ?>
	const std::regex xmlHeaderLabel("\\<\\?([^\\?|^\\>]*)\\?\\>");

	// Get first line of xml document (until first "\n")
	std::size_t position = xmlContent.find("\n");
	std::string firstLine = xmlContent.substr(0, position);

	std::cout << "Current header is: \"" << firstLine << "\"" << std::endl << std::endl;

	if (std::regex_match(firstLine, xmlHeaderLabel))
	{
		result = true;
	}

	return result;
}

bool CheckXMLBodyBalancedLabeling(std::string xmlContent)
{
	std::cout << "Checking XML file body" << std::endl << std::endl;

	bool result = true;

	// All xml regular expressions encapsulation to better handling
	XmlRegex xmlRegex;

	// All content regex to loop over every row in the file
	const std::regex allContent("(.*)");

	// Get an ordered list with all XML body's data structure
	std::vector<std::string> xmlExpressions;

	// Go over all file content to obtain only file rows
	std::sregex_iterator next(xmlContent.begin(), xmlContent.end(), allContent);
	std::sregex_iterator end;

	// While content is available
	while (next != end)
	{
		std::smatch match = *next;
		std::string currentContent = match.str();

		//std::cout << "Current content " << currentContent.c_str() << std::endl;

		// First: check for ONLY opening label ('cause xml structure could be nested)
		CheckAndPush(currentContent, *xmlRegex.openingLabel, xmlExpressions);

		// Second: check for ONLY xml data
		CheckAndPush(currentContent, *xmlRegex.data, xmlExpressions);

		// Third: check for closing label
		CheckAndPush(currentContent, *xmlRegex.closingLabel, xmlExpressions);

		next++;
	}

	// Once that is done, check the resultant container

	/*

	The syntax-check algorithm is quite simple.
	Every element could be: tag, closing tag or data (the thing between tags).
	The container is ordered.

	Then... something like this:

	<note>
		<to>Tove</to>
		<from>Jani</from>
		<heading>Reminder</heading>
		<body>Don't forget me this weekend!</body>
	</note>

	'll result in something like this:

	<note>
	<to>
	Tove
	</to>
	<from>
	Jani
	</from>
	<heading>
	Reminder
	</heading>
	<body>
	Don't forget me this weekend!
	</body>
	</note>

	Something like a stack of elements.
	The first invariant is that before a value there must be an opening tag, and then a closing tag.

	Then...

	from container
		if currentElement is data:
			if container[index(currentElement) - 1] is openingTag:
				if container[index(currentElement) + 1] is closingTag:
					Syntax so far so good
				else:
					"Closing tag expected" error
			else:
				"Opening tag espected" error

	The second invariant is it should be the exact number of opening and closing tags
	The third invariant, very close to the second one, is tags should be in mirrored order (1 2 3 data 3 2 1)
	i.e. -> <note> <to> Bla bla bla </to> </note>
	*/

	std::stack<std::string> stack;

	//for (int index = 0; index < xmlExpressions.size(); index++)
	//{
	//	std::cout << "Stack value is: " << xmlExpressions[index] << std::endl << std::endl;
	//}

	std::cout << std::endl;

	for (int index = 0; index < xmlExpressions.size(); index++)
	{
		if (std::regex_match(xmlExpressions[index], *xmlRegex.openingLabel))
		{
			// Is opening label case
			stack.push(xmlExpressions[index]);
			std::cout << "Opening label found: " << xmlExpressions[index] << std::endl;
		}
		else if (std::regex_match(xmlExpressions[index], *xmlRegex.data))
		{
			// Is value case
			std::cout << "XML value found: " << xmlExpressions[index] << std::endl;

			// Search for closing label
			if (std::regex_match(xmlExpressions[index + 1], *xmlRegex.closingLabel))
			{
				std::cout << "Closing label found: " << xmlExpressions[index + 1] << std::endl;

				// Check for label equivalency in labels of value
				if (EquivalentLabels(stack.top(), xmlExpressions[index + 1]))
				{
					// Equivalent case
					stack.pop();
					index++;
				}
				else
				{
					// Unequivalent case
					result = false;
					std::cout << "Unequivalent labels error for: " << stack.top() << " and " << xmlExpressions[index + 1] << std::endl;
					stack.pop();
				}

			}
			else
			{
				result = false;
				std::cout << "Closing label error for: " << xmlExpressions[index] << std::endl;
			}
		}
		else if (std::regex_match(xmlExpressions[index], *xmlRegex.closingLabel))
		{
			// Is closing label case. Verify label equivalency with previous label

			if (EquivalentLabels(stack.top(), xmlExpressions[index]))
			{
				stack.pop();
			}
			else
			{
				result = false;
				std::cout << "Unequivalent labels error for: " << stack.top() << " and " << xmlExpressions[index + 1] << std::endl;
				stack.pop();
			}
		}
	}

	return result;
}

bool EquivalentLabels(std::string openingLabel, std::string closingLabel)
{
	bool result = true;

	std::string newClosingLabel = closingLabel;

	// Remove closingLabel[1] char "/" to generate an equivalent opening label 
	// i. e. <data></data> ---> <data><data>
	newClosingLabel.erase(1, 1);

	// Then compare both labels
	result = openingLabel == newClosingLabel;

	if (result == false)
	{
		std::cout << "Bad syntax with labels " << openingLabel.c_str() << " and " << closingLabel.c_str() << std::endl;
	}
	else
	{
		std::cout << "Equivalent labels " << openingLabel.c_str() << " and " << closingLabel.c_str() << std::endl;
	}

	return result;
}

void XMLGeneratorPlayground(Component<DocumentGeneratorInterface>& xmlGenerator)
{
	// XML data creation for testing proposes
	DataType data = GenerateTestXMLContent();

	// XML document generator content set
	xmlGenerator->setContent(data);

	// XML document generator content print
	PrintXMLContent(xmlGenerator);

	// XML document generator content check
	CheckXMLContent(xmlGenerator->getDocument());
}

void PrintXMLContent(Component<DocumentGeneratorInterface>& xmlGenerator)
{
	std::cout << "<----------> Printing xml content <---------->" << std::endl << std::endl;
	std::cout << xmlGenerator->getDocument() << std::endl << std::endl;
	std::cout << "<-------------> End of content <------------->" << std::endl << std::endl << std::endl;
}

void CheckAndPush(std::string content, const std::regex regex, std::vector<std::string>& container)
{
	try
	{
		std::sregex_iterator subNext(content.begin(), content.end(), regex);
		std::sregex_iterator subEnd;

		while (subNext != subEnd)
		{
			std::smatch subMatch = *subNext;

			if (!subMatch.empty())
			{
				container.push_back(subMatch.str());
			}

			subNext++;
		}
	}
	catch (const std::regex_error& error)
	{
		std::cout << "Syntax error in the regular expression" << std::endl << std::endl;
	}
}