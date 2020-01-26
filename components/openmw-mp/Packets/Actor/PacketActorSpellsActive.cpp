#include <components/openmw-mp/NetworkMessages.hpp>
#include <components/openmw-mp/TimedLog.hpp>
#include "PacketActorSpellsActive.hpp"

using namespace mwmp;

PacketActorSpellsActive::PacketActorSpellsActive(RakNet::RakPeerInterface *peer) : ActorPacket(peer)
{
    packetID = ID_ACTOR_SPELLS_ACTIVE;
}

void PacketActorSpellsActive::Actor(BaseActor &actor, bool send)
{
    // Placeholder
}
