#include <components/openmw-mp/NetworkMessages.hpp>
#include "PacketClientScriptLocal.hpp"

using namespace mwmp;

PacketClientScriptLocal::PacketClientScriptLocal(RakNet::RakPeerInterface *peer) : ObjectPacket(peer)
{
    packetID = ID_CLIENT_SCRIPT_LOCAL;
    hasCellData = true;
}

void PacketClientScriptLocal::Object(BaseObject &baseObject, bool send)
{
    ObjectPacket::Object(baseObject, send);
    RW(baseObject.clientVariable.index, send);
    RW(baseObject.clientVariable.variableType, send);

    if (baseObject.clientVariable.variableType == mwmp::VARIABLE_TYPE::SHORT || baseObject.clientVariable.variableType == mwmp::VARIABLE_TYPE::LONG)
        RW(baseObject.clientVariable.intValue, send);
    else if (baseObject.clientVariable.variableType == mwmp::VARIABLE_TYPE::FLOAT)
        RW(baseObject.clientVariable.floatValue, send);
}
