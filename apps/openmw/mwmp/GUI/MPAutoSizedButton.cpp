#include "MPAutoSizedButton.hpp"

namespace Gui
{
    MyGUI::IntSize MPAutoSizedButton::getRequestedSize()
    {
        MyGUI::IntSize padding(24, 8);
        if (isUserString("TextPadding"))
            padding = MyGUI::IntSize::parse(getUserString("TextPadding"));

        MyGUI::IntSize size = getTextSize() + MyGUI::IntSize(padding.width, padding.height);
        return size;
    }

    void MPAutoSizedButton::setCaption(const MyGUI::UString& _value)
    {
        Button::setCaption(_value);

        notifySizeChange(this);
    }

    std::string MPAutoSizedButton::fieldValue() {
        return "";
    }

    void MPAutoSizedButton::setPropertyOverride(const std::string& _key, const std::string& _value) {
        MPWidget::setPropertyOverride(_key, _value);
    }

    void MPAutoSizedButton::setPropertyRaw(const std::string& _key, const std::string& _value) {
        if (_key == "ExpandDirection")
        {
            mExpandDirection = MyGUI::Align::parse(_value);
        }
        else
        {
            Button::setPropertyOverride(_key, _value);
            MPWidget::setPropertyRaw(_key, _value);
        }
    }
}
