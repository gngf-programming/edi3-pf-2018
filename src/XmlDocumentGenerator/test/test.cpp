#include <string>
#include <iostream>

#include <assert.h>
#include <regex>

#include <compset/DocumentGeneratorInterface.h>
#include <compset/Component.h>

DataType GenerateTestXMLContent(void);

bool CheckXMLContent(std::string xmlContent);

bool CheckXMLHeader(std::string xmlContent);
bool CheckXMLBodyBalancedLabeling(std::string xmlContent);

void PrintXMLContent(Component<DocumentGeneratorInterface>& xmlGenerator);
void XMLGeneratorPlayground(Component<DocumentGeneratorInterface>& xmlGenerator);

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

	fieldContent["last_name"] = "Doe";

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

	if (CheckXMLBodyBalancedLabeling(xmlContent))
	{
		std::cout << "XML body is correct!" << std::endl << std::endl;
	}
	else
	{
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

	bool result = false;

	/*
	Content - type: text / xml; charset = utf - 8

	<?xml version = "1.0" encoding = "UTF-8"?>

	<data>
		<datum>
			<last_name>Doe<last_name>
		</datum>
	</data>
	*/

	try {
		// Any string that starts with </ then anything with letters, numbers or underscore, and then >
		const std::regex xmlClosingLabel("\\<(/[a-zA-Z_0-9]*)\\>");

		// Any string that starts with < then anything with letters, numbers or underscore, and then >
		const std::regex xmlOpeningLabel("\\<([a-zA-Z_0-9]*)\\>");

		std::sregex_iterator next(xmlContent.begin(), xmlContent.end(), xmlClosingLabel);
		std::sregex_iterator end;

		while (next != end)
		{
			std::smatch match = *next;

			//std::cout << match.str() << "\n";

			next++;
		}
	}
	catch (std::regex_error& e)
	{
		std::cout << "Syntax error in the regular expression" << std::endl << std::endl;
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
	// PrintXMLContent(xmlGenerator);

	// XML document generator content check
	CheckXMLContent(xmlGenerator->getDocument());
}

void PrintXMLContent(Component<DocumentGeneratorInterface>& xmlGenerator)
{
	std::cout << xmlGenerator->getDocument() << std::endl;
}