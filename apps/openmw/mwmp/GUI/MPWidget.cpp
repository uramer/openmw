#include "MPWidget.hpp"
#include "MPSplitter.hpp"

namespace Gui
{
    const std::string MPWidget::MP_FLAG = "MP";
    const std::string MPWidget::FIELD = "Field";
    const char MPWidget::BIND = '=';
    const char MPWidget::EVENT = '@';

    const std::string MPWidget::BUTTON_DOWN = "ButtonDown";
    const std::string MPWidget::BUTTON_UP = "ButtonUp";
    const std::string MPWidget::MOUSE_DOWN = "MouseDown";
    const std::string MPWidget::MOUSE_UP = "MouseUp";
    const std::string MPWidget::MOUSE_CLICK = "MouseClick";
    const std::string MPWidget::MOUSE_DOUBLECLICK = "MouseDoubleClick";
    const std::string MPWidget::MOUSE_WHEEL = "MouseWheel";
    const std::string MPWidget::FOCUS = "Focus";
    const std::string MPWidget::FOCUS_LOST = "FocusLost";
    const std::string MPWidget::ROOT_FOCUS = "RootFocus";
    const std::string MPWidget::ROOT_FOCUS_LOST = "RootFocusLost";

    bool MPWidget::hasField() {
        return !mFieldTag.empty();
    }

    std::string MPWidget::fieldTag() {
        return mFieldTag;
    }

    std::string MPWidget::fieldValue() {
        return "";
    }

    void MPWidget::applyProps(PropList newProps) {
        for (auto prop : newProps) {
            std::string tag = prop.first;
            std::string value = prop.second;
            if (mBinds.count(tag) == 0) continue;
            mProps[tag] = value;
            widget->setProperty(mBinds[tag], value);
        }
    }

    MPWidget::ParsedProperty MPWidget::parseProperty(const std::string key) {
        ParsedProperty result;
        size_t offset = 0;
        if (key.at(0) == BIND) {
            result.bind = true;
            offset = 1;
        }

        size_t pos = key.find(EVENT);
        if (pos != std::string::npos) {
            result.event = true;
            result.key = key.substr(offset, pos - offset);
            result.eventName = key.substr(pos + 1);
        }
        else {
            result.key = key.substr(offset);
        }

        return result;
    }

    std::string MPWidget::makePropertyKey(ParsedProperty property) {
        if (!property.event) return property.key;
        return property.key + EVENT + property.eventName;
    }

    void MPWidget::initializeWidget(MyGUI::Widget* widget) {
        this->widget = widget;
        widget->setUserString(MP_FLAG, "1");
        widget->setUserData(this);
    }

    void MPWidget::bindEvent(const std::string event, const std::string value) {
        if (event == BUTTON_DOWN) {
            widget->eventKeyButtonPressed += MyGUI::newDelegate(this, &MPWidget::buttonDown);
        }
        else if (event == BUTTON_UP) {
            widget->eventKeyButtonReleased += MyGUI::newDelegate(this, &MPWidget::buttonUp);
        }
        else if (event == MOUSE_DOWN) {
            widget->eventMouseButtonPressed += MyGUI::newDelegate(this, &MPWidget::mouseDown);
        }
        else if (event == MOUSE_UP) {
            widget->eventMouseButtonReleased += MyGUI::newDelegate(this, &MPWidget::mouseUp);
        }
        else if(event == MOUSE_CLICK) {
            widget->eventMouseButtonClick += MyGUI::newDelegate(this, &MPWidget::mouseClick);
        }
        else if (event == MOUSE_DOUBLECLICK) {
            widget->eventMouseButtonDoubleClick += MyGUI::newDelegate(this, &MPWidget::mouseDoubleClick);
        }
        else if (event == MOUSE_WHEEL) {
            widget->eventMouseWheel += MyGUI::newDelegate(this, &MPWidget::mouseWheel);
        }
        else if (event == FOCUS) {
            widget->eventMouseSetFocus += MyGUI::newDelegate(this, &MPWidget::focus);
            widget->eventKeySetFocus += MyGUI::newDelegate(this, &MPWidget::focus);
        }
        else if (event == FOCUS_LOST) {
            widget->eventMouseLostFocus += MyGUI::newDelegate(this, &MPWidget::focusLost);
            widget->eventKeyLostFocus += MyGUI::newDelegate(this, &MPWidget::focusLost);
        }
        else if (event == ROOT_FOCUS) {
            widget->eventRootKeyChangeFocus += MyGUI::newDelegate(this, &MPWidget::rootFocus);
        }
        else if (event == ROOT_FOCUS_LOST) {
            widget->eventRootKeyChangeFocus += MyGUI::newDelegate(this, &MPWidget::rootFocusLost);
        }
    }

