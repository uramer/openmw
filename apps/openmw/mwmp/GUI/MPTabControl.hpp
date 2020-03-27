#pragma once
#include <MyGUI_TabControl.h>
#include "MPBase.hpp"
#ifndef OPENMW_MPTABCONTROL_HPP
#define OPENMW_MPTABCONTROL_HPP

namespace Gui
{
    class MPTabControl :
        public MyGUI::TabControl,
        public MPBase
    {
        MYGUI_RTTI_DERIVED(MPTabControl)
        MP_DERIVED(MPTabControl)
        public:
            static const std::string SELECT;

            MPTabControl() : TabControl(), MPBase() {
                MPBase::initializeWidget(this);
            }
            std::string fieldValue();
        protected:
            std::string itemData(size_t position);
            void bindEvent(const std::string event);
            void select(MyGUI::TabControl* _sender, size_t _position);
            void setPropertyRaw(const std::string& _key, const std::string& _value);
    };
}
#endif //OPENMW_MPTABCONTROL_HPP
