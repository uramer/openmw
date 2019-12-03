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
            mwmp::LocalPlayer *localPlayer = mwmp::Main::get().getLocalPlayer();

            if (isLocal())
            {
                LOG_MESSAGE_SIMPLE(TimedLog::LOG_INFO, "Received ID_PLAYER_TEAM about LocalPlayer %s from server", localPlayer->npc.mName.c_str());

                for (std::vector<RakNet::RakNetGUID>::iterator iter = localPlayer->teamMembers.begin(); iter != localPlayer->teamMembers.end(); )
                {
                    DedicatedPlayer *dedicatedPlayer = PlayerList::getPlayer(*iter);

                    if (dedicatedPlayer)
                    {
                        LOG_APPEND(TimedLog::LOG_INFO, "- Adding DedicatedPlayer %s to our team members", dedicatedPlayer->npc.mName.c_str());
                    }

                    ++iter;
                }
            }
            else if (player != 0)
            {
                LOG_MESSAGE_SIMPLE(TimedLog::LOG_INFO, "Received ID_PLAYER_TEAM about DedicatedPlayer %s from server", player->npc.mName.c_str());

                for (std::vector<RakNet::RakNetGUID>::iterator iter = player->teamMembers.begin(); iter != player->teamMembers.end(); )
                {
                    if (*iter == localPlayer->guid)
                    {
                        LOG_APPEND(TimedLog::LOG_INFO, "- Adding LocalPlayer %s to their team members", localPlayer->npc.mName.c_str());
                    }
                    else
                    {
                        DedicatedPlayer *otherDedicatedPlayer = PlayerList::getPlayer(*iter);

                        if (otherDedicatedPlayer)
                        {
                            LOG_APPEND(TimedLog::LOG_INFO, "- Adding DedicatedPlayer %s to their team members", otherDedicatedPlayer->npc.mName.c_str());
                        }
                    }

                    ++iter;
                }
            }
        }
    };
}

#endif //OPENMW_PROCESSORPLAYERTEAM_HPP
