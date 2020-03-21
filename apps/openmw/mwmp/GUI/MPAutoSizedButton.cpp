#include "MPAutoSizedButton.hpp"

namespace Gui
{
    MyGUI::IntSize MPAutoSizedButton::getRequestedSize()
    {
        return getTextSize() + mPadding;
    }

    void MPAutoSizedButton::setCaption(const MyGUI::UString& _value)
    {
        Button::setCaption(_value);
        notifySizeChange(this);
    }

    void MPAutoSizedButton::setPropertyRaw(const std::string& _key, const std::string& _value) {
        if (_key == "ExpandDirection")
        {
            mExpandDirection = MyGUI::Align::parse(_value);
        }
        else if (_key == "TextPadding")
        {
            mPadding = MyGUI::IntSize::parse(_value);
            notifySizeChange(this);
        }
        else
        {
            Button::setPropertyOverride(_key, _value);
            MPWidget::setPropertyRaw(_key, _value);
        }
    }
}
