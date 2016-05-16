#include "AppSettings.h"
#include <storage/File.h>

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
   
void AppSettings::Save(AppSettings& settings, BEntry path)
{
	BFile settingsFile(&path, B_WRITE_ONLY);
	
	BMessage message;
	settings.Archive(&message);
	
	message.Flatten(&settingsFile);
}

std::shared_ptr<AppSettings> AppSettings::Load(BEntry path)
{
	BFile settingsFile(&path, B_READ_ONLY);
	
	BMessage message;
	message.Unflatten(&settingsFile);
	
	return AppSettings::Instantiate(&message);
}		
