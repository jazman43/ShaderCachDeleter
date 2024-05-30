#include "Main.h"


Main::Main() : wxFrame(nullptr, wxID_ANY, "Shader Cach Deleter", wxPoint(30,30), wxSize(300,400))
{
    wxMenu* menuFile = new wxMenu;

    menuFile->Append(wxID_EXIT);

    wxMenu* menuHelp = new wxMenu;

    menuHelp->Append(wxID_ABOUT);

    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar(menuBar);

    CreateStatusBar();

    
    
    deleteShaderButton = new wxButton(this, AppID::SHADERBUTID, "Delete shaders", wxPoint(150 / 2, 20), wxSize(150, 50));
    
    //enterPathTextBox = new wxTextCtrl(this, wxID_ANY, "", wxPoint(20, 75), wxSize(250, 50));
    
    quitButton = new wxButton(this, AppID::APPQUITID, "Exit", wxPoint(150 / 2, 150), wxSize(150, 50));

    Bind(wxEVT_MENU, &Main::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &Main::OnExit, this, wxID_EXIT);
    Bind(wxEVT_BUTTON, &Main::OnDeleteShaderButton, this, AppID::SHADERBUTID);
    Bind(wxEVT_BUTTON, &Main::OnQuitButton, this, AppID::APPQUITID);
}

Main::~Main()
{
}



void Main::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void Main::OnAbout(wxCommandEvent& event)
{
    wxLogMessage("this app can delete the shader cache for hogwarts to help prevent start-up crash", wxOK | wxICON_INFORMATION);
}

void Main::OnDeleteShaderButton(wxCommandEvent& event)
{
    SetStatusText("Deleting Shaders!");
    
    
    std::cout << "**:beging deleting:** \n";

    std::string localPath = GetParentDirectory(pathToTemp);

    std::string folders[] = {
        localPath + "\\Hogwarts Legacy\\Saved\\Config",
        localPath + "\\Hogwarts Legacy\\Saved\\Logs"
    };

    for (const auto& folder : folders)
    {
        wxFileName folderPath(folder);
        try {
            if (folderPath.DirExists())
            {
                if (wxFileName::Rmdir(folder, wxPATH_RMDIR_RECURSIVE))
                {                    
                    textInfo = new wxStaticText(this, wxID_ANY, "Folder Deleted: " + folder, wxPoint(20, 220));                                      
                }
            }
            else
                wxLogMessage("Error: Could not delete ${folder}");
                
        }
        catch(const std::exception& e){
            wxLogError("Filesystem error: ${e}");            
        }
        
    }

   

    std::string pcInfoPath = localPath + "\\Hogwarts Legacy\\Saved\\pc_info.json";
    if (wxRemoveFile(pcInfoPath)) {
        wxLogMessage("pc_info.json deleted successfully.");        
    }
    else
    {
        wxLogMessage("Files All-Ready deleted");
    }
    

   

    std::string proagramDataPath = GetSpecialFolderPath(CSIDL_COMMON_APPDATA);

    wxString targetFolder = proagramDataPath + "\\Hogwarts Legacy";
    wxString fileType = "*.ushaderprecache";
    
    wxDir dir(targetFolder);
    if (!dir.IsOpened()) {
       wxLogMessage("could not open Folder");
        return;
    }
    //get file name and set it 
    wxString filename;
    bool cont = dir.GetFirst(&filename,  fileType, wxDIR_DEFAULT);
    while (cont) {
        wxFileName filepath(targetFolder, filename);
        if (wxRemoveFile(filepath.GetFullPath())) {
            wxLogMessage("Deleted: ${filepath.GetFullPath().ToStdString()}");
            
        }
        
        cont = dir.GetNext(&filename);
    }
    
}

void Main::OnQuitButton(wxCommandEvent& event)
{    
    Close(true);
}

std::string Main::GetParentDirectory(const std::string& path) {
    size_t pos = path.find_last_of("\\/");
    if (pos != std::string::npos) {
        return path.substr(0, pos);
    }
    return path;
}

std::string Main::GetSpecialFolderPath(int csidl) {
    char path[MAX_PATH];
    if (SHGetFolderPathA(NULL, csidl, NULL, 0, path) == S_OK) {
        return std::string(path);
    }
    return std::string("");
}

