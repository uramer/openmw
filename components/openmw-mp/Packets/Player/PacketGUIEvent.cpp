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

    uint32_t fieldCount = static_cast<uint32_t>(player->guiEvent.fields.size());
    RW(fieldCount, send);
    std::string mapIndex;
    std::string mapValue;
    if (send)
    {
        for (auto value : player->guiEvent.fields)
        {
            mapIndex = value.first;
            mapValue = value.second;
            RW(mapIndex, send, true);
            RW(mapValue, send, true);
        }
    }
    else
    {
        player->guiEvent.fields.clear();
        for (uint32_t n = 0; n < fieldCount; n++)
        {
            RW(mapIndex, send, true);
            RW(mapValue, send, true);
            player->guiEvent.fields.push_back(make_pair(mapIndex, mapValue));
        }
    }
}

