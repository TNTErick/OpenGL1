/*
 *
 * File:        src/MyWindow.cpp
 * Author:      TNTErick
 * Created:     2023-11-12
 * Modified:    2024-02-12
 * Description: `MyWindow` defines the window frame of the app.
 *
 */

#include "MyWindow.h"
#include "MyGLCanvas.h"
#include "xy/Mouse.h"

MyWindow::MyWindow(const wxString &title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(1280, 720)),
      mpCanvas(nullptr),
      mpDebugInfoFrame(nullptr)
{
    // menubar. We don't have to save the pointer or delete it.
    wxMenuBar *menuBar = new wxMenuBar;
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(wxID_ABOUT);
    helpMenu->Append(wxID_EXIT);
    // helpMenu->Bind(wxEVT_MENU, &MyWindow::OnClose, wxID_EXIT, wxID_EXIT, this);
    menuBar->Append(helpMenu, wxT("&Help"));
    SetMenuBar(menuBar);

    // my gl canvas.
    wxGLAttributes attrs;
    attrs.PlatformDefaults().Defaults().EndList();

    if (MyGLCanvas::IsDisplaySupported(attrs))
    {
        mpCanvas = new MyGLCanvas(this, attrs);
        mpCanvas->SetMinSize(FromDIP(GetSize()));
    }
    Bind(wxEVT_CLOSE_WINDOW, &MyWindow::OnClose, this);

    // debug window.
    mpDebugInfoFrame = new MyDebugWindow(this);

    // take-in the keyboard event.
    Bind(wxEVT_CHAR_HOOK, &MyWindow::OnKeyDown, this);
    Bind(wxEVT_MOTION, &MyWindow::OnMouseMove, this);
    Bind(wxEVT_LEFT_DOWN, &MyWindow::OnClickIn, this);
}

MyWindow::~MyWindow()
{
    Close();
    // TODO: test if we should manually delete things.
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

void MyWindow::OnFramerateChanged(double framerate)
{
    if (nullptr == mpDebugInfoFrame)
        return;
    mpDebugInfoFrame->OnFramerateChanged(framerate);
}

void MyWindow::OnKeyDown(wxKeyEvent &evt)
{
    wxChar ch;
    while (WXK_NONE != (ch = evt.GetUnicodeKey()))
        switch (ch)
        {
        case 'W':
            mpCanvas->OnKeyHeld(MoveDirection::FRONT);
            return;
        case 'S':
            mpCanvas->OnKeyHeld(MoveDirection::BACK);
            return;
        case 'A':
            mpCanvas->OnKeyHeld(MoveDirection::LEFT);
            return;
        case 'D':
            mpCanvas->OnKeyHeld(MoveDirection::RIGHT);
            return;
        case 'Q':
            mpCanvas->OnKeyHeld(MoveDirection::DOWN);
            return;
        case 'E':
            mpCanvas->OnKeyHeld(MoveDirection::UP);
            return;
        }

    while (WXK_NONE != (ch = evt.GetKeyCode()))
        switch (evt.GetKeyCode())
        {
        case WXK_LEFT:
            mpCanvas->OnMouseMove(wxPoint(0, -1));
            break;
        case WXK_RIGHT:
            mpCanvas->OnMouseMove(wxPoint(0, 1));
            break;
        case WXK_UP:
            mpCanvas->OnMouseMove(wxPoint(1, 0));
            break;
        case WXK_DOWN:
            mpCanvas->OnMouseMove(wxPoint(-1, 0));
            break;
        case WXK_ESCAPE:
            // leave focus.
            break;
        }
}

void MyWindow::OnMouseMove(wxMouseEvent &event)
{
    mMouse.OnMouse(event);
    mpCanvas->OnMouseMove(mMouse.GetMovement());
    event.Skip(); // pass the event to default event handlers.
}