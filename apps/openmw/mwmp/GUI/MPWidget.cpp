#include "MPWidget.hpp"
#include "MPSplitter.hpp"

namespace Gui
{
    const std::string MPWidget::MP_FLAG = "MP";
    const std::string MPWidget::FIELD = "Field";
    const char MPWidget::BIND = '=';
    const char MPWidget::EVENT = '@';
    const char MPWidget::WIDGET = '#';

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
            widget->setProperty(mBinds[tag], value);
        }
    }

    void MPWidget::initializeLayout(MPLayout* layout) {
        mLayout = layout;
        mLayoutReady = true;
        for (auto propertyIterator : mCrossWidgetProperties) {
            std::string widget = propertyIterator.first;
            std::string key = propertyIterator.second.first;
            std::string value = propertyIterator.second.second;
            getWidget(widget)->setProperty(key, value);
        }
    }

    MPWidget::ParsedKey MPWidget::parseKey(const std::string key) {
        ParsedKey result;
        size_t offset = 0;
        const size_t keyStart = 0;

        size_t widgetStart = std::string::npos;
        size_t pos = key.find(WIDGET, offset);
        if (pos != std::string::npos) {
            result.widget = true;
            widgetStart = pos + 1;
            offset = pos + 1;
        }

        size_t eventStart = std::string::npos;
        pos = key.find(EVENT, offset);
        if (pos != std::string::npos) {
            result.event = true;
            eventStart = pos + 1;
        }

        if (result.widget && result.event) {
            result.key = key.substr(keyStart, widgetStart - keyStart - 1);
            result.widgetName = key.substr(widgetStart, eventStart - widgetStart - 1);
            result.eventName= key.substr(eventStart);
        }
        else if (result.widget) {
            result.key = key.substr(keyStart, widgetStart - keyStart - 1);
            result.widgetName = key.substr(widgetStart);
        }
        else if (result.event) {
            result.key = key.substr(keyStart, eventStart - keyStart - 1);
            result.eventName = key.substr(eventStart);
        }
        else {
            result.key = key;
        }

        return result;
    }

    std::string MPWidget::makeKey(MPWidget::ParsedKey key) {
        std::ostringstream result;
        result << key.key;
        if (key.widget) result << WIDGET << key.widgetName;
        if (key.event) result << EVENT << key.eventName;
        return result.str();
    }

    MPWidget::ParsedValue MPWidget::parseValue(const std::string value) {
        ParsedValue result;
        size_t keyStart = 0;

        if (value[0] == BIND) {
            result.bind = true;
            keyStart = 1;
        }

        size_t widgetStart = std::string::npos;
        if (!result.bind) {
            size_t pos = value.find(WIDGET);
            if (pos != std::string::npos) {
                result.widget = true;
                widgetStart = pos + 1;
            }
        }
        
        if (result.widget) {
            result.value = value.substr(keyStart, widgetStart - keyStart - 1);
            result.widgetName = value.substr(widgetStart);
        }
        else {
            result.value = value.substr(keyStart);
        }

        return result;
    }

    std::string MPWidget::makeValue(MPWidget::ParsedValue value) {
        std::ostringstream result;
        if (value.bind) result << BIND;
        result << value.value;
        if (value.widget) result << WIDGET << value.widgetName;
        return result.str();
    }

    void MPWidget::initializeWidget(MyGUI::Widget* widget) {
        this->widget = widget;
        widget->setUserString(MP_FLAG, "1");
        widget->setUserData(this);
    }

    void MPWidget::bindEvent(const std::string event) {
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
        MyGUI::VectorStringPairs properties = mEvents[eventName];
        for (auto property : properties) {
            std::string key = property.first;
            std::string value = property.second;
            if (key.empty()) {
                mLayout->send(value, data);
            }
            else {
                setPropertyOverride(key, value);
            }
        }
    }

    void MPWidget::setPropertyOverride(const std::string& _key, const std::string& _value) {
        ParsedKey parsedKey = parseKey(_key);

        if (parsedKey.event) {
            ParsedKey eventKey = parsedKey;
            eventKey.event = false;
            bool first = mEvents.count(eventKey.eventName) == 0;
            if (first) mEvents[eventKey.eventName] = {};
            mEvents[eventKey.eventName].push_back(make_pair(makeKey(eventKey), _value));
            if (first) bindEvent(eventKey.eventName);
        }
        else {
            ParsedValue parsedValue = parseValue(_value);

            if (parsedKey.widget) {
                parsedKey.widget = false;
                std::string key = makeKey(parsedKey);
                if (mLayoutReady)
                    getWidget(parsedKey.widgetName)->setProperty(key, _value);
                else
                    mCrossWidgetProperties[parsedKey.widgetName] = make_pair(key, _value);
            }
            else {
                std::string value = _value;
                if (parsedValue.bind) {
                    parsedValue.bind = false;
                    mBinds[parsedValue.value] = _key;
                    if (mLayoutReady) {
                        value = getProp(parsedValue.value);
                    }
                }
                setPropertyRaw(_key, value);
            }
        }
    }

    void MPWidget::setPropertyRaw(const std::string& _key, const std::string& _value) {
        if (_key == FIELD) {
            mFieldTag = _value;
        }
    }
}
