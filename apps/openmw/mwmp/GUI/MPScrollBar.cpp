#include "MPScrollBar.hpp"

namespace Gui
{
    const std::string MPScrollBar::SCROLL = "Scroll";

    std::string MPScrollBar::fieldValue() {
        return std::to_string(getScrollPosition());
    }

    void MPScrollBar::bindEvent(const std::string event) {
        if (event == SCROLL) {
            eventScrollChangePosition += MyGUI::newDelegate(this, &MPScrollBar::scroll);
        }
        else MPBase::bindEvent(event);
    }

    void MPScrollBar::scroll(MyGUI::ScrollBar* _sender, size_t _position) {
        triggerEvent(SCROLL, std::to_string(_position));
    }

    void MPScrollBar::setPropertyRaw(const std::string& _key, const std::string& _value) {
        ScrollBar::setPropertyOverride(_key, _value);
        MPBase::setPropertyRaw(_key, _value);
    }
}
