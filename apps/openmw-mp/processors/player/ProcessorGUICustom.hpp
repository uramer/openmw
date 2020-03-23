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
            Script::Call<Script::CallbackIdentity("OnGUICustom")>(
                player.getId(), player.guiCustom.id, player.guiCustom.key.c_str(), player.guiCustom.data.c_str());
        }
    };
}

#endif //OPENMW_PROCESSORGUICUSTOM_HPP
