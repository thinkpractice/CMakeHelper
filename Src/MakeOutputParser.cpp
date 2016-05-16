#include "MakeOutputParser.h"
#include <support/StringList.h>
#include <iostream>
#include <regex>

MakeOutputParser::MakeOutputParser()
					: CommandLineOutputParser()
{
}

MakeOutputParser::~MakeOutputParser()
{
}
		
std::vector<ErrorMessage> MakeOutputParser::ParseOutput(BString& commandLineOutput)
{
	std::vector<ErrorMessage> errorMessages;
	
	BStringList errorList;
	commandLineOutput.Split("\n", false, errorList);
	
	std::smatch matches;
	std::regex pathMatcher("(\\/[\\w|\\W]+.cpp):"); 
	
	bool isMatchingError = false;
	BString errorMessageString = "";
	for (int i = 0; i < errorList.CountStrings(); i++)
	{
		BString error = errorList.StringAt(i);
		std::string errorString(error.String());
		if (error.FindFirst("[100%]") != B_ERROR)
		{
			ErrorMessage errorMessage(error);
			errorMessages.push_back(errorMessage);
		}
		else if (std::regex_search(errorString, matches, pathMatcher))
		{
			errorMessageString += error;
			if (!isMatchingError)		
			{	
				isMatchingError	= true;
				continue;
			}
			isMatchingError	= false;
			
			BEntry filePath(matches[1].str().c_str());					
			ErrorMessage errorMessage(errorMessageString, filePath);
			errorMessages.push_back(errorMessage);
		}
	}
	return errorMessages;
}
