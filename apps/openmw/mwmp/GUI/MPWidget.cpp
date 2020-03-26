#include "MPWidget.hpp"

namespace Gui
{
    void MPWidget::setPropertyRaw(const std::string& _key, const std::string& _value) {
        Widget::setPropertyOverride(_key, _value);
        MPBase::setPropertyRaw(_key, _value);
    }
}
