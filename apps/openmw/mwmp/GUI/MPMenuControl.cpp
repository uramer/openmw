#include "MPMenuControl.hpp"
#include <MyGUI_MenuItem.h>

namespace Gui
{
    const std::string MPMenuControl::ACCEPT = "Accept";
    const std::string MPMenuControl::CLOSE = "Close";

    std::string MPMenuControl::itemData(MyGUI::MenuItem* _item) {
        std::string data = "";
        try {
            data = *_item->getItemData<std::string>();
        }
        catch(...) {
            data = _item->getItemName();
        };
        return data;
    }

    void MPMenuControl::bindEvent(const std::string event) {
        if (event == ACCEPT) {
            eventMenuCtrlAccept += MyGUI::newDelegate(this, &MPMenuControl::accept);
        }
        else if (event == CLOSE) {
            eventMenuCtrlClose += MyGUI::newDelegate(this, &MPMenuControl::close);
        }
        else MPBase::bindEvent(event);
    }

    void MPMenuControl::accept(MyGUI::MenuControl* _sender, MyGUI::MenuItem* _item) {
        triggerEvent(ACCEPT, itemData(_item));
    }

    void MPMenuControl::close(MyGUI::MenuControl* _sender) {
        triggerEvent(CLOSE, "");
    }

    void MPMenuControl::setPropertyRaw(const std::string& _key, const std::string& _value) {
        MenuControl::setPropertyOverride(_key, _value);
        MPBase::setPropertyRaw(_key, _value);
    }
}
