#pragma once
#include <wx/log.h>
#include <wx/filename.h>
#include <wx/dir.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>
#include "wx/wx.h"
#include <shlobj.h>

class Main : public wxFrame
{
public:
	Main();
	~Main();

private:

	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	std::string GetParentDirectory(const std::string& path);
	std::string GetSpecialFolderPath(int csidl);

	enum AppID {
		SHADERBUTID = 2000,
		APPQUITID =2001
	};


	LPCWSTR hogwartsEXE = L"G:\\SteamLibrary\\steamapps\\common\\Hogwarts Legacy\\HogwartsLegacy.exe";
	std::string pathToTemp = std::getenv("TEMP");
	

public:
	wxButton* deleteShaderButton = nullptr;
	wxButton* quitButton = nullptr;
	wxTextCtrl* enterPathTextBox = nullptr;
	wxStaticText* textInfo = nullptr;

	void OnDeleteShaderButton(wxCommandEvent &event);
	void OnQuitButton(wxCommandEvent &event);

	//wxDECLARE_EVENT_TABLE();
	
};

