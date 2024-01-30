/*
 *
 * File:        src/MyWindow.cpp
 * Author:      TNTErick
 * Created:     2023-11-12
 * Modified:    2023-12-26
 * Description: `MyWindow` defines the window frame of the app.
 *
 */

#include "MyWindow.h"
#include "MyGLCanvas.h"

MyWindow::MyWindow(const wxString &title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxDefaultSize),
      mpCanvas(nullptr),
      mpMenuBar(nullptr)
{
    // menubar
    mpMenuBar = new wxMenuBar;
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(wxID_ABOUT);
    helpMenu->Append(wxID_EXIT);

    // helpMenu->Bind(wxEVT_MENU, &MyWindow::OnClose, wxID_EXIT, wxID_EXIT, this);
    mpMenuBar->Append(helpMenu, wxT("&Help"));
    SetMenuBar(mpMenuBar);

    // Connect(wxID_EXIT,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MyWindow::OnClose), nullptr, this);

    // my gl canvas.
    wxGLAttributes attrs;
    attrs.PlatformDefaults().Defaults().EndList();

    if (MyGLCanvas::IsDisplaySupported(attrs))
    {
        mpCanvas = new MyGLCanvas(this, attrs);
        mpCanvas->SetMinSize(FromDIP(wxSize(640, 480)));
    }
    Bind(wxEVT_CLOSE_WINDOW, &MyWindow::OnClose, this);
}

MyWindow::~MyWindow()
{
    Close();
}

void MyWindow::OnClose(const wxEvent &WXUNUSED(event))
{
    /*
    if (event.CanVeto())
        if ( wxMessageBox("The file has not been saved... continue closing?",
                            "Please confirm",
                            wxICON_QUESTION | wxYES_NO) != wxYES )
            {
                event.Veto();
                return;
            }
    */

    //  wxWidget will fire the close event and destroy the canvas.
    // canvas->Destroy();
    Destroy();
}

void MyWindow::OnFrameRateChanged(double frameRate)
{
    // TODO: create wxText in the constructor and update it here.
}