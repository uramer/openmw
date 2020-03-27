#include "MPListBox.hpp"
#include "MPSplitter.hpp"

namespace Gui
{
    const std::string MPListBox::SELECT = "Select";
    const std::string MPListBox::SELECT_ACCEPT = "Accept";
    const std::string MPListBox::ITEM_FOCUS = "ItemFocus";
    const std::string MPListBox::ITEM_FOCUS_LOST = "ItemFocusLost";
    const std::string MPListBox::SCROLL = "Scroll";

    std::string MPListBox::fieldValue() {
        return rowData(getItemSelect());
    }

    void MPListBox::addItemWithData(std::string item) {
        std::string empty("");
        auto parts = MPSplitter::split(item);
        switch (parts.size()) {
        case 0: addItem(empty, empty); break;
        case 1: addItem(parts[0], empty); break;
        default: addItem(parts[0], parts[1]); break;
        }
    }
    const size_t npos = -1;
    std::string MPListBox::rowData(size_t index) {
        if (index == npos) return "|";
        MPSplitter data;
        data << index << *getItemDataAt<std::string>(index);
        return data.str();
    }

    void MPListBox::bindEvent(const std::string& event) {
        if (event == SELECT) {
            eventListChangePosition += MyGUI::newDelegate(this, &MPListBox::select);
        }
        else if (event == SELECT_ACCEPT) {
            eventListSelectAccept += MyGUI::newDelegate(this, &MPListBox::selectAccept);
        }
        else if (event == ITEM_FOCUS) {
            eventListMouseItemFocus += MyGUI::newDelegate(this, &MPListBox::itemFocus);
        }
        else if (event == ITEM_FOCUS_LOST) {
            eventListMouseItemFocus += MyGUI::newDelegate(this, &MPListBox::itemFocusLost);
        }
        else if (event == SCROLL) {
            eventListChangeScroll += MyGUI::newDelegate(this, &MPListBox::scroll);
        }
        else MPBase::bindEvent(event);
    }

    void MPListBox::select(MyGUI::Widget* _sender, size_t _index) {
        triggerEvent(SELECT, rowData(_index));
    }

    void MPListBox::selectAccept(MyGUI::Widget* _sender, size_t _index) {
        triggerEvent(SELECT_ACCEPT, rowData(_index));
    }

    void MPListBox::itemFocus(MyGUI::Widget* _sender, size_t _index) {
        if (_index != npos) {
            triggerEvent(ITEM_FOCUS, rowData(_index));
        }
    }

    void MPListBox::itemFocusLost(MyGUI::Widget* _sender, size_t _index) {
        if (_index == npos) {
            triggerEvent(ITEM_FOCUS_LOST, "");
        }
    }

    void MPListBox::scroll(MyGUI::Widget* _sender, size_t _position) {
        triggerEvent(SCROLL, std::to_string(_position));
    }

    void MPListBox::setPropertyRaw(const std::string& _key, const std::string& _value) {
        if (_key == "AddItem") {
            addItemWithData(_value);
        }
        else if (_key == "SetItems") {
            size_t size = getItemCount();
            while (size > 0) {
                removeItemAt(size - 1);
                size--;
            }
            std::string empty("");
            auto items = MPSplitter::split(_value);
            for (std::string item : items) {
                addItemWithData(item);
            }
        }
        else {
            ListBox::setPropertyOverride(_key, _value);
            MPBase::setPropertyRaw(_key, _value);
        }
    }
}
