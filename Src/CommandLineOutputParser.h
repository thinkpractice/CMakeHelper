#ifndef COMMAND_LINE_OUTPUT_PARSER_H
#define COMMAND_LINE_OUTPUT_PARSER_H

#include <vector>
#include <support/String.h>
#include "ErrorMessage.h"

class CommandLineOutputParser
{
	public:
		CommandLineOutputParser() {}
		virtual std::vector<ErrorMessage> ParseOutput(BString& commandLineOutput) = 0;
	
};

#endif
