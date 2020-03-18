#include "GUI.hpp"

#include <components/openmw-mp/NetworkMessages.hpp>

#include <apps/openmw-mp/Script/ScriptFunctions.hpp>
#include <apps/openmw-mp/Networking.hpp>

void GUIFunctions::_MessageBox(unsigned short pid, int id, const char *label) noexcept
{
    Player *player;
    GET_PLAYER(pid, player,);

    player->guiMessageBox.id = id;
    player->guiMessageBox.label = label;
    player->guiMessageBox.type = Player::GUIMessageBox::MessageBox;

    mwmp::PlayerPacket *packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_GUI_MESSAGEBOX);
    packet->setPlayer(player);

    packet->Send(false);
}

void GUIFunctions::CustomMessageBox(unsigned short pid, int id, const char *label, const char *buttons) noexcept
{
    Player *player;
    GET_PLAYER(pid, player,);

    player->guiMessageBox.id = id;
    player->guiMessageBox.label = label;
    player->guiMessageBox.buttons = buttons;
    player->guiMessageBox.type = Player::GUIMessageBox::CustomMessageBox;

    mwmp::PlayerPacket *packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_GUI_MESSAGEBOX);
    packet->setPlayer(player);

    packet->Send(false);
}

void GUIFunctions::InputDialog(unsigned short pid, int id, const char *label, const char *note) noexcept
{
    Player *player;
    GET_PLAYER(pid, player,);

    player->guiMessageBox.id = id;
    player->guiMessageBox.label = label;
    player->guiMessageBox.note = note;
    player->guiMessageBox.type = Player::GUIMessageBox::InputDialog;

    mwmp::PlayerPacket *packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_GUI_MESSAGEBOX);
    packet->setPlayer(player);
    
    packet->Send(false);
}

void GUIFunctions::PasswordDialog(unsigned short pid, int id, const char *label, const char *note) noexcept
{
    Player *player;
    GET_PLAYER(pid, player,);

    player->guiMessageBox.id = id;
    player->guiMessageBox.label = label;
    player->guiMessageBox.note = note;
    player->guiMessageBox.type = Player::GUIMessageBox::PasswordDialog;

    mwmp::PlayerPacket *packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_GUI_MESSAGEBOX);
    packet->setPlayer(player);
    
    packet->Send(false);
}

void GUIFunctions::ListBox(unsigned short pid, int id, const char *label, const char *items)
{
    Player *player;
    GET_PLAYER(pid, player,);

    player->guiMessageBox.id = id;
    player->guiMessageBox.label = label;
    player->guiMessageBox.data = items;
    player->guiMessageBox.type = Player::GUIMessageBox::ListBox;

    mwmp::PlayerPacket *packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_GUI_MESSAGEBOX);
    packet->setPlayer(player);
    
    packet->Send(false);
}

void GUIFunctions::CustomWindow(unsigned short pid, int id, const char* layout, double x, double y, double w, double h, bool relative)
{
    Player* player;
    GET_PLAYER(pid, player, );

    player->guiCustom.id = id;
    player->guiCustom.layout = layout;
    player->guiCustom.x = x;
    player->guiCustom.y = y;
    player->guiCustom.w = w;
    player->guiCustom.h = h;
    player->guiCustom.relative = relative;

    mwmp::PlayerPacket* packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_GUI_CUSTOM);
    packet->setPlayer(player);

    packet->Send(false);
}

void GUIFunctions::ClearQuickKeyChanges(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    player->quickKeyChanges.clear();
}

unsigned int GUIFunctions::GetQuickKeyChangesSize(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    return player->quickKeyChanges.size();
}

int GUIFunctions::GetQuickKeySlot(unsigned short pid, unsigned int index) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    if (index >= player->quickKeyChanges.size())
        return 0;

    return player->quickKeyChanges.at(index).slot;
}

int GUIFunctions::GetQuickKeyType(unsigned short pid, unsigned int index) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    if (index >= player->quickKeyChanges.size())
        return 0;

    return player->quickKeyChanges.at(index).type;
}

const char *GUIFunctions::GetQuickKeyItemId(unsigned short pid, unsigned int index) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, "");

    if (index >= player->quickKeyChanges.size())
        return "invalid";

    return player->quickKeyChanges.at(index).itemId.c_str();
}

void GUIFunctions::AddQuickKey(unsigned short pid, unsigned short slot, int type, const char* itemId) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    mwmp::QuickKey quickKey;
    quickKey.slot = slot;
    quickKey.type = type;
    quickKey.itemId = itemId;

    player->quickKeyChanges.push_back(quickKey);
}

void GUIFunctions::SendQuickKeyChanges(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_PLAYER_QUICKKEYS)->setPlayer(player);
    mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_PLAYER_QUICKKEYS)->Send(false);
}

void GUIFunctions::SetMapVisibility(unsigned short targetPid, unsigned short affectedPid, unsigned short state) noexcept
{
    LOG_MESSAGE(TimedLog::LOG_WARN, "stub");
}

void GUIFunctions::SetMapVisibilityAll(unsigned short targetPid, unsigned short state) noexcept
{
    LOG_MESSAGE(TimedLog::LOG_WARN, "stub");
}

unsigned int GUIFunctions::GetGUIFieldSize(unsigned short pid) noexcept
{
    Player* player;
    GET_PLAYER(pid, player, 0);

    return player->guiEvent.fields.size();
}

const char* GUIFunctions::GetGUIFieldKey(unsigned short pid, unsigned int index) noexcept
{
    Player* player;
    GET_PLAYER(pid, player, "");

    return player->guiEvent.fields[index].first.c_str();
}

const char* GUIFunctions::GetGUIFieldValue(unsigned short pid, unsigned int index) noexcept
{
    Player* player;
    GET_PLAYER(pid, player, "");

    return player->guiEvent.fields[index].second.c_str();
}

// All methods below are deprecated versions of methods from above

void GUIFunctions::InitializeQuickKeyChanges(unsigned short pid) noexcept
{
    ClearQuickKeyChanges(pid);
}
