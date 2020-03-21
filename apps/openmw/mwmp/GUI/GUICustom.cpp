#include "GUICustom.hpp"

#include <MyGUI_Widget.h>
#include <MyGUI_EditBox.h>
#include <MyGUI_ListBox.h>
#include <MyGUI_RenderManager.h>

#include "../Networking.hpp"
#include "../Main.hpp"
#include "../LocalPlayer.hpp"

#include <components/openmw-mp/TimedLog.hpp>

namespace mwmp
{
    const std::string GUICustom::BUTTON_PRESSED = "ButtonPressed";
    const std::string GUICustom::MOUSE_CLICK = "MouseClick";
    const std::string GUICustom::FIELD = "Field";
    const std::string GUICustom::BIND = "Bind:";
    const std::string GUICustom::ANCHOR = "Anchor";
    const std::string GUICustom::RELATIVE_POSITION = "RelativePosition";

    GUICustom::GUICustom(int id, const std::string& layout): WindowBase(layout)
    {
        this->id = id;
        for (MyGUI::Widget* widget : mListWindowRoot) {
            traverse(widget);
        }
        positionRelatively();
    }

    void GUICustom::positionRelatively() {
        std::string positionString = mMainWidget->getUserString(RELATIVE_POSITION);
        if (positionString.empty()) return;

        std::string anchorString = mMainWidget->getUserString(ANCHOR);
        MyGUI::FloatSize anchor = MyGUI::FloatSize::parse(anchorString);
        
        MyGUI::FloatSize position = MyGUI::FloatSize::parse(positionString);

        MyGUI::IntSize layerSize = MyGUI::RenderManager::getInstance().getViewSize();
        if (mMainWidget->getLayer()) layerSize = mMainWidget->getLayer()->getSize();

        MyGUI::IntCoord coord = mMainWidget->getCoord();
        coord.left += layerSize.width * position.width - anchor.width * coord.width;
        coord.top += layerSize.height * position.height - anchor.height * coord.height;
        mMainWidget->setCoord(coord);
    }

    void GUICustom::log(std::string event, std::string name, std::string data) {
        LOG_MESSAGE_SIMPLE(
            TimedLog::LOG_VERBOSE, "Custom UI: event %s, tag: %s, data: %s",
            event.c_str(), name.c_str(), data.c_str()
        );
    }

    void GUICustom::send(std::string event, std::string data) {
        LocalPlayer* localPlayer = Main::get().getLocalPlayer();
        Networking* networking = Main::get().getNetworking();

        localPlayer->guiCustom.id = id;
        localPlayer->guiCustom.event = event;
        localPlayer->guiCustom.data = data;

        collectFields();

        networking->getPlayerPacket(ID_GUI_CUSTOM)->setPlayer(localPlayer);
        networking->getPlayerPacket(ID_GUI_CUSTOM)->Send();
    }

    void GUICustom::updateProperties(BasePlayer::FieldList properties) {
        for (auto property : properties) {
            if (propertyMap.find(property.first) == propertyMap.end()) continue;
            auto match = propertyMap[property.first];
            MyGUI::Widget* widget = match.first;
            widget->setProperty(match.second, property.second);
        }
    }

    void GUICustom::traverse(MyGUI::Widget* widget) {
        attachEventHandlers<MyGUI::Widget>(widget);
        findFields(widget);
        findPropertyBindings(widget);
        if (widget->isType<MyGUI::ListBox>()) {
            attachEventHandlers<MyGUI::ListBox>(static_cast<MyGUI::ListBox*>(widget));
        }

        size_t children = widget->getChildCount();
        for (size_t i = 0; i < children; i++) {
            traverse(widget->getChildAt(i));
        }
    }

    template<>
    void GUICustom::attachEventHandlers<MyGUI::Widget>(MyGUI::Widget* widget)
    {
        if (!widget->getUserString(BUTTON_PRESSED).empty()) {
            widget->eventKeyButtonPressed = newDelegate(this, &GUICustom::buttonPressed);
        }
        if (!widget->getUserString(MOUSE_CLICK).empty()) {
            widget->eventMouseButtonClick = newDelegate(this, &GUICustom::mouseClick);
        }
    }

    template<>
    void GUICustom::attachEventHandlers<MyGUI::ListBox>(MyGUI::ListBox* listBox)
    {
        if (!listBox->getUserString(MOUSE_CLICK).empty()) {
            listBox->eventListMouseItemActivate = newDelegate(this, &GUICustom::listMouseItemActivate);
            listBox->eventListSelectAccept = newDelegate(this, &GUICustom::listMouseItemActivate);
        }
    }

    void GUICustom::findFields(MyGUI::Widget* widget) {
        std::string key = widget->getUserString(FIELD);
        if (!key.empty()) {
            fieldWidgets[key] = widget;
        }
    }

    void GUICustom::findPropertyBindings(MyGUI::Widget* widget) {
        for (auto userString : widget->getUserStrings()) {
            bool prefix = std::mismatch(BIND.begin(), BIND.end(), userString.first.begin()).first == BIND.end();
            if (prefix)
            {
                std::string property = userString.first.substr(BIND.size());
                if(!property.empty()) propertyMap[userString.second] = std::make_pair(widget, property);
            }
        }
    }

    void GUICustom::buttonPressed(MyGUI::Widget* _sender, MyGUI::KeyCode _key, MyGUI::Char _char) {
        std::string event = _sender->getUserString(BUTTON_PRESSED);
        std::string data = std::to_string(_key.getValue());
        log(BUTTON_PRESSED, event, data);
        send(event, data);
    }

    void GUICustom::mouseClick(MyGUI::Widget* _sender) {
        std::string event = _sender->getUserString(MOUSE_CLICK);
        std::string data = "";
        log(MOUSE_CLICK, event, data);
        send(event, data);
    }

    void GUICustom::listMouseItemActivate(MyGUI::ListBox* _sender, size_t _index) {
        std::string event = _sender->getUserString(MOUSE_CLICK);
        std::string data = "";
        log(MOUSE_CLICK, event, data);
        send(event, data);
    }

    void GUICustom::collectFields() {
        LocalPlayer* localPlayer = Main::get().getLocalPlayer();
        localPlayer->guiCustom.fields.clear();

        for (auto widgetIterator: fieldWidgets) {
            std::string key = widgetIterator.first;
            MyGUI::Widget* widget = widgetIterator.second;
            std::string value = "";

            if (widget->isType<MyGUI::EditBox>()) {
                value = static_cast<MyGUI::EditBox*>(widget)->getCaption().asUTF8();
            }

            if (widget->isType<MyGUI::ListBox>()) {
                auto index = static_cast<MyGUI::ListBox*>(widget)->getIndexSelected();
                if (index != MyGUI::ITEM_NONE)
                    value = std::to_string(index);
            }

            localPlayer->guiCustom.fields.push_back(make_pair(key, value));
        }
    }
}
