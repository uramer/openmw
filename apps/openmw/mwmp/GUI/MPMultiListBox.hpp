#pragma once
#include <MyGUI_MultiListBox.h>
#include "MPBase.hpp"
#ifndef OPENMW_MPMULTILISTBOX_HPP
#define OPENMW_MPMULTILISTBOX_HPP

namespace Gui
{
    class MPMultiListBox :
        public MyGUI::MultiListBox,
        public MPBase
    {
        MYGUI_RTTI_DERIVED(MPMultiListBox)
        MP_DERIVED(MPMultiListBox)
        public:
            MPMultiListBox() : MultiListBox(), MPBase() {
                MPBase::initializeWidget(this);
            }
        protected:
            void setPropertyRaw(const std::string& _key, const std::string& _value);
    };
}
#endif //OPENMW_MPMULTILISTBOX_HPP
