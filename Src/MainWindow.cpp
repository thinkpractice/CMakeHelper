#include "MainWindow.h"
#include <app/Application.h>
#include <app/Message.h>

#include <interface/Button.h>
#include <interface/TextControl.h>
#include <interface/Box.h>
#include <interface/ListView.h>
#include "Constants.h"

MainWindow::MainWindow(BRect frame)
				: BWindow(frame, "CMakeHelper", B_TITLED_WINDOW, 0)
{
	_windowController = new MainWindowController();
	
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
		case MessageConstants::kBrowseFileMessage:
		{
			_windowController->ShowOpenFileDialog();
		}
		break;
		case MessageConstants::kRunMessage:
		{
			_windowController->RunMake();
		}
		break;
		case MessageConstants::kCleanMessage:
		{
			_windowController->CleanMake();
		}
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
	
	BTextControl* filePathControl = new BTextControl("Makefile Path:", "", new BMessage());
	horizontalGroup->AddView(filePathControl);
	
	BButton* browseButton = new BButton("Browse..", new BMessage(MessageConstants::kBrowseFileMessage));
	horizontalGroup->AddView(browseButton);
	
	BButton* runButton = new BButton("Run", new BMessage(MessageConstants::kRunMessage));
	horizontalGroup->AddView(runButton);
	
	BButton* cleanButton = new BButton("Clean", new BMessage(MessageConstants::kCleanMessage));
	horizontalGroup->AddView(cleanButton);	
}
