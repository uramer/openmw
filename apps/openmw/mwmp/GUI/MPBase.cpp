#include "MPBase.hpp"
#include "MPSplitter.hpp"

namespace Gui
{
    const std::string MPBase::MP_FLAG = "MP";
    const char MPBase::BIND = '=';
    const char MPBase::EVENT = '@';
    const char MPBase::WIDGET = '$';

    const std::string MPBase::BUTTON_DOWN = "ButtonDown";
    const std::string MPBase::BUTTON_UP = "ButtonUp";
    const std::string MPBase::MOUSE_DOWN = "MouseDown";
    const std::string MPBase::MOUSE_UP = "MouseUp";
    const std::string MPBase::MOUSE_CLICK = "MouseClick";
    const std::string MPBase::MOUSE_DOUBLECLICK = "MouseDoubleClick";
    const std::string MPBase::MOUSE_WHEEL = "MouseWheel";
    const std::string MPBase::FOCUS = "Focus";
    const std::string MPBase::FOCUS_LOST = "FocusLost";
    const std::string MPBase::ROOT_FOCUS = "RootFocus";
    const std::string MPBase::ROOT_FOCUS_LOST = "RootFocusLost";
    const std::string MPBase::TOOLTIP_SHOW = "ToolTipShow";
    const std::string MPBase::TOOLTIP_HIDE = "ToolTipHide";

    bool MPBase::hasField() {
        return !mFieldTag.empty();
    }

    std::string MPBase::fieldTag() {
        return mFieldTag;
    }

    void MPBase::applyProps(PropList newProps) {
        for (auto prop : newProps) {
            std::string tag = prop.first;
            std::string value = prop.second;
            if (mBinds.count(tag) == 0) continue;
            widget->setProperty(mBinds[tag], value);
        }
    }

