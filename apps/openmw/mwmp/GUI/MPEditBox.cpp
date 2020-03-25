#include "MPEditBox.hpp"

namespace Gui
{
    const std::string MPEditBox::TEXT_CHANGE = "TextChange";
    const std::string MPEditBox::SELECT_ACCEPT = "Accept";

    std::string MPEditBox::fieldValue() {
        return getCaption();
    }

    void MPEditBox::bindEvent(const std::string event) {
        if (event == TEXT_CHANGE) {
            eventEditTextChange += MyGUI::newDelegate(this, &MPEditBox::textChange);
        }
        else if (event == SELECT_ACCEPT) {
            eventEditSelectAccept += MyGUI::newDelegate(this, &MPEditBox::selectAccept);
        }
        else MPWidget::bindEvent(event);
    }

    void MPEditBox::textChange(MyGUI::Widget* _sender) {
        triggerEvent(TEXT_CHANGE, "");
    }

    void MPEditBox::selectAccept(MyGUI::Widget* _sender) {
        triggerEvent(SELECT_ACCEPT, "");
    }

    void MPEditBox::setPropertyRaw(const std::string& _key, const std::string& _value) {
        EditBox::setPropertyOverride(_key, _value);
        MPWidget::setPropertyRaw(_key, _value);
    }
}
