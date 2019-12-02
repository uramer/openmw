#include <components/openmw-mp/NetworkMessages.hpp>
#include "PacketPlayerTeam.hpp"

mwmp::PacketPlayerTeam::PacketPlayerTeam(RakNet::RakPeerInterface *peer) : PlayerPacket(peer)
{
    packetID = ID_PLAYER_TEAM;
}

void mwmp::PacketPlayerTeam::Packet(RakNet::BitStream *bs, bool send)
{
    PlayerPacket::Packet(bs, send);

    uint32_t count;

    if (send)
        count = static_cast<uint32_t>(player->teamMembers.size());

    RW(count, send);

    if (!send)
    {
        player->teamMembers.clear();
        player->teamMembers.resize(count);
    }

    for (auto &&teamPlayerGuid : player->teamMembers)
    {
        RW(teamPlayerGuid, send, true);
    }
}
