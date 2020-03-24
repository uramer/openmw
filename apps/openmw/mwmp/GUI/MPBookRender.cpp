#include "MPBookRender.hpp"

namespace Gui
{
    void MPBookRender::setPropertyRaw(const std::string& _key, const std::string& _value) {
        if (_key == "Content") {
            mFormatter.markupToWidget(this, _value);
        }
        else {
            Widget::setPropertyOverride(_key, _value);
            MPWidget::setPropertyRaw(_key, _value);
        }
    }
}
