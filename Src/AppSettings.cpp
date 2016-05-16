#include "AppSettings.h"

#define CHECK_STATUS(status) if (status != B_OK) return status


AppSettings::AppSettings()
				: BArchivable()
{
}

AppSettings::AppSettings(BMessage* archive)
				: BArchivable(archive)
{
	entry_ref fileRef;
	archive->FindRef("fileRef", &fileRef);
	_filePath = BEntry(&fileRef);
}

AppSettings::~AppSettings()
{
}
		
void AppSettings::SetFilePath(BEntry& entry)
{
	_filePath = entry;
}

BEntry AppSettings::FilePath()
{
	return _filePath;
}		

status_t AppSettings::Archive(BMessage* archive, bool deep) const
{
	CHECK_STATUS(archive->AddString("class", "AppSettings"));
	
	entry_ref fileRef;
	CHECK_STATUS(_filePath.GetRef(&fileRef));
	CHECK_STATUS(archive->AddRef("fileRef", &fileRef));
	return B_OK;
}

BArchivable* AppSettings::Instantiate(BMessage* archive)
{
   if ( !validate_instantiation(archive, "AppSettings") )
      return NULL;
   return new AppSettings(archive);
}
   
