#include "MainWindow.h"
#include <app/Application.h>
#include <app/Message.h>
#include <app/Messenger.h>
#include <interface/Button.h>
#include <interface/Box.h>
#include <interface/ListView.h>
#include <interface/LayoutBuilder.h>
#include <storage/Entry.h>
#include "Constants.h"

MainWindow::MainWindow(BRect frame)
				: BWindow(frame, "CMakeHelper", B_TITLED_WINDOW, 0)
{
	BMessenger windowMessenger(this);
	_windowController = new MainWindowController(windowMessenger);

	_filePathControl = new BTextControl("Makefile Path:", "", new BMessage());
	
	BButton* browseButton = new BButton("Browse..", new BMessage(kBrowseFileMessage));
	BButton* runButton = new BButton("Run", new BMessage(kRunMessage));
	BButton* cleanButton = new BButton("Clean", new BMessage(kCleanMessage));
	
	BBox* errorsBox = new BBox("Errors & Warnings");
	BListView* errorsListView = new BListView();
	errorsBox->AddChild(errorsListView);	
	
	BLayoutBuilder::Group<>(this, B_VERTICAL, 0)
		.SetInsets(0)
		.AddGroup(B_HORIZONTAL,1)
			.Add(_filePathControl)
			.Add(browseButton)
		.End()
		.AddGroup(B_HORIZONTAL,2)
			.Add(errorsBox)
		.End()
		.AddGroup(B_HORIZONTAL,1)
			.Add(runButton)
			.Add(cleanButton)	
		.End();
}

MainWindow::~MainWindow()
{
	delete _windowController;
}

void MainWindow::MessageReceived(BMessage *message)
{
	switch(message->what)
	{
		case B_REFS_RECEIVED:
		{
			entry_ref directoryRef;
			message->FindRef("refs", &directoryRef);
			BPath path(&directoryRef); 
			_windowController->SetMakeFileLocation(path);
		}
		break;		
		case kBrowseFileMessage:
		{
			_windowController->ShowOpenFileDialog();
		}
		break;
		case kRunMessage:
		{
			_windowController->RunMake();
		}
		break;
		case kCleanMessage:
		{
			_windowController->CleanMake();
		}
		break;
		case kPropertyChanged:
		{			
			BPath path = _windowController->GetMakeFileLocation();
			_filePathControl->SetText(path.Path());
		}
		break;
		default:
			BWindow::MessageReceived(message);
		break;
	}
}

bool MainWindow::QuitRequested()
{
	be_app->PostMessage(B_QUIT_REQUESTED);
	return BWindow::QuitRequested();	
}
