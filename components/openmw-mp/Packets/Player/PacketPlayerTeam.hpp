#ifndef OPENMW_PACKETTEAM_HPP
#define OPENMW_PACKETTEAM_HPP

#include <components/openmw-mp/Packets/Player/PlayerPacket.hpp>

namespace mwmp
{
    class PacketPlayerTeam : public PlayerPacket
    {
    public:
        PacketPlayerTeam(RakNet::RakPeerInterface *peer);

        virtual void Packet(RakNet::BitStream *bs, bool send);
    };
}

#endif //OPENMW_PACKETTEAM_HPP
