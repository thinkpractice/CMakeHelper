#include "MakeOutputParser.h"
#include <support/StringList.h>

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
	
	for (int i = 0; i < errorList.CountStrings(); i++)
	{
		BString error = errorList.StringAt(i);
		ErrorMessage errorMessage(error);
		errorMessages.push_back(errorMessage);
	}
	return errorMessages;
}
