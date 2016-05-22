#include "AppSettings.h"
#include <storage/File.h>
#include <iostream>

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

std::shared_ptr<AppSettings> AppSettings::Instantiate(BMessage* archive)
{
   if ( !validate_instantiation(archive, "AppSettings") )
      return NULL;
   return std::shared_ptr<AppSettings>(new AppSettings(archive));
}
   
void AppSettings::Save(std::shared_ptr<AppSettings> settings, BEntry path)
{
	BFile settingsFile(&path, B_READ_WRITE | B_ERASE_FILE | B_CREATE_FILE);
	if (settingsFile.InitCheck() != B_OK)
		return;
	
	BMessage message;
	settings->Archive(&message);
	
	status_t status = message.Flatten(&settingsFile);
	if (status != B_OK)
		std::cout << "Settings file not written" << std::endl;
}

std::shared_ptr<AppSettings> AppSettings::Load(BEntry path)
{
	BFile settingsFile(&path, B_READ_ONLY);
	
	BMessage message;
	status_t status = message.Unflatten(&settingsFile);
	
	if (status != B_OK)
		std::cout << "Settings file not read" << std::endl;
	
	return AppSettings::Instantiate(&message);
}		
