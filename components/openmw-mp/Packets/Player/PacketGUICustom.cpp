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
    RW(player->guiCustom.hide, send);

    uint32_t propertyCount = static_cast<uint32_t>(player->guiCustom.properties.size());
    RW(propertyCount, send);
    std::string mapIndex;
    std::string mapValue;
    if (send)
    {
        for (auto value : player->guiCustom.properties)
        {
            mapIndex = value.first;
            mapValue = value.second;
            RW(mapIndex, send, true);
            RW(mapValue, send, true);
        }
    }
    else
    {
        player->guiCustom.properties.clear();
        for (uint32_t n = 0; n < propertyCount; n++)
        {
            RW(mapIndex, send, true);
            RW(mapValue, send, true);
            player->guiCustom.properties.push_back(make_pair(mapIndex, mapValue));
        }
    }
}

