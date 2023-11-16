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

MyApp::MyApp() : wxApp() {}

bool MyApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    MyWindow *window = new MyWindow("Test Title");

    if (window == nullptr)
        return false;
    window->Show();

    return true;
}

wxIMPLEMENT_APP(MyApp);

// FINISHED?