/*
 *
 * File:        src/MyApp.cpp
 * Author:      TNTErick
 * Created:     2023-11-12
 * Modified:    2023-11-12
 * Description: This file implements the main application class `MyApp`, which serves as the entry point of the whole program.
 *
 */

#include "MyApp.h"
#include "MyWindow.h"
#include <wx/imagpng.h>

MyApp::MyApp() : wxApp() {}

bool MyApp::OnInit()
{
    wxLogInfo("Hello from GLEW/wxWidgets!");
    if (!wxApp::OnInit())
        return false;

    // wxInitAllImageHandlers(); // to load image formats like PNG.
    wxImage::AddHandler(new wxPNGHandler);

    MyWindow *window = new MyWindow("Test Title");

    if (window == nullptr)
        return false;

    window->Show();
    return true;
}

wxIMPLEMENT_APP(MyApp);

// FINISHED?