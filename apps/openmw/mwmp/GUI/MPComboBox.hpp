#pragma once
#include <MyGUI_ComboBox.h>
#include "MPWidget.hpp"
#include <components/widgets/box.hpp>
#ifndef OPENMW_MPCOMBOBOX_HPP
#define OPENMW_MPCOMBOBOX_HPP

namespace Gui
{
    class MPComboBox :
        public MyGUI::ComboBox,
        public MPWidget
    {
        MYGUI_RTTI_DERIVED(MPComboBox)
        MP_DERIVED(MPComboBox)
        public:
            static const std::string ACCEPT;
            static const std::string CHANGE;

            MPComboBox() : ComboBox(), MPWidget() {
                MPWidget::initialize(this);
            }
            std::string fieldValue();
        protected:
            std::string rowData(size_t index);
            void bindEvent(const std::string event, const std::string value);
            void accept(MyGUI::Widget* _sender);
            void change(MyGUI::Widget* _sender, size_t _index);

            void setPropertyRaw(const std::string& _key, const std::string& _value);
    };
}
#endif //OPENMW_MPCOMBOBOX_HPP
