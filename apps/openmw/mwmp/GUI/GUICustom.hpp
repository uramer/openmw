#pragma once
#ifndef OPENMW_GUICUSTOM_HPP
#define OPENMW_GUICUSTOM_HPP

#include "apps/openmw/mwgui/windowbase.hpp"
#include "../LocalPlayer.hpp"
#include <apps\openmw\mwmp\GUI\MPWidget.hpp>

namespace mwmp
{
    class GUICustom : public MWGui::WindowBase, public Gui::MPLayout
    {
        public:
            GUICustom(int id, const std::string& layout);
            void updateProps(BasePlayer::FieldList newProps);

            MyGUI::Widget* getWidget(const std::string name);
            std::string getProp(const std::string name);
            void send(const std::string event, const std::string data);

        private:
            static const std::string ANCHOR;
            static const std::string RELATIVE_POSITION;

            static void log(std::string event, std::string name, std::string data);

            int mId;
            std::map <std::string, std::string> mProps;
            std::map<std::string, Gui::MPWidget*> mFieldWidgets;
            std::vector<Gui::MPWidget*> mMPWidgets;

            void positionRelatively();
            void traverse(MyGUI::Widget* widget);
            void collectFields();
    };
}
#endif //OPENMW_GUICUSTOM_HPP
