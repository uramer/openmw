#ifndef OPENMW_PROCESSORCELLRESET_HPP
#define OPENMW_PROCESSORCELLRESET_HPP

#include "../WorldstateProcessor.hpp"
#include <apps/openmw/mwworld/player.hpp>

namespace mwmp
{
    class ProcessorCellReset final: public WorldstateProcessor
    {
    public:
        ProcessorCellReset()
        {
            BPP_INIT(ID_CELL_RESET)
        }

        virtual void Do(WorldstatePacket &packet, Worldstate &worldstate)
        {
            LOG_MESSAGE_SIMPLE(TimedLog::LOG_INFO, "Received ID_CELL_RESET");

            CellController* cellController = Main::get().getCellController();
            MWBase::World * world = MWBase::Environment::get().getWorld();

            world->reloadCells(&worldstate.cellsToReset);

            /*for (ESM::Cell cell : worldstate.cellsToReset)
            {
                Main::get().getLocalPlayer()->storeCellState(cell, CellState::LOAD);
            }
            Main::get().getLocalPlayer()->sendCellStates();
            Main::get().getLocalPlayer()->clearCellStates();*/
        }
    };
}

#endif //OPENMW_PROCESSORCELLRESET_HPP