    void MPWidget::buttonDown(MyGUI::Widget* _sender, MyGUI::KeyCode _key, MyGUI::Char _char) {
        triggerEvent(BUTTON_DOWN, std::to_string(_key.getValue()));
    }

    void MPWidget::buttonUp(MyGUI::Widget* _sender, MyGUI::KeyCode _key) {
        triggerEvent(BUTTON_UP, std::to_string(_key.getValue()));
    }

    void MPWidget::mouseDown(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id) {
        MPSplitter data;
        data << _id.getValue() << _left << _top;
        triggerEvent(MOUSE_DOWN, data.str());
    }

    void MPWidget::mouseUp(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id) {
        MPSplitter data;
        data << _id.getValue() << _left << _top;
        triggerEvent(MOUSE_UP, data.str());
    }

    void MPWidget::mouseClick(MyGUI::Widget* _sender) {
        triggerEvent(MOUSE_CLICK, "");
    }

    void MPWidget::mouseDoubleClick(MyGUI::Widget* _sender) {
        triggerEvent(MOUSE_DOUBLECLICK, "");
    }

    void MPWidget::mouseWheel(MyGUI::Widget* _sender, int _rel) {
        triggerEvent(MOUSE_WHEEL, std::to_string(_rel));
    }

    void MPWidget::focus(MyGUI::Widget* _sender, MyGUI::Widget* _old) {
        triggerEvent(FOCUS, "");
    }

    void MPWidget::focusLost(MyGUI::Widget* _sender, MyGUI::Widget* _old) {
        triggerEvent(FOCUS_LOST, "");
    }

    void MPWidget::rootFocus(MyGUI::Widget* _sender, bool _focus) {
        if (_focus) {
            triggerEvent(ROOT_FOCUS, "");
        }
    }

    void MPWidget::rootFocusLost(MyGUI::Widget* _sender, bool _focus) {
        if (!_focus) {
            triggerEvent(ROOT_FOCUS_LOST, "");
        }
    }

    void MPWidget::triggerEvent(const std::string eventName, const std::string data) {
        if (mEvents.count(eventName) == 0) return;
        std::map<std::string, EventValueBind> properties = mEvents[eventName];
        for (auto property : properties) {
            std::string key = property.first;
            std::string value = property.second.first;
            if (key.empty()) {
                eventSend(value, data);
            }
            else {
                bool bind = property.second.second;
                if (!bind) {
                    setPropertyRaw(key, value);
                }
                else if (mProps.count(value) > 0) {
                    setPropertyRaw(key, mProps[value]);
                }
            }
        }
    }

    void MPWidget::setPropertyOverride(const std::string& _key, const std::string& _value) {
        ParsedProperty property = parseProperty(_key);
        if (property.bind) {
            mBinds[_value] = makePropertyKey(property);
        }
        if (property.event) {
            bool first = mEvents.count(property.eventName) == 0;
            if (first) mEvents[property.eventName] = {};
            mEvents[property.eventName][property.key] = make_pair(_value, property.bind);
            if(first) bindEvent(property.eventName, _value);
        }
        if (!property.event && !property.bind) {
            setPropertyRaw(_key, _value);
        }
    }

    void MPWidget::setPropertyRaw(const std::string& _key, const std::string& _value) {
        if (_key == FIELD) {
            mFieldTag = _value;
        }
    }
}
