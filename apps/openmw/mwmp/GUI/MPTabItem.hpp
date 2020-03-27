#pragma once
#include <MyGUI_TabItem.h>
#include "MPBase.hpp"
#ifndef OPENMW_MPTABITEM_HPP
#define OPENMW_MPTABITEM_HPP

namespace Gui
{
    class MPTabItem :
        public MyGUI::TabItem,
        public MPBase
    {
        MYGUI_RTTI_DERIVED(MPTabItem)
        MP_DERIVED(MPTabItem)
        public:
            MPTabItem() : TabItem(), MPBase() {
                MPBase::initializeWidget(this);
            }
        protected:
            void setPropertyRaw(const std::string& _key, const std::string& _value);
    };
}
#endif //OPENMW_MPTABITEM_HPP
