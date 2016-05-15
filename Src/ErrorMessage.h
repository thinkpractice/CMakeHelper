#ifndef ERROR_MESSAGE_H
#define ERROR_MESSAGE_H

#include <support/String.h>
#include <storage/Entry.h>

class ErrorMessage
{
	public:
		ErrorMessage(BString& message);
		ErrorMessage(BString& message, BEntry& path);
		virtual ~ErrorMessage();
		
		BEntry FilePath();
		uint32 LineNumber();
		uint32 ColumnNumber();
		BString Message();
	
	private:		
		BEntry _filePath;
		uint32 _lineNumber;
		uint32 _columnNumber;
		BString _message;
};

#endif
