#pragma once
#include <MyGUI_MultiListItem.h>
#include "MPBase.hpp"
#ifndef OPENMW_MPMULTILISTITEM_HPP
#define OPENMW_MPMULTILISTITEM_HPP

namespace Gui
{
    class MPMultiListItem :
        public MyGUI::MultiListItem,
        public MPBase
    {
        MYGUI_RTTI_DERIVED(MPMultiListItem)
        MP_DERIVED(MPMultiListItem)
        public:
            MPMultiListItem() : MultiListItem(), MPBase() {
                MPBase::initializeWidget(this);
            }
        protected:
            void setPropertyRaw(const std::string& _key, const std::string& _value);
    };
}
#endif //OPENMW_MPMULTILISTITEM_HPP
