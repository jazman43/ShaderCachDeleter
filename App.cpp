#include "App.h"



wxIMPLEMENT_APP(App);

App::App()
{
}

App::~App()
{
}

bool App::OnInit()
{
	appFrame = new Main();


	appFrame->Show(true);
	return true;
}


