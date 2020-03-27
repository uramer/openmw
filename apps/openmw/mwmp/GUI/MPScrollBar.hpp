#pragma once
#include <MyGUI_ScrollBar.h>
#include "MPBase.hpp"
#ifndef OPENMW_MPSCROLLBAR_HPP
#define OPENMW_MPSCROLLBAR_HPP

namespace Gui
{
    class MPScrollBar :
        public MyGUI::ScrollBar,
        public MPBase
    {
        MYGUI_RTTI_DERIVED(MPScrollBar)
        MP_DERIVED(MPScrollBar)
        public:
            static const std::string SCROLL;

            MPScrollBar() : ScrollBar(), MPBase() {
                MPBase::initializeWidget(this);
            }
            std::string fieldValue();
        protected:
            void bindEvent(const std::string& event);
            void scroll(MyGUI::ScrollBar* _sender, size_t _position);
            void setPropertyRaw(const std::string& _key, const std::string& _value);
    };
}
#endif //OPENMW_MPSCROLLBAR_HPP
