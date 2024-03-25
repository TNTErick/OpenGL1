#include "Mouse.h"

xy::Mouse::Mouse() : isActivated(false) {}

void xy::Mouse::OnMouse(wxMouseEvent &event)
{
    if (!isActivated)
        return;

    wxPoint curPos = event.GetPosition();
    curMovement = (curPos - lastPos) * rateTurn;

    lastPos = curPos;
}

