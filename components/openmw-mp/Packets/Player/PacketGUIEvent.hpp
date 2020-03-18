#ifndef OPENMW_PACKETGUIEVENT_HPP
#define OPENMW_PACKETGUIEVENT_HPP

#include <components/openmw-mp/Packets/Player/PlayerPacket.hpp>

namespace mwmp
{
    class PacketGUIEvent : public PlayerPacket
    {
    public:
        PacketGUIEvent(RakNet::RakPeerInterface *peer);

        virtual void Packet(RakNet::BitStream *newBitstream, bool send);
    };
}

#endif //OPENMW_PACKETGUIEVENT_HPP
