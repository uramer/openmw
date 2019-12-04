#include <components/openmw-mp/NetworkMessages.hpp>
#include "PacketPlayerCast.hpp"

#include <components/openmw-mp/TimedLog.hpp>

using namespace mwmp;

PacketPlayerCast::PacketPlayerCast(RakNet::RakPeerInterface *peer) : PlayerPacket(peer)
{
    packetID = ID_PLAYER_CAST;
}

void PacketPlayerCast::Packet(RakNet::BitStream *newBitstream, bool send)
{
    PlayerPacket::Packet(newBitstream, send);

    RW(player->cast.target.isPlayer, send);

    if (player->cast.target.isPlayer)
    {
        RW(player->cast.target.guid, send);
    }
    else
    {
        RW(player->cast.target.refId, send, true);
        RW(player->cast.target.refNum, send);
        RW(player->cast.target.mpNum, send);
    }

    RW(player->cast.type, send);

    if (player->cast.type == mwmp::Cast::ITEM)
        RW(player->cast.itemId, send, true);
    else
    {
        RW(player->cast.pressed, send);
        RW(player->cast.success, send);

        RW(player->cast.instant, send);
        RW(player->cast.spellId, send, true);
    }
}
