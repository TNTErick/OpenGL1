/*
 *
 * File:        src/MyDebugWindow.cpp
 * Author:      TNTErick
 * Created:     2024-02-08
 * Modified:    2024-02-12
 * Description: `MyDebugWindow` class shows info like fps and sliders like object coordinates.
 *
 */

#include "MyDebugWindow.h"

MyDebugWindow::MyDebugWindow(MyWindow *parent)
    : wxFrame(parent, wxID_ANY, "Robot Dance - Debug Info"),
      m_parent(parent)
{
    // Create a sizer to organize the controls
    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

    // 1. FPS Display
    mpLabelFPS = new wxStaticText(this, wxID_ANY, "FPS: 0.0");
    mainSizer->Add(mpLabelFPS, 0, wxALL, 10);

    // 2. WASD Keyboard Visualization
    mpKeyboardPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 100));
    mpKeyboardPanel->SetBackgroundColour(wxColour(200, 200, 200));

    // You may want to draw WASD visualization here using wxDC or another method
    // For simplicity, let's just add a static text
    wxStaticText *keyboardLabel = new wxStaticText(mpKeyboardPanel, wxID_ANY, "WASD Visualization");
    wxBoxSizer *keyboardSizer = new wxBoxSizer(wxHORIZONTAL);
    keyboardSizer->Add(keyboardLabel, 0, wxALL, 10);
    mpKeyboardPanel->SetSizer(keyboardSizer);

    mainSizer->Add(mpKeyboardPanel, 0, wxALL, 10);

    // 3. Camera Position
    mpLabelPosition = new wxStaticText(this, wxID_ANY, "Camera Position: (0, 0, 0)");
    mainSizer->Add(mpLabelPosition, 0, wxALL, 10);

    // Set the sizer for the frame
    SetSizer(mainSizer);

    // You can set additional properties for the frame, such as background color, etc.
    SetBackgroundColour(wxColour(255, 255, 255));
    Show();
}

void MyDebugWindow::OnFramerateChanged(double fps)
{
    if (IsBeingDeleted())
        return;
    mpLabelFPS->SetLabel(wxString::Format("Your openGL now run at %.1f fps", fps));
}