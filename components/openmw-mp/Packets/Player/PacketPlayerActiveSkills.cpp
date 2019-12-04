#include "PacketPlayerActiveSkills.hpp"
#include <components/openmw-mp/NetworkMessages.hpp>

using namespace mwmp;

PacketPlayerActiveSkills::PacketPlayerActiveSkills(RakNet::RakPeerInterface *peer) : PlayerPacket(peer)
{
    packetID = ID_PLAYER_ACTIVESKILLS;
}

void PacketPlayerActiveSkills::Packet(RakNet::BitStream *newBitstream, bool send)
{
    PlayerPacket::Packet(newBitstream, send);

    uint32_t spells = 0;

    if (send)
        spells = player->activeSpells.mSpells.size();

    RW(spells, send);

    if (send)
        for (ESM::ActiveSpells::TContainer::const_iterator spell = player->activeSpells.mSpells.begin();
             spell != player->activeSpells.mSpells.end(); ++spell)
        {
            RW(spell->first, true);
            RW(spell->second.mTimeStamp, true);
            uint32_t effects = spell->second.mEffects.size();
            RW(effects, true);

            for (std::vector<ESM::ActiveEffect>::const_iterator effect = spell->second.mEffects.begin();
                 effect != spell->second.mEffects.end(); ++effect)
                RW(effect, true);

        }
    else
        for (uint32_t i = 0; i < spells; i++)
        {
            ESM::ActiveSpells::TContainer::value_type spell;

            RW(spell.first, false);
            RW(spell.second.mTimeStamp, false);
            uint32_t effects;
            RW(effects, false);

            ESM::ActiveEffect effect;
            for (uint32_t j = 0; j < effects; j++)
            {
                RW(effect, false);
                spell.second.mEffects.push_back(effect);
            }
            player->activeSpells.mSpells.insert(spell);
        }
}
