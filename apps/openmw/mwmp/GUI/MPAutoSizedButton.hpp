#pragma once
#include "MPWidget.hpp"
#include <components/widgets/box.hpp>
#ifndef OPENMW_MPAUTOSIZEDBUTTON_HPP
#define OPENMW_MPAUTOSIZEDBUTTON_HPP

namespace Gui
{
    class MPAutoSizedButton :
        public AutoSizedWidget,
        public Button,
        public MPWidget
    {
        MYGUI_RTTI_DERIVED(MPAutoSizedButton)
        MP_DERIVED(MPAutoSizedButton)

    public:
        MyGUI::IntSize getRequestedSize();
        void setCaption(const MyGUI::UString& _value);
        MPAutoSizedButton() : Gui::Button(), MPWidget(), mPadding(24, 8) {
            MPWidget::initialize(this);
        }

    protected:
        void setPropertyRaw(const std::string& _key, const std::string& _value);
        std::string mFontSize;
        MyGUI::IntSize mPadding;
    };
}
#endif //OPENMW_MPAUTOSIZEDBUTTON_HPP
