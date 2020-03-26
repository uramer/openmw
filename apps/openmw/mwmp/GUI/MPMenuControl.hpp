#pragma once
#include <MyGUI_MenuControl.h>
#include "MPBase.hpp"
#ifndef OPENMW_MPMENUCONTROL_HPP
#define OPENMW_MPMENUCONTROL_HPP

namespace Gui
{
    class MPMenuControl:
        public MyGUI::MenuControl,
        public MPBase
    {
        MYGUI_RTTI_DERIVED(MPMenuControl)
        MP_DERIVED(MPMenuControl)
        public:
            static const std::string ACCEPT;
            static const std::string CLOSE;

            MPMenuControl() : MenuControl(), MPBase() {
                MPBase::initializeWidget(this);
            }
        protected:
            std::string itemData(MyGUI::MenuItem* _item);
            void bindEvent(const std::string event);
            void accept(MyGUI::MenuControl* _sender, MyGUI::MenuItem* _item);
            void close(MyGUI::MenuControl* _sender);

            void setPropertyRaw(const std::string& _key, const std::string& _value);
    };
}
#endif //OPENMW_MPMENUCONTROL_HPP
