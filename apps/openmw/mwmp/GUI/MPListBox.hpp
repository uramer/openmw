#pragma once
#include "MPBase.hpp"
#include <MyGUI_ListBox.h>
#ifndef OPENMW_MPLISTBOX_HPP
#define OPENMW_MPLISTBOX_HPP

namespace Gui
{
    class MPListBox : 
        public MyGUI::ListBox,
        public MPBase
    {
        MYGUI_RTTI_DERIVED(MPListBox)
        MP_DERIVED(MPListBox)
        public:
            static const std::string SELECT;
            static const std::string SELECT_ACCEPT;
            static const std::string ITEM_FOCUS;
            static const std::string ITEM_FOCUS_LOST;
            static const std::string SCROLL;

            MPListBox(): ListBox(), MPBase() {
                MPBase::initializeWidget(this);
            }
            std::string fieldValue();
        protected:
            std::string rowData(size_t index);
            void bindEvent(const std::string event);
            void select(MyGUI::Widget* _sender, size_t _index);
            void selectAccept(MyGUI::Widget* _sender, size_t _index);
            void itemFocus(MyGUI::Widget* _sender, size_t _index);
            void itemFocusLost(MyGUI::Widget* _sender, size_t _index);
            void scroll(MyGUI::Widget* _sender, size_t _position);

            void setPropertyRaw(const std::string& _key, const std::string& _value);
    };
}
#endif //OPENMW_MPLISTBOX_HPP
