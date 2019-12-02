#ifndef OPENMW_PROCESSORPLAYERTEAM_HPP
#define OPENMW_PROCESSORPLAYERTEAM_HPP

#include "../PlayerProcessor.hpp"
#include "apps/openmw/mwmp/Main.hpp"
#include "apps/openmw/mwmp/LocalPlayer.hpp"

namespace mwmp
{
    class ProcessorPlayerTeam final: public PlayerProcessor
    {
    public:
        ProcessorPlayerTeam()
        {
            BPP_INIT(ID_PLAYER_TEAM)
        }

        virtual void Do(PlayerPacket &packet, BasePlayer *player)
        {
            if (isLocal())
            {
                LOG_MESSAGE_SIMPLE(TimedLog::LOG_INFO, "Received ID_PLAYER_TEAM about LocalPlayer from server");

                mwmp::LocalPlayer *localPlayer = mwmp::Main::get().getLocalPlayer();

                for (std::vector<RakNet::RakNetGUID>::iterator iter = localPlayer->teamMembers.begin(); iter != localPlayer->teamMembers.end(); )
                {
                    DedicatedPlayer *dedicatedPlayer = PlayerList::getPlayer(*iter);

                    if (dedicatedPlayer)
                    {
                        LOG_APPEND(TimedLog::LOG_INFO, "- Adding %s to our team members", dedicatedPlayer->npc.mName.c_str());
                    }

                    ++iter;
                }
            }
        }
    };
}

#endif //OPENMW_PROCESSORPLAYERTEAM_HPP
