#ifndef OPENMW_PACKETPLAYERACTIVESKILLS_HPP
#define OPENMW_PACKETPLAYERACTIVESKILLS_HPP

#include <components/openmw-mp/Packets/Player/PlayerPacket.hpp>

namespace mwmp
{
    class PacketPlayerActiveSkills : public PlayerPacket
    {
    public:
        PacketPlayerActiveSkills(RakNet::RakPeerInterface *peer);

        virtual void Packet(RakNet::BitStream *newBitstream, bool send);
    };
}

#endif //OPENMW_PACKETPLAYERACTIVESKILLS_HPP
