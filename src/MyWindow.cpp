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
      mpCanvas(nullptr)
{
    // menubar. We don't have to save the pointer or delete it.
    wxMenuBar *menuBar = new wxMenuBar;
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(wxID_ABOUT);
    helpMenu->Append(wxID_EXIT);
    // helpMenu->Bind(wxEVT_MENU, &MyWindow::OnClose, wxID_EXIT, wxID_EXIT, this);
    menuBar->Append(helpMenu, wxT("&Help"));
    SetMenuBar(menuBar);

    mpStatusBar = CreateStatusBar(1);
    mpStatusBar->SetFieldsCount(1);
    // int style[] = {wxSB_SUNKEN};
    // statusBar->SetStatusStyles(1, style);
    SetStatusBar(mpStatusBar);

    // my gl canvas.
    wxGLAttributes attrs;
    attrs.PlatformDefaults().Defaults().EndList();

    if (MyGLCanvas::IsDisplaySupported(attrs))
    {
        mpCanvas = new MyGLCanvas(this, attrs);
        mpCanvas->SetMinSize(FromDIP(GetSize()));
    }
    Bind(wxEVT_CLOSE_WINDOW, &MyWindow::OnClose, this);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(mpCanvas);
    SetSizer(sizer);

    wxStaticText *s = new wxStaticText(this, wxID_ANY, wxString::Format("Hello"), wxPoint(10, 10));
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
    wxString str = wxString::Format("%.1f fps", frameRate);
    // wxLogDebug(str);
    // mpStatusBar->SetStatusText(str);

    // FIXME: status bar keep giving runtime error from Win32.
    // possible fixes:use fixed positioning for wxStaticText to draw over myGLCanvas, which can be in a box sizer.
}