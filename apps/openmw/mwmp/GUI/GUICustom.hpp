#pragma once
#ifndef OPENMW_GUICUSTOM_HPP
#define OPENMW_GUICUSTOM_HPP

#include "apps/openmw/mwgui/windowbase.hpp"
#include "../LocalPlayer.hpp"
#include "../GUI/MPBase.hpp"
#include "../../mwgui/mode.hpp"

namespace mwmp
{
    class GUICustom : public MWGui::WindowBase, public Gui::MPLayout
    {
        public:
            GUICustom(int id, const std::string& layout);
            void updateProps(BasePlayer::FieldList newProps);
            void updateVisible(MWGui::GuiMode mode);

            MyGUI::Widget* getWidget(const std::string& name);
            std::string getProp(const std::string& name);
            void send(const std::string& event, const std::string& data);

        private:
            static const std::string ANCHOR;
            static const std::string RELATIVE_POSITION;

            static void log(const std::string& event, const std::string& name, const std::string& data);

            int mId;
            std::map <std::string, std::string> mProps;
            std::map<std::string, Gui::MPBase*> mFieldWidgets;
            std::vector<Gui::MPBase*> mMPWidgets;

            void positionRelatively();
            void traverse(MyGUI::Widget* widget);
            void collectFields();
    };
}
#endif //OPENMW_GUICUSTOM_HPP
