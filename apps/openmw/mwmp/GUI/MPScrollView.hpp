#pragma once
#include <MyGUI_ScrollView.h>
#include "MPBase.hpp"
#ifndef OPENMW_MPSCROLLVIEW_HPP
#define OPENMW_MPSCROLLVIEW_HPP

namespace Gui
{
    class MPScrollView :
        public MyGUI::ScrollView,
        public MPBase
    {
        MYGUI_RTTI_DERIVED(MPScrollView)
        MP_DERIVED(MPScrollView)
        public:
            MPScrollView() : ScrollView(), MPBase() {
                MPBase::initializeWidget(this);
            }
        protected:
            void setPropertyRaw(const std::string& _key, const std::string& _value);
    };
}
#endif //OPENMW_MPSCROLLVIEW_HPP
