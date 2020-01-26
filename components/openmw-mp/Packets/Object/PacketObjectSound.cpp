#include <components/openmw-mp/NetworkMessages.hpp>
#include "PacketObjectSound.hpp"

using namespace mwmp;

PacketObjectSound::PacketObjectSound(RakNet::RakPeerInterface *peer) : ObjectPacket(peer)
{
    packetID = ID_OBJECT_SOUND;
    hasCellData = true;
}

void PacketObjectSound::Object(BaseObject &baseObject, bool send)
{
    ObjectPacket::Object(baseObject, send);
    // Placeholder
}
