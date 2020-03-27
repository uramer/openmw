#pragma once
#include "MPBase.hpp"
#include <MyGUI_EditBox.h>
#ifndef OPENMW_MPEDITBOX_HPP
#define OPENMW_MPEDITBOX_HPP

namespace Gui
{
    class MPEditBox : 
        public MyGUI::EditBox, 
        public MPBase
    {
        MYGUI_RTTI_DERIVED(MPEditBox)
        MP_DERIVED(MPEditBox)
        public:
            static const std::string TEXT_CHANGE;
            static const std::string SELECT_ACCEPT;

            MPEditBox(): EditBox(), MPBase() {
                MPBase::initializeWidget(this);
            }
            std::string fieldValue();
        protected:
            void bindEvent(const std::string& event);
            void textChange(MyGUI::Widget* _sender);
            void selectAccept(MyGUI::Widget* _sender);
            void setPropertyRaw(const std::string& _key, const std::string& _value);
    };
}
#endif //OPENMW_MPEDITBOX_HPP
