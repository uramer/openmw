#pragma once
#include "MPBase.hpp"
#include <components/widgets/box.hpp>
#ifndef OPENMW_MPBUTTON_HPP
#define OPENMW_MPBUTTON_HPP

namespace Gui
{
    class MPButton :
        public Gui::Button,
        public MPBase
    {
        MYGUI_RTTI_DERIVED(MPButton)
        MP_DERIVED(MPButton)
        public:
            MPButton() : Gui::Button(), MPBase() {
                MPBase::initializeWidget(this);
            }

        protected:
            void setPropertyRaw(const std::string& _key, const std::string& _value);
    };
}
#endif //OPENMW_MPBUTTON_HPP
