#include "MPProgressBar.hpp"
#include "MPSplitter.hpp"

namespace Gui
{
    void MPProgressBar::setPropertyRaw(const std::string& _key, const std::string& _value) {
        ProgressBar::setPropertyOverride(_key, _value);
        MPWidget::setPropertyRaw(_key, _value);
    }
}
