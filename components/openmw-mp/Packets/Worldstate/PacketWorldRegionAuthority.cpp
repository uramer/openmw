#include <components/openmw-mp/NetworkMessages.hpp>
#include "PacketWorldRegionAuthority.hpp"

mwmp::PacketWorldRegionAuthority::PacketWorldRegionAuthority(RakNet::RakPeerInterface *peer) : WorldstatePacket(peer)
{
    packetID = ID_WORLD_REGION_AUTHORITY;
    priority = IMMEDIATE_PRIORITY;
    reliability = RELIABLE_ORDERED;
}

void mwmp::PacketWorldRegionAuthority::Packet(RakNet::BitStream *newBitstream, bool send)
{
    WorldstatePacket::Packet(newBitstream, send);

    RW(worldstate->authorityRegion, send, true);
}
