#ifndef APP_SETTINGS_H
#define APP_SETTINGS_H

#include <memory>
#include <Message.h>
#include <support/Archivable.h>
#include <storage/Entry.h>

class AppSettings : public BArchivable
{
	public:
		AppSettings();
		AppSettings(BMessage* message);
		virtual ~AppSettings();
		
		void SetFilePath(BEntry& entry);
		BEntry FilePath();		
		virtual status_t Archive(BMessage* archive, bool deep = true) const;
		
		static std::shared_ptr<AppSettings> Instantiate(BMessage* archive);
		static void Save(std::shared_ptr<AppSettings> settings, BEntry path);
		static std::shared_ptr<AppSettings> Load(BEntry path);
		
	private:
		BEntry _filePath;
};

#endif
