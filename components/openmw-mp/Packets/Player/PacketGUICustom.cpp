#include "PacketGUICustom.hpp"
#include <components\openmw-mp\NetworkMessages.hpp>

using namespace mwmp;

PacketGUICustom::PacketGUICustom(RakNet::RakPeerInterface *peer) : PlayerPacket(peer)
{
    packetID = ID_GUI_CUSTOM;
    orderChannel = CHANNEL_SYSTEM;
}

void PacketGUICustom::Packet(RakNet::BitStream *newBitstream, bool send)
{
    PlayerPacket::Packet(newBitstream, send);

    RW(player->guiCustom.id, send);
    RW(player->guiCustom.layout, send, true);
    RW(player->guiCustom.x, send);
    RW(player->guiCustom.y, send);
    RW(player->guiCustom.w, send);
    RW(player->guiCustom.h, send);
    RW(player->guiCustom.relative, send);
}