    MPBase::ParsedKey MPBase::parseKey(const std::string key) {
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

    std::string MPBase::makeKey(MPBase::ParsedKey key) {
        std::ostringstream result;
        result << key.key;
        if (key.widget) result << WIDGET << key.widgetName;
        if (key.event) result << EVENT << key.eventName;
        return result.str();
    }

    MPBase::ParsedValue MPBase::parseValue(const std::string value) {
        ParsedValue result;
        size_t keyStart = 0;

        if (value[0] == BIND) {
            result.bind = true;
            keyStart = 1;
        }
        else if (value[0] == WIDGET) {
            result.widget = true;
            keyStart = 1;
        }

        result.value = value.substr(keyStart);

        return result;
    }

    std::string MPBase::makeValue(MPBase::ParsedValue value) {
        std::ostringstream result;
        if (value.bind) result << BIND;
        if (value.widget) result << WIDGET;
        result << value.value;
        return result.str();
    }

    void MPBase::initializeWidget(MyGUI::Widget* widget) {
        this->widget = widget;
        widget->setUserString(MP_FLAG, "1");
        widget->setUserData(this);
    }

    void MPBase::buttonDown(MyGUI::Widget* _sender, MyGUI::KeyCode _key, MyGUI::Char _char) {
        triggerEvent(BUTTON_DOWN, std::to_string(_key.getValue()));
    }

    void MPBase::buttonUp(MyGUI::Widget* _sender, MyGUI::KeyCode _key) {
        triggerEvent(BUTTON_UP, std::to_string(_key.getValue()));
    }

    void MPBase::mouseDown(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id) {
        MPSplitter data;
        data << _id.getValue() << _left << _top;
        triggerEvent(MOUSE_DOWN, data.str());
    }

    void MPBase::mouseUp(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id) {
        MPSplitter data;
        data << _id.getValue() << _left << _top;
        triggerEvent(MOUSE_UP, data.str());
    }

    void MPBase::mouseClick(MyGUI::Widget* _sender) {
        triggerEvent(MOUSE_CLICK, "");
    }

    void MPBase::mouseDoubleClick(MyGUI::Widget* _sender) {
        triggerEvent(MOUSE_DOUBLECLICK, "");
    }

    void MPBase::mouseWheel(MyGUI::Widget* _sender, int _rel) {
        triggerEvent(MOUSE_WHEEL, std::to_string(_rel));
    }

    void MPBase::focus(MyGUI::Widget* _sender, MyGUI::Widget* _old) {
        triggerEvent(FOCUS, "");
    }

    void MPBase::focusLost(MyGUI::Widget* _sender, MyGUI::Widget* _old) {
        triggerEvent(FOCUS_LOST, "");
    }

    void MPBase::rootFocus(MyGUI::Widget* _sender, bool _focus) {
        if (_focus) {
            triggerEvent(ROOT_FOCUS, "");
        }
    }

    void MPBase::rootFocusLost(MyGUI::Widget* _sender, bool _focus) {
        if (!_focus) {
            triggerEvent(ROOT_FOCUS_LOST, "");
        }
    }

    void MPBase::toolTipShow(MyGUI::Widget* _sender, const MyGUI::ToolTipInfo& _info) {
        if (_info.type == _info.Show) {
            MPSplitter data;
            data << _info.point.left << _info.point.top;
            triggerEvent(TOOLTIP_SHOW, data.str());
        }
    }

    void MPBase::toolTipHide(MyGUI::Widget* _sender, const MyGUI::ToolTipInfo& _info) {
        if (_info.type == _info.Hide) {
            triggerEvent(TOOLTIP_HIDE, "");
        }
    }

    void MPBase::triggerEvent(const std::string eventName, const std::string data) {
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

    void MPBase::setPropertyOverride(const std::string& _key, const std::string& _value) {
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
                if (parsedValue.widget) {
                    if (parsedValue.value.empty()) {
                        value = fieldValue();
                    }
                    else if (mLayoutReady) {
                        MyGUI::Widget* widget = getWidget(parsedValue.value);
                        MPBase* mpWidget = 0;
                        if(widget) mpWidget = fromWidget(widget);
                        if (mpWidget) value = mpWidget->fieldValue();
                    }
                }
                else if (parsedValue.bind) {
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

    std::string MPBase::fieldValue() {
        return "";
    }

    void MPBase::initializeLayout(MPLayout* layout) {
        mLayout = layout;
        mLayoutReady = true;
        for (auto propertyIterator : mCrossWidgetProperties) {
            std::string widget = propertyIterator.first;
            std::string key = propertyIterator.second.first;
            std::string value = propertyIterator.second.second;
            getWidget(widget)->setProperty(key, value);
        }
    }

    void MPBase::bindEvent(const std::string event) {
        if (event == BUTTON_DOWN) {
            widget->eventKeyButtonPressed += MyGUI::newDelegate(this, &MPBase::buttonDown);
        }
        else if (event == BUTTON_UP) {
            widget->eventKeyButtonReleased += MyGUI::newDelegate(this, &MPBase::buttonUp);
        }
        else if (event == MOUSE_DOWN) {
            widget->eventMouseButtonPressed += MyGUI::newDelegate(this, &MPBase::mouseDown);
        }
        else if (event == MOUSE_UP) {
            widget->eventMouseButtonReleased += MyGUI::newDelegate(this, &MPBase::mouseUp);
        }
        else if (event == MOUSE_CLICK) {
            widget->eventMouseButtonClick += MyGUI::newDelegate(this, &MPBase::mouseClick);
        }
        else if (event == MOUSE_DOUBLECLICK) {
            widget->eventMouseButtonDoubleClick += MyGUI::newDelegate(this, &MPBase::mouseDoubleClick);
        }
        else if (event == MOUSE_WHEEL) {
            widget->eventMouseWheel += MyGUI::newDelegate(this, &MPBase::mouseWheel);
        }
        else if (event == FOCUS) {
            widget->eventMouseSetFocus += MyGUI::newDelegate(this, &MPBase::focus);
            widget->eventKeySetFocus += MyGUI::newDelegate(this, &MPBase::focus);
        }
        else if (event == FOCUS_LOST) {
            widget->eventMouseLostFocus += MyGUI::newDelegate(this, &MPBase::focusLost);
            widget->eventKeyLostFocus += MyGUI::newDelegate(this, &MPBase::focusLost);
        }
        else if (event == ROOT_FOCUS) {
            widget->eventRootKeyChangeFocus += MyGUI::newDelegate(this, &MPBase::rootFocus);
        }
        else if (event == ROOT_FOCUS_LOST) {
            widget->eventRootKeyChangeFocus += MyGUI::newDelegate(this, &MPBase::rootFocusLost);
        }
        else if (event == TOOLTIP_SHOW) {
            widget->eventToolTip += MyGUI::newDelegate(this, &MPBase::toolTipShow);
        }
        else if (event == TOOLTIP_HIDE) {
            widget->eventToolTip += MyGUI::newDelegate(this, &MPBase::toolTipHide);
        }
    }

    void MPBase::setPropertyRaw(const std::string& _key, const std::string& _value) {
        if (_key == "Field") {
            mFieldTag = _value;
        }
        else if (_key == "State") {
            widget->_setWidgetState(_value);
        }
    }
}
