#ifndef OPENMW_GUICONTROLLER_HPP
#define OPENMW_GUICONTROLLER_HPP

#include <components/settings/settings.hpp>

#include "apps/openmw/mwgui/mode.hpp"

#include <components/openmw-mp/Base/BasePlayer.hpp>
#include "GUI/PlayerMarkerCollection.hpp"
#include "GUI/TextInputDialog.hpp"
#include "GUI/GUICustom.hpp"

namespace MWGui
{
    class LocalMapBase;
    class MapWindow;
}

namespace mwmp
{
    class GUIDialogList;
    class GUIChat;
    class GUIController
    {
    public:
        enum GM
        {
            GM_TES3MP_InputBox = MWGui::GM_QuickKeysMenu + 1,
            GM_TES3MP_ListBox,
            GM_TES3MP_Custom

        };
        GUIController();
        ~GUIController();
        void cleanUp();

        void registerWidgets();

        void refreshGuiMode(MWGui::GuiMode guiMode);

        void setupChat();

        void printChatMessage(std::string &msg);
        void setChatVisible(bool chatVisible);

        void showMessageBox(const BasePlayer::GUIMessageBox &guiMessageBox);
        void showCustomMessageBox(const BasePlayer::GUIMessageBox &guiMessageBox);
        void showInputBox(const BasePlayer::GUIMessageBox &guiMessageBox);

        void showDialogList(const BasePlayer::GUIMessageBox &guiMessageBox);

        void processCustom(const BasePlayer::GUICustom& guiCustom);

        /// Return true if any tes3mp gui element in active state
        bool hasFocusedElement();
        /// Returns 0 if there was no events
        bool pressedKey(int key);

        void update(float dt);

        void WM_UpdateVisible(MWGui::GuiMode mode);

        static const std::map<std::string, MWGui::GuiWindow> mForceHideNames;
        void forceHide(std::string window);

        void updatePlayersMarkers(MWGui::LocalMapBase *localMapBase);
        void updateGlobalMapMarkerTooltips(MWGui::MapWindow *pWindow);
        std::string storeLayout(std::string name, std::string source);
        std::string storeResource(std::string name, std::string source);

        ESM::CustomMarker createMarker(const RakNet::RakNetGUID &guid);
        PlayerMarkerCollection mPlayerMarkers;
    private:
        void setGlobalMapMarkerTooltip(MWGui::MapWindow *mapWindow ,MyGUI::Widget* markerWidget, int x, int y);

    private:
        GUIChat *mChat;
        int keySay;
        int keyChatMode;

        long id;
        bool calledInteractiveMessage;
        TextInputDialog *mInputBox;
        GUIDialogList *mListBox;
        std::map<int, GUICustom*> mCustom;
        std::map <std::string, std::string> mLayouts;
        void onInputBoxDone(MWGui::WindowBase* parWindow);
        //MyGUI::Widget *oldFocusWidget, *currentFocusWidget;
    };
}

#endif //OPENMW_GUICONTROLLER_HPP
