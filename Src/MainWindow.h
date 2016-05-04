#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <interface/Rect.h>
#include <interface/Window.h>
#include <interface/GroupLayout.h>
#include <interface/TextControl.h>
#include <interface/ListView.h>
#include "MainWindowController.h"

class MainWindow : public BWindow
{
	public:
		MainWindow(BRect frame);
		virtual ~MainWindow();
		
		virtual void MessageReceived(BMessage *message);		
		virtual bool QuitRequested();
		
	private:
		void HandlePropertyChanged(BMessage* message);
	
	private:		
		MainWindowController* _windowController;
		BTextControl* _filePathControl;
		BListView* _errorsListView; 
};

#endif
