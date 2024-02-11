/*
 *
 * File:        src/MyDebugWindow.h
 * Author:      TNTErick
 * Created:     2024-02-08
 * Modified:    2024-02-12
 * Description: `MyDebugWindow` class shows info like fps and sliders like object coordinates.
 *
 */
#pragma once

#include <wx/wx.h>
#include <glm/glm.hpp>

class MyWindow;
class MyDebugWindow : public wxFrame
{
private:
    MyWindow *m_parent;
    wxStaticText *mpLabelFPS;
    wxStaticText *mpLabelPosition;
    wxPanel *mpKeyboardPanel;

public:
    MyDebugWindow(MyWindow *parent);
    void OnFramerateChanged(double fps);
    // void OnCameraPositionChanged(glm::vec3 position);
};

#include "MyWindow.h"