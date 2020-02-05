#ifndef OPENMW_PROCESSORCLIENTSCRIPTLOCAL_HPP
#define OPENMW_PROCESSORCLIENTSCRIPTLOCAL_HPP

#include "../ObjectProcessor.hpp"

namespace mwmp
{
    class ProcessorClientScriptLocal : public ObjectProcessor
    {
    public:
        ProcessorClientScriptLocal()
        {
            BPP_INIT(ID_CLIENT_SCRIPT_LOCAL)
        }
    };
}

#endif //OPENMW_PROCESSORCLIENTSCRIPTLOCAL_HPP
