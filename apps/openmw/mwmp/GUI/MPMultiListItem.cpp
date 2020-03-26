#include "MPMultiListItem.hpp"
#include "MPSplitter.hpp"

namespace Gui
{

    void MPMultiListItem::setPropertyRaw(const std::string& _key, const std::string& _value) {
        MultiListItem::setPropertyOverride(_key, _value);
        MPBase::setPropertyRaw(_key, _value);
    }
}
