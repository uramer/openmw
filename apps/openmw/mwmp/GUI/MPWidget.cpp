#include "MPWidget.hpp"

namespace Gui
{
    const std::string MPWidget::MP_FLAG = "MP";
    const std::string MPWidget::FIELD = "Field";
    const char MPWidget::BIND = '=';
    const char MPWidget::EVENT = '@';
    const std::string MPWidget::BUTTON_PRESS = "ButtonPress";
    const std::string MPWidget::MOUSE_CLICK = "MouseClick";

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
            if (binds.count(tag) == 0) continue;
            props[tag] = value;
            widget->setProperty(binds[tag], value);
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

    void MPWidget::initialize(MyGUI::Widget* widget) {
        this->widget = widget;
        widget->setUserString(MP_FLAG, "1");
        widget->setUserData(this);
    }

    void MPWidget::bindEvent(ParsedProperty property, const std::string value) {
        if (events.count(property.eventName) == 0) events[property.eventName] = {};
        events[property.eventName][property.key] = make_pair(value, property.bind);

        if (property.eventName == BUTTON_PRESS) {
            if(widget->eventKeyButtonPressed.empty())
                widget->eventKeyButtonPressed = MyGUI::newDelegate(this, &MPWidget::buttonPressed);
        }
        else if(property.eventName == MOUSE_CLICK) {
            if (widget->eventMouseButtonClick.empty())
                widget->eventMouseButtonClick = MyGUI::newDelegate(this, &MPWidget::mouseClicked);
        }
    }

    void MPWidget::buttonPressed(MyGUI::Widget* _sender, MyGUI::KeyCode _key, MyGUI::Char _char) {
        triggerEvent(BUTTON_PRESS, std::to_string(_key.getValue()));
    }

    void MPWidget::mouseClicked(MyGUI::Widget* _sender) {
        triggerEvent(MOUSE_CLICK, "");
    }

    void MPWidget::triggerEvent(const std::string eventName, const std::string data) {
        if (events.count(eventName) == 0) return;
        std::map<std::string, EventValueBind> properties = events[eventName];
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
                else if (props.count(value) > 0) {
                    setPropertyRaw(key, props[value]);
                }
            }
        }
    }

    void MPWidget::setPropertyOverride(const std::string& _key, const std::string& _value) {
        ParsedProperty property = parseProperty(_key);
        if (property.bind) {
            binds[_value] = makePropertyKey(property);
        }
        if (property.event) {
            bindEvent(property, _value);
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
