#include "PacketGUIEvent.hpp"
#include <components\openmw-mp\NetworkMessages.hpp>

using namespace mwmp;

PacketGUIEvent::PacketGUIEvent(RakNet::RakPeerInterface* peer) : PlayerPacket(peer)
{
    packetID = ID_GUI_EVENT;
    orderChannel = CHANNEL_SYSTEM;
}

void PacketGUIEvent::Packet(RakNet::BitStream* newBitstream, bool send)
{
    PlayerPacket::Packet(newBitstream, send);

    RW(player->guiEvent.tag, send, true);
    RW(player->guiEvent.data, send, true);
}

