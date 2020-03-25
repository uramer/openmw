#pragma once
#include <MyGUI_Widget.h>
#include <components\openmw-mp\Base\BasePlayer.hpp>
#include <apps\openmw\mwgui\layout.hpp>
#ifndef OPENMW_MPWIDGET_HPP
#define OPENMW_MPWIDGET_HPP

namespace Gui
{
    class MPLayout {
        public:
            virtual MyGUI::Widget* getWidget(const std::string name) { return 0; };
            virtual std::string getProp(const std::string name) { return ""; };
            virtual void send(const std::string event, const std::string data) {};
    };
    class MPWidget
    {
        public:
            typedef mwmp::BasePlayer::FieldList PropList;
            static const std::string MP_FLAG;
            static const std::string FIELD;
            static const char BIND;
            static const char EVENT;
            static const char WIDGET;

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

            static MPWidget* fromWidget(MyGUI::Widget* widget) {
                if (!widget->getUserString(MP_FLAG).empty()) {
                    return *widget->getUserData<MPWidget*>();
                }
                return 0;
            }

            MPWidget() : mLayout(0), widget(0) {
                mLayoutReady = false;
            }

            bool hasField();
            std::string fieldTag();
            virtual std::string fieldValue();
            void applyProps(PropList props);

            virtual void initializeLayout(MPLayout* layout);

        protected:
            struct ParsedKey {
                std::string key = "";
                bool event = false;
                std::string eventName = "";
                bool widget = false;
                std::string widgetName = "";
            };
            static ParsedKey parseKey(const std::string key);
            static std::string makeKey(ParsedKey key);
            struct ParsedValue {
                bool bind = false;
                std::string value = "";
                bool widget = false;
            };
            static ParsedValue parseValue(const std::string value);
            static std::string makeValue(ParsedValue value);

            std::string mFieldTag = "";
            std::map<std::string, std::string> mBinds;
            typedef std::string EventName;
            std::map<EventName, MyGUI::VectorStringPairs> mEvents;

            void initializeWidget(MyGUI::Widget* widget);

            MyGUI::Widget* getWidget(const std::string name) {
                if (name.empty()) return widget;
                return mLayout->getWidget(name);
            }

            std::string getProp(const std::string name) {
                return mLayout->getProp(name);
            }

            virtual void bindEvent(const std::string event);
            void triggerEvent(const std::string eventName, const std::string data);
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

            void setPropertyOverride(const std::string& _key, const std::string& _value);
            virtual void setPropertyRaw(const std::string& _key, const std::string& _value);
        private:
            MPLayout* mLayout;
            bool mLayoutReady;
            MyGUI::Widget* widget;
            std::map <std::string, std::pair<std::string, std::string>> mCrossWidgetProperties;
    };
}

#define MP_DERIVED(className) \
protected:\
void setPropertyOverride(const std::string& _key, const std::string& _value) {\
    MPWidget::setPropertyOverride(_key, _value);\
}

#endif //OPENMW_MPWIDGET_HPP
