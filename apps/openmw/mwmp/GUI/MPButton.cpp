#include "MPButton.hpp"

namespace Gui
{
    void MPButton::setPropertyRaw(const std::string& _key, const std::string& _value) {
        Gui::Button::setPropertyOverride(_key, _value);
        MPWidget::setPropertyRaw(_key, _value);
    }
}
