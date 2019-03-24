#ifndef OPENMW_PROCESSORCELLRESET_HPP
#define OPENMW_PROCESSORCELLRESET_HPP

#include "../WorldstateProcessor.hpp"

namespace mwmp
{
    class ProcessorCellReset : public WorldstateProcessor
    {
    public:
        ProcessorCellReset()
        {
            BPP_INIT(ID_CELL_RESET)
        }

        virtual void Do(WorldstatePacket &packet, Worldstate &worldstate)
        {
            LOG_MESSAGE_SIMPLE(Log::LOG_INFO, "Received ID_CELL_RESET");
            CellController* cellController = Main::get().getCellController();
            
            for (ESM::Cell cell : worldstate.cellsToReset)
            {
                MWWorld::CellStore * cellStore = cellController->getCellStore(cell);
                if (cellStore != nullptr)
                {
                    LOG_MESSAGE_SIMPLE(Log::LOG_INFO, "Resetting cell %s!", cell.getDescription().c_str());
                    cellStore->clear();
                }
                else
                    LOG_MESSAGE_SIMPLE(Log::LOG_INFO, "Attempted to reset an uninitialized cell %s!", cell.getDescription().c_str());
            }
        }
    };
}

#endif //OPENMW_PROCESSORCELLRESET_HPP
