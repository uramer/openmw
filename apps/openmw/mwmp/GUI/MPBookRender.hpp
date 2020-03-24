#pragma once
#include <MyGUI_Widget.h>
#include "MPWidget.hpp"
#include <components/widgets/box.hpp>
#include <apps\openmw\mwgui\formatting.hpp>
#ifndef OPENMW_MPBOOKRENDER_HPP
#define OPENMW_MPBOOKRENDER_HPP

namespace Gui
{
    class MPBookRender :
        public MyGUI::Widget,
        public MPWidget
    {
        MYGUI_RTTI_DERIVED(MPBookRender)
        MP_DERIVED(MPBookRender)
        public:
            typedef MWGui::Formatting::Paginator::Page Page;
            typedef MWGui::Formatting::Paginator::Pages Pages;
            typedef MWGui::Formatting::BookFormatter BookFormatter;

            MPBookRender() : Widget(), MPWidget() {
                MPWidget::initializeWidget(this);
            }

        protected:
            BookFormatter mFormatter;
            //Pages mPages;
            void setPropertyRaw(const std::string& _key, const std::string& _value);
    };
}
#endif //OPENMW_MPBOOKRENDER_HPP
