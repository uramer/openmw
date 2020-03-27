#include "MPTabItem.hpp"
#include "MPSplitter.hpp"

namespace Gui
{
    void MPTabItem::setPropertyRaw(const std::string& _key, const std::string& _value) {
        TabItem::setPropertyOverride(_key, _value);
        MPBase::setPropertyRaw(_key, _value);
    }
}
