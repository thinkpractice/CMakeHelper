#include "ErrorMessage.h"

ErrorMessage::ErrorMessage(BString& message)
				: _message(message)
{	
}

ErrorMessage::~ErrorMessage()
{
}

BString ErrorMessage::Message()
{
	return _message;
}
