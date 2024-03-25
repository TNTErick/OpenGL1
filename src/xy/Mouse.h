/*
 *
 * File:        src/xy/Mouse.h
 * Author:      TNTErick
 * Created:     2024-03-11
 * Modified:    2024-03-11
 * Description: The Class handles Mouse Events.
 *
 */

#pragma once

#include "wx/wx.h"

namespace xy
{
    class Mouse
    {
    private:
        static constexpr double rateTurn = .1;
        bool isActivated;
        wxPoint lastPos;
        wxPoint curMovement;

    public:
        Mouse();
        inline void OnActivate() {isActivated = true;}
        void OnMouse(wxMouseEvent &);
        inline const wxPoint &GetMovement() const { return curMovement; }
    };
}