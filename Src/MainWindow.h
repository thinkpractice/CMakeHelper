#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <interface/Rect.h>
#include <interface/Window.h>
#include <interface/GroupLayout.h>
#include <interface/TextControl.h>
#include "MainWindowController.h"

class MainWindow : public BWindow
{
	public:
		MainWindow(BRect frame);
		virtual ~MainWindow();
		
		virtual void MessageReceived(BMessage *message);		
		virtual bool QuitRequested();
	
	private:		
		MainWindowController* _windowController;
		BTextControl* _filePathControl;
};

#endif
