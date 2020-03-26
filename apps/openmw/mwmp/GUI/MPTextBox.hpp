#pragma once
#include "MPBase.hpp"
#include <MyGUI_TextBox.h>
#ifndef OPENMW_MPTEXTBOX_HPP
#define OPENMW_MPTEXTBOX_HPP

namespace Gui
{
    class MPTextBox :
        public MyGUI::TextBox,
        public MPBase
    {
        MYGUI_RTTI_DERIVED(MPTextBox)
        public:
            MPTextBox(): TextBox(), MPBase() {
                MPBase::initializeWidget(this);
            }
        protected:
            void setPropertyOverride(const std::string& _key, const std::string& _value);
            void setPropertyRaw(const std::string& _key, const std::string& _value);
    };
}
#endif //OPENMW_MPTEXTBOX_HPP
