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
#ifndef __XY_MY_APP_H__
#define __XY_MY_APP_H__

#include <wx/wx.h>

class MyApp : public wxApp
{
public:
    MyApp();
    bool OnInit() wxOVERRIDE;
};

#endif

// FINISHED