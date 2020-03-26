#include "MPScrollView.hpp"

namespace Gui
{
    void MPScrollView::setPropertyRaw(const std::string& _key, const std::string& _value) {
        ScrollView::setPropertyOverride(_key, _value);
        MPBase::setPropertyRaw(_key, _value);
    }
}
