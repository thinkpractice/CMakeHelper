#ifndef ERROR_MESSAGE_H
#define ERROR_MESSAGE_H

#include <support/String.h>
#include <storage/Path.h>

class ErrorMessage
{
	public:
		ErrorMessage(BString& message);
		virtual ~ErrorMessage();
		
		BPath FilePath();
		uint32 LineNumber();
		uint32 ColumnNumber();
		BString Message();
	
	private:		
		BPath _filePath;
		uint32 _lineNumber;
		uint32 _columnNumber;
		BString _message;
};

#endif
