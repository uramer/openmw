#include "GUICustom.hpp"

#include <MyGUI_Widget.h>
#include <MyGUI_EditBox.h>
#include <MyGUI_ListBox.h>
#include <MyGUI_RenderManager.h>

#include "../Networking.hpp"
#include "../Main.hpp"
#include "../LocalPlayer.hpp"

#include <components/openmw-mp/TimedLog.hpp>
#include <components\widgets\imagebutton.hpp>
#include <apps\openmw\mwmp\GUI\MPWidget.hpp>

namespace mwmp
{
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

    void GUICustom::updateProps(BasePlayer::FieldList newProps) {
        for (Gui::MPWidget* mpWidget : mMPWidgets) {
            mpWidget->applyProps(newProps);
        }
    }

    void GUICustom::log(std::string event, std::string name, std::string data) {
        LOG_MESSAGE_SIMPLE(
            TimedLog::LOG_VERBOSE, "Custom UI: event %s, tag: %s, data: %s",
            event.c_str(), name.c_str(), data.c_str()
        );
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

    void GUICustom::traverse(MyGUI::Widget* widget) {
        std::string MP = widget->getUserString(Gui::MPWidget::MP_FLAG);
        if (!MP.empty()) {
            Gui::MPWidget* mpWidget = *widget->getUserData<Gui::MPWidget*>();
            mMPWidgets.push_back(mpWidget);
            mpWidget->eventSend += MyGUI::newDelegate(this, &GUICustom::send);
            if (mpWidget->hasField()) {
                fieldWidgets[mpWidget->fieldTag()] = mpWidget;
            }
        }
        size_t children = widget->getChildCount();
        for (size_t i = 0; i < children; i++) {
            traverse(widget->getChildAt(i));
        }
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

    void GUICustom::collectFields() {
        LocalPlayer* localPlayer = Main::get().getLocalPlayer();
        localPlayer->guiCustom.fields.clear();

        for (auto widgetIterator : fieldWidgets) {
            std::string key = widgetIterator.first;
            Gui::MPWidget* widget = widgetIterator.second;
            localPlayer->guiCustom.fields.push_back(make_pair(key, widget->fieldValue()));
        }
    }
}
