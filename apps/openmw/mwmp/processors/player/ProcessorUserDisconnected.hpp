#ifndef OPENMW_PROCESSORUSERDISCONNECTED_HPP
#define OPENMW_PROCESSORUSERDISCONNECTED_HPP


#include "../PlayerProcessor.hpp"
#include <components/openmw-mp/Utils.hpp>
#include <apps/openmw/mwbase/environment.hpp>
#include "apps/openmw/mwstate/statemanagerimp.hpp"

namespace mwmp
{
    class ProcessorUserDisconnected final: public PlayerProcessor
    {
    public:
        ProcessorUserDisconnected()
        {
            BPP_INIT(ID_USER_DISCONNECTED)
            avoidReading = true;
        }

        virtual void Do(PlayerPacket &packet, BasePlayer *player)
        {
            if (isLocal())
                MWBase::Environment::get().getStateManager()->requestQuit();
            else if (player != 0)
            {
                mwmp::LocalPlayer *localPlayer = mwmp::Main::get().getLocalPlayer();

                for (std::vector<RakNet::RakNetGUID>::iterator iter = localPlayer->teamMembers.begin(); iter != localPlayer->teamMembers.end(); )
                {
                    if (*iter == guid)
                    {
                        DedicatedPlayer *dedicatedPlayer = PlayerList::getPlayer(guid);
                        LOG_APPEND(TimedLog::LOG_INFO, "- Deleting %s from our team members", dedicatedPlayer->npc.mName.c_str());
                        iter = localPlayer->teamMembers.erase(iter);
                    }
                    else
                        ++iter;
                }

                PlayerList::deletePlayer(guid);
            }
        }
    };
}

#endif //OPENMW_PROCESSORUSERDISCONNECTED_HPP
