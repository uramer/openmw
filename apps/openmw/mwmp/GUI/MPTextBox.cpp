#include "MPTextBox.hpp"

namespace Gui
{
    void MPTextBox::setPropertyOverride(const std::string& _key, const std::string& _value) {
        MPBase::setPropertyOverride(_key, _value);
    }

    void MPTextBox::setPropertyRaw(const std::string& _key, const std::string& _value) {
        TextBox::setPropertyOverride(_key, _value);
        MPBase::setPropertyRaw(_key, _value);
    }
}
