#include "MPMultiListBox.hpp"
#include "MPSplitter.hpp"

namespace Gui
{

    void MPMultiListBox::setPropertyRaw(const std::string& _key, const std::string& _value) {
        MultiListBox::setPropertyOverride(_key, _value);
        MPBase::setPropertyRaw(_key, _value);
    }
}
