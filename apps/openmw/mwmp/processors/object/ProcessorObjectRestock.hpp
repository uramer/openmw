#ifndef OPENMW_PROCESSOROBJECTRESTOCK_HPP
#define OPENMW_PROCESSOROBJECTRESTOCK_HPP

#include "BaseObjectProcessor.hpp"

namespace mwmp
{
    class ProcessorObjectRestock final: public BaseObjectProcessor
    {
    public:
        ProcessorObjectRestock()
        {
            BPP_INIT(ID_OBJECT_RESTOCK)
        }

        virtual void Do(ObjectPacket &packet, ObjectList &objectList)
        {
            BaseObjectProcessor::Do(packet, objectList);

            objectList.restockObjects(ptrCellStore);
        }
    };
}

#endif //OPENMW_PROCESSOROBJECTRESTOCK_HPP
