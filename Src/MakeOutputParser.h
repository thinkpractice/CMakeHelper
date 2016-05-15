#ifndef MAKE_OUTPUT_PARSER_H
#define MAKE_OUTPUT_PARSER_H

#include "CommandLineOutputParser.h" 

class MakeOutputParser : public CommandLineOutputParser
{
	public:
		MakeOutputParser();
		virtual ~MakeOutputParser();
		
		virtual std::vector<ErrorMessage> ParseOutput(BString& commandLineOutput);
};

#endif 
