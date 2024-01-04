/*
 *
 * File:        src/MyWindow.h
 * Author:      TNTErick
 * Created:     2023-11-12
 * Modified:    2023-11-12
 * Description: `MyWindow` class is the class to which the program create window
 *frame according.
 *
 */

#pragma once
#include <wx/wx.h>
#include <wx/menu.h>

class MyGLCanvas; // include this class in the cpp file.

class MyWindow : public wxFrame
{
private:
    // MyGLCanvas *canvas;
    wxPanel* mpContent;
    wxMenuBar *menuBar;
    wxBitmap *mpBitmap;

public:
    MyWindow(const wxString &title);
    ~MyWindow();
    void OnPaint(wxPaintEvent &event);

    void OnClose(const wxEvent &WXUNUSED(event));
};
