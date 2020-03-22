#include "MPComboBox.hpp"
#include "MPSplitter.hpp"

namespace Gui
{
    const std::string MPComboBox::ACCEPT = "Accept";
    const std::string MPComboBox::CHANGE = "Change";

    std::string MPComboBox::fieldValue() {
        return rowData(getIndexSelected());
    }

    const size_t npos = -1;
    std::string MPComboBox::rowData(size_t index) {
        if (index == npos) return "|";
        MPSplitter data;
        data << index << *getItemDataAt<std::string>(index);
        return data.str();
    }

    void MPComboBox::bindEvent(const std::string event, const std::string value) {
        if (event == ACCEPT) {
            eventComboAccept += MyGUI::newDelegate(this, &MPComboBox::accept);
        }
        else if (event == CHANGE) {
            eventComboChangePosition += MyGUI::newDelegate(this, &MPComboBox::change);
        }
        else MPWidget::bindEvent(event, value);
    }

    void MPComboBox::accept(MyGUI::Widget* _sender) {
        triggerEvent(ACCEPT, rowData(getIndexSelected()));
    }

    void MPComboBox::change(MyGUI::Widget* _sender, size_t _index) {
        triggerEvent(CHANGE, rowData(_index));
    }

    void MPComboBox::setPropertyRaw(const std::string& _key, const std::string& _value) {
        if (_key == "AddItem") {
            auto parts = MPSplitter::split(_value);
            std::string empty("");
            switch (parts.size()) {
            case 0: addItem(empty, empty); break;
            case 1: addItem(parts[0], empty); break;
            default: addItem(parts[0], parts[1]); break;
            }
        }
        else {
            ComboBox::setPropertyOverride(_key, _value);
            MPWidget::setPropertyRaw(_key, _value);
        }
    }
}
