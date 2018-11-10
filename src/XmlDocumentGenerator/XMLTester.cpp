/**
* Copyright (c) 2016 Giuliano Decesares <giulianodecesares@gmail.com>. All rights reserved.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

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

#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <regex>
#include <stack>

#include <ComponentInterface.h>
#include <XMLTesterInterface.h>

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

class XMLTester : public XMLTesterInterface, public ComponentInterface
{
private:

	// ComponentInterface
	int referenceCounter;

	bool implemented;

public:

	XMLTester();

	virtual ~XMLTester();

	// ComponentInterface
	bool implements(std::string interfaceName);

	void* getInstance();

	void release();

	// XMLTesterInterface
	virtual std::vector<std::unordered_map<std::string, std::string>> GenerateTestContent(DifficultyLevel level) override;

	virtual bool CheckXMLHeader(std::string xmlContent) override;

	virtual bool CheckXMLBody(std::string xmlContent) override;

	virtual bool EquivalentLabels(std::string openingLabel, std::string closingLabes, bool silent = false) override;

	// Concrete behavior
	std::vector<std::string> SplitXMLContent(std::string xmlContent);

	void CheckAndPush(std::string content, const std::regex regex, std::vector<std::string>& container);
};

XMLTester::XMLTester() : referenceCounter(0)
{
	//std::cout << "XML Tester constructor has been called" << std::endl << std::endl;
}

XMLTester::~XMLTester()
{
	//std::cout << "XML Tester destructor has been called" << std::endl << std::endl;
}

std::vector<std::unordered_map<std::string, std::string>> XMLTester::GenerateTestContent(DifficultyLevel level)
{
	std::vector<std::unordered_map<std::string, std::string>> returnContent;
	std::unordered_map<std::string, std::string> fieldContent;

	switch (level)
	{
	case BABY_STEPS:
		fieldContent["last_name"] = "Doe and Joe";
		returnContent.push_back(fieldContent);
		break;

	case NORMAL:
		break;
	case TAKE_IT_EASY_BRO:
		break;
	case NIGHTMARE:
		break;
	default:
		break;
	}


	return returnContent;
}

bool XMLTester::CheckXMLHeader(std::string xmlContent)
{
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

bool XMLTester::CheckXMLBody(std::string xmlContent)
{
	bool result = true;

	// All xml regular expressions encapsulation to better handling
	XmlRegex xmlRegex;

	// Split the xml content into elements to better handling
	std::vector<std::string> xmlExpressions = this->SplitXMLContent(xmlContent);

	// Check the resultant container

	// Check second invariant: it should be the exact number of opening and closing tags
	std::vector<std::string> closingTags;
	std::vector<std::string> openingTags;

	for (int index = 0; index < xmlExpressions.size(); index++)
	{
		if (std::regex_match(xmlExpressions[index], *xmlRegex.openingLabel))
			openingTags.push_back(xmlExpressions[index]);
		else if (std::regex_match(xmlExpressions[index], *xmlRegex.closingLabel))
			closingTags.push_back(xmlExpressions[index]);
	}

	std::reverse(std::begin(closingTags), std::end(closingTags));

	if (openingTags.size() > closingTags.size())
	{
		std::cout << "Syntax error. More closing tags needed" << std::endl << std::endl;

		for (int index = 0; index < closingTags.size(); index++)
		{
			if (EquivalentLabels(openingTags[index], closingTags[index], true))
			{
				openingTags[index] = "";
			}
		}

		for (int index = 0; index < openingTags.size(); index++)
		{
			if (openingTags[index] != "")
			{
				std::cout << "Missing closing tag for " << openingTags[index] << std::endl << std::endl;
			}
		}

		result = false;
	}
	else if (closingTags.size() > openingTags.size())
	{
		std::cout << "Syntax error. More opening tags needed" << std::endl << std::endl;

		for (int index = 0; index < openingTags.size(); index++)
		{
			if (EquivalentLabels(openingTags[index], closingTags[index], true))
			{
				closingTags[index] = "";
			}
		}

		for (int index = 0; index < closingTags.size(); index++)
		{
			if (closingTags[index] != "")
			{
				std::cout << "Missing opening tag for " << closingTags[index] << std::endl << std::endl;
			}
		}

		result = false;
	}

	// Check both first and third invariant

	std::stack<std::string> stack;

	if (result == true)
	{
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
	}

	return result;
}

bool XMLTester::EquivalentLabels(std::string openingLabel, std::string closingLabel, bool silent)
{
	bool result = true;

	std::string newClosingLabel = closingLabel;

	// Remove closingLabel[1] char "/" to generate an equivalent opening label 
	// i. e. <data></data> ---> <data><data>
	newClosingLabel.erase(1, 1);

	// Then compare both labels
	result = openingLabel == newClosingLabel;

	if (silent == false)
	{
		if (result == false)
		{
			std::cout << "Bad syntax with labels " << openingLabel.c_str() << " and " << closingLabel.c_str() << std::endl;
		}
		else
		{
			std::cout << "Equivalent labels " << openingLabel.c_str() << " and " << closingLabel.c_str() << std::endl;
		}
	}

	return result;
}

std::vector<std::string> XMLTester::SplitXMLContent(std::string xmlContent)
{
	// All xml regular expressions encapsulation to better handling
	XmlRegex xmlRegex;

	// All content regex to loop over every row in the file
	const std::regex allContent("(.*)");

	// Get an ordered list with all XML body's data structure
	std::vector<std::string> returnVector;

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
		this->CheckAndPush(currentContent, *xmlRegex.openingLabel, returnVector);

		// Second: check for ONLY xml data
		this->CheckAndPush(currentContent, *xmlRegex.data, returnVector);

		// Third: check for closing label
		this->CheckAndPush(currentContent, *xmlRegex.closingLabel, returnVector);

		next++;
	}

	return returnVector;
}

void XMLTester::CheckAndPush(std::string content, const std::regex regex, std::vector<std::string>& container)
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

// Component interface implementation

bool XMLTester::implements(std::string interfaceName)
{
	return (interfaceName == "ComponentInterface" || interfaceName == "XMLTesterInterface") ?
		this->implemented = true : this->implemented = false;
}

void* XMLTester::getInstance()
{
	if (implemented) { referenceCounter++;  return this; }
	return NULL;
}

void XMLTester::release()
{
	referenceCounter--;
	if (referenceCounter <= 0) delete this;
}

extern "C" ComponentInterface* create();

ComponentInterface* create()
{
	return (ComponentInterface*) new XMLTester;
}
