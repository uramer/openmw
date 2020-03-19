#ifndef OPENMW_PROCESSORGUICUSTOM_HPP
#define OPENMW_PROCESSORGUICUSTOM_HPP


#include "../PlayerProcessor.hpp"
#include <apps\openmw\mwmp\Main.cpp>

namespace mwmp
{
    class ProcessorGUICustom final: public PlayerProcessor
    {
    public:
        ProcessorGUICustom()
        {
            BPP_INIT(ID_GUI_CUSTOM)
        }

        virtual void Do(PlayerPacket &packet, BasePlayer *player)
        {
            if (isLocal())
            {
                LOG_MESSAGE_SIMPLE(TimedLog::LOG_INFO, "ID_GUI_CUSTOM, Type %d, MSG %s", player->guiCustom.id,
                                   player->guiCustom.layout.c_str());

                Main::get().getGUIController()->processCustom(player->guiCustom);
            }
        }
    };
}


#endif //OPENMW_PROCESSORGUICUSTOM_HPP
