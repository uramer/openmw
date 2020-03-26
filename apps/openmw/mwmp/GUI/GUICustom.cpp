#include "GUICustom.hpp"

#include <MyGUI_Widget.h>
#include <MyGUI_EditBox.h>
#include <MyGUI_ListBox.h>
#include <MyGUI_RenderManager.h>

#include "../Networking.hpp"
#include "../Main.hpp"
#include "../LocalPlayer.hpp"
#include "./MPBase.hpp"
#include "./MPSplitter.hpp"
#include "../GuiController.hpp"

#include <components/openmw-mp/TimedLog.hpp>
#include <components\widgets\imagebutton.hpp>


namespace mwmp
{
    const std::string GUICustom::ANCHOR = "Anchor";
    const std::string GUICustom::RELATIVE_POSITION = "RelativePosition";

    GUICustom::GUICustom(int id, const std::string& layout) : WindowBase(layout), MPLayout()
    {
        mId = id;
        for (MyGUI::Widget* widget : mListWindowRoot) {
            traverse(widget);
        }
        positionRelatively();

        std::string replaces = mMainWidget->getUserString("Replaces");
        GUIController* gui = Main::get().getGUIController();
        if (!replaces.empty()) {
            auto windows = Gui::MPSplitter::split(replaces);
            for (std::string window : windows) {
                gui->forceHide(window);
            }
        }
    }

    void GUICustom::updateProps(BasePlayer::FieldList newProps) {
        for (Gui::MPBase* mpWidget : mMPWidgets) {
            mpWidget->applyProps(newProps);
        }
        for (auto prop : newProps) {
            mProps[prop.first] = prop.second;
        }
    }

    void GUICustom::updateVisible(MWGui::GuiMode mode) {
        for (Gui::MPBase* mpWidget : mMPWidgets) {
            mpWidget->updateVisible(mode);
        }
    }

    MyGUI::Widget* GUICustom::getWidget(const std::string name) {
        return WindowBase::getWidget(name);
    }

    std::string GUICustom::getProp(const std::string name) {
        if (mProps.count(name) > 0) return mProps[name];
        else "";
    }

    void GUICustom::send(const std::string event, const std::string data) {
        LocalPlayer* localPlayer = Main::get().getLocalPlayer();
        Networking* networking = Main::get().getNetworking();

        localPlayer->guiCustom.id = mId;
        localPlayer->guiCustom.key = event;
        localPlayer->guiCustom.data = data;

        collectFields();

        networking->getPlayerPacket(ID_GUI_CUSTOM)->setPlayer(localPlayer);
        networking->getPlayerPacket(ID_GUI_CUSTOM)->Send();
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
        Gui::MPBase* mpWidget = Gui::MPBase::fromWidget(widget);
        if (mpWidget) {
            mMPWidgets.push_back(mpWidget);
            mpWidget->initializeLayout(this);
            if (mpWidget->hasField()) {
                mFieldWidgets[mpWidget->fieldTag()] = mpWidget;
            }
        }
        size_t children = widget->getChildCount();
        for (size_t i = 0; i < children; i++) {
            traverse(widget->getChildAt(i));
        }
    }

    void GUICustom::collectFields() {
        LocalPlayer* localPlayer = Main::get().getLocalPlayer();
        localPlayer->guiCustom.fields.clear();

        for (auto widgetIterator : mFieldWidgets) {
            std::string key = widgetIterator.first;
            Gui::MPBase* widget = widgetIterator.second;
            localPlayer->guiCustom.fields.push_back(make_pair(key, widget->fieldValue()));
        }
    }
}
