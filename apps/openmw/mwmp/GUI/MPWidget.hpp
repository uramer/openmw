#pragma once
#include <MyGUI_Widget.h>
#include <components\openmw-mp\Base\BasePlayer.hpp>
#ifndef OPENMW_MPWIDGET_HPP
#define OPENMW_MPWIDGET_HPP

namespace Gui
{
    class MPWidget
    {
        public:
            typedef mwmp::BasePlayer::FieldList PropList;
            static const std::string MP_FLAG;
            static const std::string FIELD;
            static const char BIND;
            static const char EVENT;
            static const char DELIMETER;

            static const std::string BUTTON_DOWN;
            static const std::string BUTTON_UP;
            static const std::string MOUSE_DOWN;
            static const std::string MOUSE_UP;
            static const std::string MOUSE_CLICK;
            static const std::string MOUSE_DOUBLECLICK;
            static const std::string MOUSE_WHEEL;
            static const std::string FOCUS;
            static const std::string FOCUS_LOST;
            static const std::string ROOT_FOCUS;
            static const std::string ROOT_FOCUS_LOST;

            typedef MyGUI::delegates::CMultiDelegate2<std::string, std::string> SendHandler;
            SendHandler eventSend;

            bool hasField();
            std::string fieldTag();
            virtual std::string fieldValue();
            void applyProps(PropList props);

        protected:
            typedef std::map<std::string, std::string> StringMap;
            struct ParsedProperty {
                std::string key = "";
                bool bind = false;
                bool event = false;
                std::string eventName = "";
            };
            static ParsedProperty parseProperty(const std::string key);
            static std::string makePropertyKey(ParsedProperty property);

            std::string mFieldTag = "";
            StringMap mProps;
            StringMap mBinds;
            typedef std::string EventName;
            typedef std::pair<std::string, bool> EventValueBind;
            std::map<EventName, std::map<std::string, EventValueBind>> mEvents;

            void initialize(MyGUI::Widget* widget);

            void bindEvent(const std::string event, const std::string value);
            void buttonDown(MyGUI::Widget* _sender, MyGUI::KeyCode _key, MyGUI::Char _char);
            void buttonUp(MyGUI::Widget* _sender, MyGUI::KeyCode _key);
            void mouseDown(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id);
            void mouseUp(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id);
            void mouseClick(MyGUI::Widget* _sender);
            void mouseDoubleClick(MyGUI::Widget* _sender);
            void mouseWheel(MyGUI::Widget* _sender, int _rel);
            void focus(MyGUI::Widget* _sender, MyGUI::Widget* _old);
            void focusLost(MyGUI::Widget* _sender, MyGUI::Widget* _old);
            void rootFocus(MyGUI::Widget* _sender, bool _focus);
            void rootFocusLost(MyGUI::Widget* _sender, bool _focus);
            void triggerEvent(const std::string eventName, const std::string data);

            void setPropertyOverride(const std::string& _key, const std::string& _value);
            virtual void setPropertyRaw(const std::string& _key, const std::string& _value);
        private:
            MyGUI::Widget* widget;
    };
}
#endif //OPENMW_MPWIDGET_HPP
