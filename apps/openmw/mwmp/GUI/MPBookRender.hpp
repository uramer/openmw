#pragma once
#include <MyGUI_Widget.h>
#include "MPBase.hpp"
#include <apps/openmw/mwgui/formatting.hpp>
#ifndef OPENMW_MPBOOKRENDER_HPP
#define OPENMW_MPBOOKRENDER_HPP

namespace Gui
{
    class MPBookRender :
        public MyGUI::Widget,
        public MPBase
    {
        MYGUI_RTTI_DERIVED(MPBookRender)
        MP_DERIVED(MPBookRender)
        public:
            typedef MWGui::Formatting::Paginator::Page Page;
            typedef MWGui::Formatting::Paginator::Pages Pages;
            typedef MWGui::Formatting::BookFormatter BookFormatter;

            MPBookRender() : Widget(), MPBase() {
                MPBase::initializeWidget(this);
            }

        protected:
            BookFormatter mFormatter;
            //Pages mPages;
            void setPropertyRaw(const std::string& _key, const std::string& _value);
    };
}
#endif //OPENMW_MPBOOKRENDER_HPP
