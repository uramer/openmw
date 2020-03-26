#pragma once
#include "MPBase.hpp"
#include <apps\openmw\mwgui\exposedwindow.hpp>
#ifndef OPENMW_MPWINDOW_HPP
#define OPENMW_MPWINDOW_HPP

namespace Gui
{
    class MPWindow :
        public MWGui::Window,
        public MPBase
    {
        MYGUI_RTTI_DERIVED(MPWindow)
        MP_DERIVED(MPWindow)
        public:
            MPWindow() : Window(), MPBase() {
                MPBase::initializeWidget(this);
            }

        protected:
            void setPropertyRaw(const std::string& _key, const std::string& _value);
    };
}
#endif //OPENMW_MPWINDOW_HPP
