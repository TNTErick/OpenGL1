/*
 *
 * File:        src/MyApp.cpp
 * Author:      TNTErick
 * Created:     2023-11-12
 * Modified:    2024-03-15
 * Description: This file implements the main application class `MyApp` and the member class `MyAppTraits`, which serves as the entry point of the whole program.
 *
 */

// #define wxDEBUG_LEVEL 1
#include "MyApp.h"
#include "MyWindow.h"
#include <wx/imagpng.h>
// #include <glm/ext.hpp>
// #include <iostream>

MyApp::MyApp() : wxApp() {}

bool MyApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    wxImage::AddHandler(new wxPNGHandler);
    // wxLog::SetActiveTarget();

    MyWindow *window = new MyWindow("Test Title");

    if (window == nullptr)
        return false;

    window->Show();
    return true;
}

wxIMPLEMENT_APP(MyApp);