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
bool EquivalentLabels(std::string openingLabel, std::string closingLabel);

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

	bool result = true;

	std::cout << xmlContent.c_str() << std::endl << std::endl;

	try {
		// Any string that starts with </ then anything with letters, numbers or underscore, and then >
		const std::regex xmlClosingLabel("\\<(/[a-zA-Z_0-9]*)\\>");

		// Any string that starts with < then anything with letters, numbers or underscore, and then >
		const std::regex xmlOpeningLabel("\\<([a-zA-Z_0-9]*)\\>");

		// Combination of both opening and closing label's regular expressions
		const std::regex xmlOpeningAndClosingLabels("\\<(/[a-zA-Z_0-9]*)\\>|\\<([a-zA-Z_0-9]*)\\>");

		// Filter entire content to obtain only xml labels
		std::sregex_iterator next(xmlContent.begin(), xmlContent.end(), xmlOpeningAndClosingLabels);
		std::sregex_iterator end;

		std::vector<std::string> openingLabels;
		std::vector<std::string> closingLabels;

		// While content is available
		while (next != end)
		{
			std::smatch match = *next;

			//std::cout << match.str() << std::endl << std::endl;

			// Filter only closing labels
			if (std::regex_match(match.str(), xmlOpeningLabel))
			{
				openingLabels.push_back(match.str());
			
			} // Else filter only opening labels
			else if (std::regex_match(match.str(), xmlClosingLabel))
			{
				closingLabels.push_back(match.str());
			}

			next++;
		}

		// Revert one vector, 'cause labels are stored in an inverted order due the nature of xml files
		std::reverse(closingLabels.begin(), closingLabels.end());

		// Compare the size of the vectors first. There must be the same number of opening and closing labels.
		if (openingLabels.size() == closingLabels.size())
		{
			// After that, compare label by label as long as result equals true
			for (int index = 0; index < openingLabels.size(); index++)
			{
				if (EquivalentLabels(openingLabels[index], closingLabels[index]) == false)
				{
					result = false;
					break; // !!
				}
			}
		}
		else
		{
			std::cout << "The opening-labels amount differs from the closing-labels amount" << std::endl << std::endl;
			result = false;
		}

	}
	catch (std::regex_error& e)
	{
		std::cout << "Syntax error in the regular expression" << std::endl << std::endl;
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
		std::cout << "Bad syntax with labels " << openingLabel.c_str() << " and " << closingLabel.c_str() << std::endl << std::endl;
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