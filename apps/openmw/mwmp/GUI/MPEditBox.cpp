#include "MPEditBox.hpp"

namespace Gui
{
    std::string MPEditBox::fieldValue() {
        return getCaption();
    }
    void MPEditBox::setPropertyOverride(const std::string& _key, const std::string& _value) {
        MPWidget::setPropertyOverride(_key, _value);
    }

    void MPEditBox::setPropertyRaw(const std::string& _key, const std::string& _value) {
        EditBox::setPropertyOverride(_key, _value);
        MPWidget::setPropertyRaw(_key, _value);
    }
}
