#include "MainWindow.h"
#include <app/Application.h>
#include <app/Message.h>
#include <app/Messenger.h>
#include <interface/Button.h>
#include <interface/Box.h>
#include <interface/ListView.h>
#include <storage/Entry.h>
#include "Constants.h"

MainWindow::MainWindow(BRect frame)
				: BWindow(frame, "CMakeHelper", B_TITLED_WINDOW, 0)
{
	BMessenger windowMessenger(this);
	_windowController = new MainWindowController(windowMessenger);
	
	BGroupLayout* verticalGroup = new BGroupLayout(B_VERTICAL);
	verticalGroup->SetInsets(0,0,0,0);
	SetLayout(verticalGroup);
	
	BGroupLayout* horizontalGroup = new BGroupLayout(B_HORIZONTAL);
	verticalGroup->AddItem(horizontalGroup);
	BuildFileLayout(horizontalGroup);		
				
	BBox* errorsBox = new BBox("Errors & Warnings");
	verticalGroup->AddView(errorsBox);
	
	BListView* errorsListView = new BListView();
	errorsBox->AddChild(errorsListView);	
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

void MainWindow::BuildFileLayout(BGroupLayout* horizontalGroup)
{	
	horizontalGroup->SetInsets(5,5,5,5);
	
	_filePathControl = new BTextControl("Makefile Path:", "", new BMessage());
	horizontalGroup->AddView(_filePathControl);
	
	BButton* browseButton = new BButton("Browse..", new BMessage(kBrowseFileMessage));
	horizontalGroup->AddView(browseButton);
	
	BButton* runButton = new BButton("Run", new BMessage(kRunMessage));
	horizontalGroup->AddView(runButton);
	
	BButton* cleanButton = new BButton("Clean", new BMessage(kCleanMessage));
	horizontalGroup->AddView(cleanButton);	
}
