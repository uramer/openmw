#include "MPTabControl.hpp"
#include "MPSplitter.hpp"

namespace Gui
{
    const std::string MPTabControl::SELECT = "Select";

    std::string MPTabControl::fieldValue() {
        size_t position = getIndexSelected();
        return itemData(position);
    }

    std::string MPTabControl::itemData(size_t position) {
        return std::to_string(position);
    }

    void MPTabControl::bindEvent(const std::string& event) {
        if (event == SELECT) {
            eventTabChangeSelect += MyGUI::newDelegate(this, &MPTabControl::select);
        }
        else MPBase::bindEvent(event);
    }

    void MPTabControl::select(MyGUI::TabControl* _sender, size_t _position) {
        triggerEvent(SELECT, itemData(_position));
    }

    void MPTabControl::setPropertyRaw(const std::string& _key, const std::string& _value) {
        TabControl::setPropertyOverride(_key, _value);
        MPBase::setPropertyRaw(_key, _value);
    }
}
