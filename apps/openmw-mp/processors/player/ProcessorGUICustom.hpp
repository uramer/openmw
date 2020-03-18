#ifndef OPENMW_PROCESSORGUICUSTOM_HPP
#define OPENMW_PROCESSORGUICUSTOM_HPP

#include "../PlayerProcessor.hpp"

namespace mwmp
{
    class ProcessorGUICustom : public PlayerProcessor
    {
    public:
        ProcessorGUICustom()
        {
            BPP_INIT(ID_GUI_CUSTOM)
        }

        void Do(PlayerPacket &packet, Player &player) override
        {
            DEBUG_PRINTF(strPacketID.c_str());

            Script::Call<Script::CallbackIdentity("OnGUIAction")>(
                player.getId(), (int)player.guiMessageBox.id, player.guiMessageBox.data.c_str());
        }
    };
}

#endif //OPENMW_PROCESSORGUICUSTOM_HPP
