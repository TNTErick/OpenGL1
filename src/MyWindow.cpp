/*
 *
 * File:        src/MyWindow.cpp
 * Author:      TNTErick
 * Created:     2023-11-12
 * Modified:    2023-12-21
 * Description: `MyWin-dow` defines the window frame of the app.
 *
 */

#include "MyWindow.h"
#include "MyGLCanvas.h"

MyWindow::MyWindow(const wxString &title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxDefaultSize),
      canvas(nullptr)
{
    wxGLAttributes attrs;
    attrs.PlatformDefaults().Defaults().EndList();

    if (MyGLCanvas::IsDisplaySupported(attrs))
    {
        canvas = new MyGLCanvas(this, attrs);
        canvas->SetMinSize(FromDIP(wxSize(640, 480)));
    }
    // Bind(wxEVT_CLOSE_WINDOW, &MyWindow::OnClose, this);
}

MyWindow::~MyWindow()
{
    Close();
}

void MyWindow::OnClose(const wxCloseEvent &event)
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
    //canvas->Destroy();
    Destroy();
}