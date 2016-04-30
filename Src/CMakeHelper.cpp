#include "CMakeHelper.h"
#include "MainWindow.h"

CMakeHelper::CMakeHelper()
				: BApplication("application/x-vnd.CMakeHelper")
{
	BRect mainWindowRect(100.0f, 100.0f, 600.0f, 400.0f);
	MainWindow* mainWindow = new MainWindow(mainWindowRect);
	mainWindow->Show(); 
}

CMakeHelper::~CMakeHelper()
{
}

int main()
{
	CMakeHelper cmakeHelper;
	cmakeHelper.Run();
	return 0;
}
