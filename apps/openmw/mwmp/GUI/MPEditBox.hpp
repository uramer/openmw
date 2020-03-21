#pragma once
#include "MPWidget.hpp"
#include <MyGUI_EditBox.h>
#ifndef OPENMW_MPEDITBOX_HPP
#define OPENMW_MPEDITBOX_HPP

namespace Gui
{
    class MPEditBox : 
        public MyGUI::EditBox, 
        public MPWidget
    {
        MYGUI_RTTI_DERIVED(MPEditBox)
        public:
            MPEditBox(): EditBox(), MPWidget() {
                MPWidget::initialize(this);
            }
            std::string fieldValue();
        protected:
            void setPropertyOverride(const std::string& _key, const std::string& _value);
            void setPropertyRaw(const std::string& _key, const std::string& _value);
    };
}
#endif //OPENMW_MPEDITBOX_HPP
