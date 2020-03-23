#pragma once
#include "MPButton.hpp"
#ifndef OPENMW_MPAUTOSIZEDBUTTON_HPP
#define OPENMW_MPAUTOSIZEDBUTTON_HPP

namespace Gui
{
    class MPAutoSizedButton :
        public AutoSizedWidget,
        public MPButton
    {
        MYGUI_RTTI_DERIVED(MPAutoSizedButton)

    public:
        MyGUI::IntSize getRequestedSize();
        void setCaption(const MyGUI::UString& _value);
        MPAutoSizedButton() : MPButton(), mPadding(24, 8) {
            MPWidget::initializeWidget(this);
        }

    protected:
        void setPropertyRaw(const std::string& _key, const std::string& _value);
        MyGUI::IntSize mPadding;
    };
}
#endif //OPENMW_MPAUTOSIZEDBUTTON_HPP
