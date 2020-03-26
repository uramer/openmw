#pragma once
#include "MPBase.hpp"
#include <MyGUI_Widget.h>
#ifndef OPENMW_MPWIDGET_HPP
#define OPENMW_MPWIDGET_HPP

namespace Gui
{
    class MPWidget :
        public MyGUI::Widget,
        public MPBase
    {
        MYGUI_RTTI_DERIVED(MPWidget)
        MP_DERIVED(MPWidget)
        public:
            MPWidget() : Widget(), MPBase() {
                MPBase::initializeWidget(this);
            }

        protected:
            void setPropertyRaw(const std::string& _key, const std::string& _value);
    };
}
#endif //OPENMW_MPWIDGET_HPP
