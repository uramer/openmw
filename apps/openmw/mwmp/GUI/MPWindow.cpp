#include "MPWindow.hpp"

namespace Gui
{
    void MPWindow::setPropertyRaw(const std::string& _key, const std::string& _value) {
        Window::setPropertyOverride(_key, _value);
        MPBase::setPropertyRaw(_key, _value);
    }
}
