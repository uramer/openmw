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
            static const std::string BUTTON_PRESS;
            static const std::string MOUSE_CLICK;

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
            StringMap props;
            StringMap binds;
            typedef std::string EventName;
            typedef std::pair<std::string, bool> EventValueBind;
            std::map<EventName, std::map<std::string, EventValueBind>> events;

            void initialize(MyGUI::Widget* widget);

            void bindEvent(ParsedProperty property, const std::string value);
            void buttonPressed(MyGUI::Widget* _sender, MyGUI::KeyCode _key, MyGUI::Char _char);
            void mouseClicked(MyGUI::Widget* _sender);
            void triggerEvent(const std::string eventName, const std::string data);

            void setPropertyOverride(const std::string& _key, const std::string& _value);
            virtual void setPropertyRaw(const std::string& _key, const std::string& _value);
        private:
            MyGUI::Widget* widget;
    };
}
#endif //OPENMW_MPWIDGET_HPP
