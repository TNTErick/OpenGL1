/*
 *
 * File:        src/xy/FramerateEvent.h
 * Author:      TNTErick
 * Created:     2024-01-30
 * Modified:    2024-01-30
 * Description: The Camera handles input and ViewMatrix.
 *
 */

#pragma once

#include <wx/event.h>

namespace xy
{
    class FramerateEvent;

    wxDECLARE_EVENT(xyEVT_FRAMERATE, xy::FramerateEvent);

    class FramerateEvent : public wxCommandEvent
    {
    private:
        double mFramerate;

    public:
        FramerateEvent(double rate, wxEventType commandType = xyEVT_FRAMERATE, int id = 0)
            : wxCommandEvent(commandType, id),
              mFramerate(rate)
        {
        }

        // You *must* copy here the data to be transported
        FramerateEvent(const FramerateEvent &event)
            : wxCommandEvent(event) { this->SetRate(event.GetRate()); }

        // Required for sending with wxPostEvent()
        wxEvent *Clone() const { return new FramerateEvent(*this); }

        double GetRate() const { return mFramerate; }
        void SetRate(double rate) { mFramerate = rate; }
    };
}