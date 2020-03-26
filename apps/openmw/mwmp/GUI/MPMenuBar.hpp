#pragma once
#include "MPMenuControl.hpp"
#ifndef OPENMW_MPMENUBAR_HPP
#define OPENMW_MPMENUBAR_HPP

namespace Gui
{
    class MPMenuBar:
        public MPMenuControl
    {
        MYGUI_RTTI_DERIVED(MPMenuBar)
        public:
            MPMenuBar() : MPMenuControl() {
                mHideByAccept = false;
                mMenuDropMode = true;
                mIsMenuDrop = false;
                mResizeToContent = false;
            }
    };
}
#endif //OPENMW_MPMENUBAR_HPP
