#ifndef OPENMW_PROCESSOROBJECTSOUND_HPP
#define OPENMW_PROCESSOROBJECTSOUND_HPP

#include "BaseObjectProcessor.hpp"

namespace mwmp
{
    class ProcessorObjectSound final: public BaseObjectProcessor
    {
    public:
        ProcessorObjectSound()
        {
            BPP_INIT(ID_OBJECT_SOUND)
        }

        virtual void Do(ObjectPacket &packet, ObjectList &objectList)
        {
            BaseObjectProcessor::Do(packet, objectList);

            //objectList.setObjectSounds(ptrCellStore);
        }

    };
}

#endif //OPENMW_PROCESSOROBJECTSOUND_HPP
