#pragma once
#include "MPWidget.hpp"
#include <MyGUI_TextBox.h>
#ifndef OPENMW_MPTEXTBOX_HPP
#define OPENMW_MPTEXTBOX_HPP

namespace Gui
{
    class MPTextBox :
        public MyGUI::TextBox,
        public MPWidget
    {
        MYGUI_RTTI_DERIVED(MPTextBox)
        public:
            MPTextBox(): TextBox(), MPWidget() {
                MPWidget::initializeWidget(this);
            }
        protected:
            void setPropertyOverride(const std::string& _key, const std::string& _value);
            void setPropertyRaw(const std::string& _key, const std::string& _value);
    };
}
#endif //OPENMW_MPTEXTBOX_HPP
