#include "ErrorMessage.h"

ErrorMessage::ErrorMessage(BString& message)
				: 	_message(message)									
{	
}

ErrorMessage::ErrorMessage(BString& message, BEntry& path)
				:	_message(message),
					_filePath(path)
{
}

ErrorMessage::~ErrorMessage()
{
}

BEntry ErrorMessage::FilePath()
{
	return _filePath;
}

uint32 ErrorMessage::LineNumber()
{
	return _lineNumber;
}

uint32 ErrorMessage::ColumnNumber()
{
	return _columnNumber;
}

BString ErrorMessage::Message()
{
	return _message;
}
