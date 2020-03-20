#pragma once
#ifndef OPENMW_GUICUSTOM_HPP
#define OPENMW_GUICUSTOM_HPP

#include "apps/openmw/mwgui/windowbase.hpp"
#include "../LocalPlayer.hpp"

namespace mwmp
{
    class GUIController;
    
    class GUICustom : public MWGui::WindowBase
    {
        friend class GUIController;
        public:
            GUICustom(int id, const std::string& layout);
        private:
            int id;
            static const std::string BUTTON_PRESSED;
            static const std::string MOUSE_CLICK;
            static const std::string FIELD;
            static const std::string LIST;
            static const std::string ROW;
            static const std::string BIND;
            static void log(std::string event, std::string name, std::string data);
            void send(std::string tag, std::string data);

            void updateProperties(BasePlayer::FieldList properties);

            void traverse(MyGUI::Widget* widget);
            void attachEventHandlers(MyGUI::Widget* widget);
            std::map<std::string, MyGUI::Widget*> fieldWidgets;
            void findFields(MyGUI::Widget* widget);
            void prepareList(MyGUI::ListBox* listBox);
            std::map<std::string, std::pair<MyGUI::Widget*, std::string>> propertyMap;
            void findPropertyBindings(MyGUI::Widget* widget);

            void buttonPressed(MyGUI::Widget* _sender, MyGUI::KeyCode key, MyGUI::Char _char);
            void mouseClick(MyGUI::Widget* _sender);

            void collectFields();
    };
}
#endif //OPENMW_GUICUSTOM_HPP
