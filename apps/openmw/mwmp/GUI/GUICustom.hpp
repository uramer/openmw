#pragma once
#ifndef OPENMW_GUICUSTOM_HPP
#define OPENMW_GUICUSTOM_HPP

#include "apps/openmw/mwgui/windowbase.hpp"
#include "../LocalPlayer.hpp"
#include <apps\openmw\mwmp\GUI\MPWidget.hpp>

namespace mwmp
{
    class GUICustom : public MWGui::WindowBase
    {
        public:
            GUICustom(int id, const std::string& layout);
            void updateProps(BasePlayer::FieldList newProps);
        private:
            static const std::string ANCHOR;
            static const std::string RELATIVE_POSITION;

            static void log(std::string event, std::string name, std::string data);

            int id;
            std::map<std::string, Gui::MPWidget*> fieldWidgets;
            std::vector<Gui::MPWidget*> mMPWidgets;

            void positionRelatively();
            void traverse(MyGUI::Widget* widget);
            void send(std::string event, std::string data);
            void collectFields();
    };
}
#endif //OPENMW_GUICUSTOM_HPP
