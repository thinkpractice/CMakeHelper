#ifndef ERROR_MESSAGE_H
#define ERROR_MESSAGE_H

#include <support/String.h>

class ErrorMessage
{
	public:
		ErrorMessage(BString& message);
		virtual ~ErrorMessage();
		
		BString Message();
	
	private:
		BString _message;
};

#endif
