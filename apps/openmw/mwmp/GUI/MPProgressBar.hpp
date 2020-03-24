#pragma once
#include <MyGUI_ProgressBar.h>
#include "MPWidget.hpp"
#include <components/widgets/box.hpp>
#ifndef OPENMW_MPPROGRESSBAR_HPP
#define OPENMW_MPPROGRESSBAR_HPP

namespace Gui
{
    class MPProgressBar :
        public MyGUI::ProgressBar,
        public MPWidget
    {
        MYGUI_RTTI_DERIVED(MPProgressBar)
        MP_DERIVED(MPProgressBar)
        public:
            MPProgressBar() : ProgressBar(), MPWidget() {
                MPWidget::initializeWidget(this);
            }

        protected:
            void setPropertyRaw(const std::string& _key, const std::string& _value);
    };
}
#endif //OPENMW_MPPROGRESSBAR_HPP
