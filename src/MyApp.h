/*
 *
 * File:        src/MyApp.h
 * Author:      TNTErick
 * Created:     2023-11-12
 * Modified:    2023-11-12
 * Description: This file declares the main application class `MyApp`.
 *
 */

#pragma once

#include <wx/wx.h>

class MyApp : public wxApp
{
public:
    MyApp();
    bool OnInit() wxOVERRIDE;
};


// FINISHED