#ifndef OPENMW_PROCESSORGUIEVENT_HPP
#define OPENMW_PROCESSORGUIEVENT_HPP

#include "../PlayerProcessor.hpp"

namespace mwmp
{
    class ProcessorGUIEvent : public PlayerProcessor
    {
    public:
        ProcessorGUIEvent()
        {
            BPP_INIT(ID_GUI_EVENT)
        }

        void Do(PlayerPacket &packet, Player &player) override
        {
            DEBUG_PRINTF(strPacketID.c_str());

            Script::Call<Script::CallbackIdentity("OnGUIEvent")>(
                player.getId(), player.guiEvent.tag.c_str(), player.guiEvent.data.c_str());
        }
    };
}

#endif //OPENMW_PROCESSORGUIEVENT_HPP
