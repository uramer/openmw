#ifndef OPENMW_PACKETGUICUSTOM_HPP
#define OPENMW_PACKETGUICUSTOM_HPP

#include <components/openmw-mp/Packets/Player/PlayerPacket.hpp>

namespace mwmp
{
    class PacketGUICustom : public PlayerPacket
    {
    public:
        PacketGUICustom(RakNet::RakPeerInterface *peer);

        virtual void Packet(RakNet::BitStream *newBitstream, bool send);
    };
}

#endif //OPENMW_PACKETGUICUSTOM_HPP
