#pragma once
#include "MPMenuControl.hpp"
#ifndef OPENMW_MPPOPUPMENU_HPP
#define OPENMW_MPPOPUPMENU_HPP

namespace Gui
{
    class MPPopupMenu :
        public MPMenuControl
    {
        MYGUI_RTTI_DERIVED(MPPopupMenu)
    public:
        MPPopupMenu() : MPMenuControl() {
            mHideByLostKey = true;
        }
    };
}
#endif //OPENMW_MPPOPUPMENU_HPP
