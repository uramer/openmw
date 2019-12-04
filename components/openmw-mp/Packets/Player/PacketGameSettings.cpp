#include "PacketGameSettings.hpp"
#include <components/openmw-mp/NetworkMessages.hpp>

using namespace mwmp;

PacketGameSettings::PacketGameSettings(RakNet::RakPeerInterface *peer) : PlayerPacket(peer)
{
    packetID = ID_GAME_SETTINGS;
    orderChannel = CHANNEL_SYSTEM;
}

void PacketGameSettings::Packet(RakNet::BitStream *newBitstream, bool send)
{
    PlayerPacket::Packet(newBitstream, send);

    RW(player->difficulty, send);
    RW(player->consoleAllowed, send);
    RW(player->bedRestAllowed, send);
    RW(player->wildernessRestAllowed, send);
    RW(player->waitAllowed, send);
    RW(player->enforcedLogLevel, send);
    RW(player->physicsFramerate, send);
}
