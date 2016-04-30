#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <interface/Rect.h>
#include <interface/Window.h>

class MainWindow : public BWindow
{
	public:
		MainWindow(BRect frame);
		virtual ~MainWindow();
		
		virtual bool QuitRequested();
};

#endif
