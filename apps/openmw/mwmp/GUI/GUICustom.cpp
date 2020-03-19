#include "GUICustom.hpp"

#include <MyGUI_Widget.h>
#include <MyGUI_EditBox.h>
#include <MyGUI_ListBox.h>

#include "../Networking.hpp"
#include "../Main.hpp"
#include "../LocalPlayer.hpp"

#include <components/openmw-mp/TimedLog.hpp>

namespace mwmp
{
    const std::string GUICustom::BUTTON_PRESSED = "ButtonPressed";
    const std::string GUICustom::MOUSE_CLICK = "MouseClick";
    const std::string GUICustom::FIELD = "Field";

    GUICustom::GUICustom(const std::string& layout): WindowBase(layout)
    {
        for (MyGUI::Widget* widget : mListWindowRoot)
        {
            traverse(widget);
        }
    }

    void GUICustom::log(std::string event, std::string name, std::string data) {
        LOG_MESSAGE_SIMPLE(
            TimedLog::LOG_VERBOSE, "Custom GUI event: %s, tag: %s, data: %s",
            event.c_str(), name.c_str(), data.c_str()
        );
    }

    void GUICustom::send(std::string tag, std::string data) {
        LocalPlayer* localPlayer = Main::get().getLocalPlayer();
        Networking* networking = Main::get().getNetworking();

        localPlayer->guiEvent.tag = tag;
        localPlayer->guiEvent.data = data;

        collectFields();

        networking->getPlayerPacket(ID_GUI_EVENT)->setPlayer(localPlayer);
        networking->getPlayerPacket(ID_GUI_EVENT)->Send();
    }

    void GUICustom::traverse(MyGUI::Widget* widget) {
        attachEventHandlers(widget);
        findFields(widget);
        MyGUI::ListBox* listBox = dynamic_cast<MyGUI::ListBox*>(widget);
        if (listBox != NULL) prepareList(listBox);

        size_t children = widget->getChildCount();
        for (size_t i = 0; i < children; i++) {
            traverse(widget->getChildAt(i));
        }
    }

    void GUICustom::attachEventHandlers(MyGUI::Widget* widget)
    {
        if (!widget->getUserString(BUTTON_PRESSED).empty()) {
            widget->eventKeyButtonPressed = newDelegate(this, &GUICustom::buttonPressed);
        }
        if (!widget->getUserString(MOUSE_CLICK).empty()) {
            widget->eventMouseButtonClick = newDelegate(this, &GUICustom::mouseClick);
        }
    }

    void GUICustom::findFields(MyGUI::Widget* widget) {
        std::string key = widget->getUserString(FIELD);
        if (!key.empty()) {
            fieldWidgets[key] = widget;
        }
    }

    void GUICustom::prepareList(MyGUI::ListBox* listBox) {
        if (listBox->getUserString("List").empty()) return;
        size_t children = listBox->getChildCount();
        for (size_t i = 0; i < children; i++) {
            auto child = listBox->getChildAt(i);
            std::string row = child->getUserString("Row");
            if (!row.empty()) {
                listBox->addItem(row);
            }
        }
    }

    void GUICustom::buttonPressed(MyGUI::Widget* _sender, MyGUI::KeyCode key, MyGUI::Char _char) {
        std::string tag = _sender->getUserString(BUTTON_PRESSED);
        std::string data = std::to_string(_char);
        log(BUTTON_PRESSED, tag, data);
        send(tag, data);
    }

    void GUICustom::mouseClick(MyGUI::Widget* _sender) {
        std::string tag = _sender->getUserString(MOUSE_CLICK);
        std::string data = "";
        log(MOUSE_CLICK, tag, data);
        send(tag, data);
    }

    void GUICustom::collectFields() {
        LocalPlayer* localPlayer = Main::get().getLocalPlayer();
        localPlayer->guiEvent.fields.clear();

        for (auto widgetIterator: fieldWidgets) {
            std::string key = widgetIterator.first;
            MyGUI::Widget* widget = widgetIterator.second;
            std::string value = "";

            MyGUI::EditBox* editBox = dynamic_cast<MyGUI::EditBox*>(widget);
            if (editBox != NULL)
                value = editBox->getCaption().asUTF8();

            MyGUI::ListBox* listBox = dynamic_cast<MyGUI::ListBox*>(widget);
            if (listBox != NULL) {
                auto index = listBox->getIndexSelected();
                if (index != MyGUI::ITEM_NONE)
                    value = std::to_string(index);
            }
            localPlayer->guiEvent.fields.push_back(make_pair(key, value));
        }
    }
}
