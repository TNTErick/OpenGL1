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
#include <wx/stdpaths.h>

MyWindow::MyWindow(const wxString &title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxDefaultSize),
      // canvas(nullptr),
      mpContent(nullptr),
      menuBar(nullptr),
      mpBitmap(nullptr)
{
    // menubar
    menuBar = new wxMenuBar;
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(wxID_ABOUT);
    helpMenu->Append(wxID_EXIT);

    // helpMenu->Bind(wxEVT_MENU, &MyWindow::OnClose, wxID_EXIT, wxID_EXIT, this);
    menuBar->Append(helpMenu, wxT("&Help"));
    SetMenuBar(menuBar);

    // Connect(wxID_EXIT,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MyWindow::OnClose), nullptr, this);

    //// my gl canvas.
    // wxGLAttributes attrs;
    // attrs.PlatformDefaults().Defaults().EndList();
    //
    // if (MyGLCanvas::IsDisplaySupported(attrs))
    //{
    //     canvas = new MyGLCanvas(this, attrs);
    //     canvas->SetMinSize(FromDIP(wxSize(640, 480)));
    // }
    // Bind(wxEVT_CLOSE_WINDOW, &MyWindow::OnClose, this);

    mpContent = new wxPanel(this);
    mpContent->Bind(wxEVT_PAINT, &MyWindow::OnPaint, this);
    // Bind(wxEVT_SIZE, &MyWindow::OnPaint, this);
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

void MyWindow::OnPaint(wxPaintEvent &event)
{
    if (mpBitmap == nullptr)
    {
        wxString s = wxGetCwd() + "\\resource\\mojang.png";
        wxImage pImage = wxImage(s, wxBITMAP_TYPE_PNG);
        pImage.HasAlpha();

        mpBitmap = new wxBitmap;
        mpBitmap->wxBitmap::wxBitmap(pImage);

        wxLogDebug("mpBitmap is %d okay.", mpBitmap->IsOk());
    }
    wxPaintDC dc(mpContent);
    dc.SetBrush(*wxBLUE_BRUSH);
    dc.DrawRectangle(wxPoint(0, 0), wxSize(1000, 1000));
    dc.DrawBitmap(*mpBitmap, wxPoint(0, 0));
}