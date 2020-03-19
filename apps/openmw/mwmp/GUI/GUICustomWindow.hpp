#pragma once
#ifndef OPENMW_GUICUSTOM_HPP
#define OPENMW_GUICUSTOM_HPP

#include "apps/openmw/mwgui/windowbase.hpp"

namespace mwmp
{
    class GUIController;
    class GUICustomWindow : public MWGui::WindowBase
    {
        friend class GUIController;
        public:
            GUICustomWindow(const std::string& layout);
        private:
            static const std::string BUTTON_PRESSED;
            static const std::string MOUSE_CLICK;
            static const std::string FIELD;
            static void log(std::string event, std::string name, std::string data);
            void send(std::string tag, std::string data);

            void traverse(MyGUI::Widget* widget);
            void attachEventHandlers(MyGUI::Widget* widget);
            void findFields(MyGUI::Widget* widget);
            void prepareList(MyGUI::ListBox* listBox);


            void buttonPressed(MyGUI::Widget* _sender, MyGUI::KeyCode key, MyGUI::Char _char);
            void mouseClick(MyGUI::Widget* _sender);

            std::map<std::string, MyGUI::Widget*> fieldWidgets;
            void collectFields();
    };
}
#endif //OPENMW_GUICUSTOM_HPP
