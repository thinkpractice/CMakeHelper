#include "MainWindow.h"
#include <app/Application.h>

MainWindow::MainWindow(BRect frame)
				: BWindow(frame, "CMakeHelper", B_TITLED_WINDOW, 0)
{
}

MainWindow::~MainWindow()
{
}

bool MainWindow::QuitRequested()
{
	be_app->PostMessage(B_QUIT_REQUESTED);
	return BWindow::QuitRequested();	
}
