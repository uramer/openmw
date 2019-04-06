#include <components/openmw-mp/NetworkMessages.hpp>

#include <apps/openmw-mp/Networking.hpp>
#include <apps/openmw-mp/Player.hpp>
#include <apps/openmw-mp/Script/ScriptFunctions.hpp>
#include <apps/openmw-mp/CellController.hpp>
#include <fstream>

#include <apps/openmw-mp/Utils.hpp>

#include "Worldstate.hpp"

using namespace std;
using namespace mwmp;

BaseWorldstate *WorldstateFunctions::readWorldstate;
BaseWorldstate WorldstateFunctions::writeWorldstate;

void WorldstateFunctions::ReadReceivedWorldstate() noexcept
{
    readWorldstate = mwmp::Networking::getPtr()->getReceivedWorldstate();
}

void WorldstateFunctions::CopyReceivedWorldstateToStore() noexcept
{
    writeWorldstate = *readWorldstate;
}

void WorldstateFunctions::ClearMapChanges() noexcept
{
    writeWorldstate.mapTiles.clear();
}

unsigned int WorldstateFunctions::GetMapChangesSize() noexcept
{
    return readWorldstate->mapTiles.size();
}

const char *WorldstateFunctions::GetWeatherRegion() noexcept
{
    return readWorldstate->weather.region.c_str();
}

int WorldstateFunctions::GetWeatherCurrent() noexcept
{
    return readWorldstate->weather.currentWeather;
}

int WorldstateFunctions::GetWeatherNext() noexcept
{
    return readWorldstate->weather.nextWeather;
}

int WorldstateFunctions::GetWeatherQueued() noexcept
{
    return readWorldstate->weather.queuedWeather;
}

double WorldstateFunctions::GetWeatherTransitionFactor() noexcept
{
    return readWorldstate->weather.transitionFactor;
}

int WorldstateFunctions::GetMapTileCellX(unsigned int index) noexcept
{
    return readWorldstate->mapTiles.at(index).x;
}

int WorldstateFunctions::GetMapTileCellY(unsigned int index) noexcept
{
    return readWorldstate->mapTiles.at(index).y;
}

void WorldstateFunctions::SetAuthorityRegion(const char* authorityRegion) noexcept
{
    writeWorldstate.authorityRegion = authorityRegion;
}

void WorldstateFunctions::SetWeatherRegion(const char* region) noexcept
{
    writeWorldstate.weather.region = region;
}

void WorldstateFunctions::SetWeatherForceState(bool forceState) noexcept
{
    writeWorldstate.forceWeather = forceState;
}

void WorldstateFunctions::SetWeatherCurrent(int currentWeather) noexcept
{
    writeWorldstate.weather.currentWeather = currentWeather;
}

void WorldstateFunctions::SetWeatherNext(int nextWeather) noexcept
{
    writeWorldstate.weather.nextWeather = nextWeather;
}

void WorldstateFunctions::SetWeatherQueued(int queuedWeather) noexcept
{
    writeWorldstate.weather.queuedWeather = queuedWeather;
}

void WorldstateFunctions::SetWeatherTransitionFactor(double transitionFactor) noexcept
{
    writeWorldstate.weather.transitionFactor = transitionFactor;
}

void WorldstateFunctions::SetHour(double hour) noexcept
{
    writeWorldstate.time.hour = hour;
}

void WorldstateFunctions::SetDay(int day) noexcept
{
    writeWorldstate.time.day = day;
}

void WorldstateFunctions::SetMonth(int month) noexcept
{
    writeWorldstate.time.month = month;
}

void WorldstateFunctions::SetYear(int year) noexcept
{
    writeWorldstate.time.year = year;
}

void WorldstateFunctions::SetDaysPassed(int daysPassed) noexcept
{
    writeWorldstate.time.daysPassed = daysPassed;
}

void WorldstateFunctions::SetTimeScale(double timeScale) noexcept
{
    writeWorldstate.time.timeScale = timeScale;
}

void WorldstateFunctions::SetPlayerCollisionState(bool state) noexcept
{
    writeWorldstate.hasPlayerCollision = state;
}

void WorldstateFunctions::SetActorCollisionState(bool state) noexcept
{
    writeWorldstate.hasActorCollision = state;
}

void WorldstateFunctions::SetPlacedObjectCollisionState(bool state) noexcept
{
    writeWorldstate.hasPlacedObjectCollision = state;
}

void WorldstateFunctions::UseActorCollisionForPlacedObjects(bool useActorCollision) noexcept
{
    writeWorldstate.useActorCollisionForPlacedObjects = useActorCollision;
}

void WorldstateFunctions::AddEnforcedCollisionRefId(const char *refId) noexcept
{
    writeWorldstate.enforcedCollisionRefIds.push_back(refId);
}

void WorldstateFunctions::AddCellToReset(const char *cellDescription) noexcept
{
    ESM::Cell cell = Utils::getCellFromDescription(cellDescription);
    writeWorldstate.cellsToReset.push_back(cell);
}

void WorldstateFunctions::ClearEnforcedCollisionRefIds() noexcept
{
    writeWorldstate.enforcedCollisionRefIds.clear();
}

void WorldstateFunctions::ClearCellsToReset() noexcept
{
    writeWorldstate.cellsToReset.clear();
}

void WorldstateFunctions::SaveMapTileImageFile(unsigned int index, const char *filePath) noexcept
{
    if (index >= readWorldstate->mapTiles.size())
        return;

    const std::vector<char>& imageData = readWorldstate->mapTiles.at(index).imageData;

    std::ofstream outputFile(filePath, std::ios::binary);
    std::ostream_iterator<char> outputIterator(outputFile);
    std::copy(imageData.begin(), imageData.end(), outputIterator);
}

void WorldstateFunctions::LoadMapTileImageFile(int cellX, int cellY, const char* filePath) noexcept
{
    mwmp::MapTile mapTile;
    mapTile.x = cellX;
    mapTile.y = cellY;

    std::ifstream inputFile(filePath, std::ios::binary);
    mapTile.imageData = std::vector<char>(std::istreambuf_iterator<char>(inputFile), std::istreambuf_iterator<char>());

    if (mapTile.imageData.size() > mwmp::maxImageDataSize)
    {
        LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, "Error loading image file for map tile: "
            "%s has a size of %i, which is over the maximum allowed of %i!",
            filePath, mapTile.imageData.size(), mwmp::maxImageDataSize);
    }
    else
    {
        writeWorldstate.mapTiles.push_back(mapTile);
    }
}

void WorldstateFunctions::SendWorldMap(unsigned short pid, bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    writeWorldstate.guid = player->guid;

    mwmp::WorldstatePacket *packet = mwmp::Networking::get().getWorldstatePacketController()->GetPacket(ID_WORLD_MAP);
    packet->setWorldstate(&writeWorldstate);

    if (!skipAttachedPlayer)
        packet->Send(false);
    if (sendToOtherPlayers)
        packet->Send(true);
}

void WorldstateFunctions::SendWorldTime(unsigned short pid, bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    writeWorldstate.guid = player->guid;

    mwmp::WorldstatePacket *packet = mwmp::Networking::get().getWorldstatePacketController()->GetPacket(ID_WORLD_TIME);
    packet->setWorldstate(&writeWorldstate);
    
    if (!skipAttachedPlayer)
        packet->Send(false);
    if (sendToOtherPlayers)
        packet->Send(true);
}

void WorldstateFunctions::SendWorldWeather(unsigned short pid, bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    writeWorldstate.guid = player->guid;

    mwmp::WorldstatePacket *packet = mwmp::Networking::get().getWorldstatePacketController()->GetPacket(ID_WORLD_WEATHER);
    packet->setWorldstate(&writeWorldstate);

    if (!skipAttachedPlayer)
        packet->Send(false);
    if (sendToOtherPlayers)
        packet->Send(true);
}

void WorldstateFunctions::SendWorldCollisionOverride(unsigned short pid, bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    writeWorldstate.guid = player->guid;

    mwmp::WorldstatePacket *packet = mwmp::Networking::get().getWorldstatePacketController()->GetPacket(ID_WORLD_COLLISION_OVERRIDE);
    packet->setWorldstate(&writeWorldstate);

    if (!skipAttachedPlayer)
        packet->Send(false);
    if (sendToOtherPlayers)
        packet->Send(true);
}

void WorldstateFunctions::SendWorldRegionAuthority(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    writeWorldstate.guid = player->guid;

    mwmp::WorldstatePacket *packet = mwmp::Networking::get().getWorldstatePacketController()->GetPacket(ID_WORLD_REGION_AUTHORITY);
    packet->setWorldstate(&writeWorldstate);

    packet->Send(false);

    // This packet should always be sent to all other players
    packet->Send(true);
}

void WorldstateFunctions::SendCellReset(unsigned short pid, bool sendToOtherPlayers) noexcept
{
    mwmp::WorldstatePacket *packet = mwmp::Networking::get().getWorldstatePacketController()->GetPacket(ID_CELL_RESET);

    Player *player;
    GET_PLAYER(pid, player, );

    writeWorldstate.guid = player->guid;

    packet->setWorldstate(&writeWorldstate);

    packet->Send(sendToOtherPlayers);

    if (sendToOtherPlayers)
    {
        packet->Send(false);
    }

    CellController * cellController = CellController::get();

    for (ESM::Cell cell : writeWorldstate.cellsToReset)
    {
        if (sendToOtherPlayers)
        {
            TPlayers * players = Players::getPlayers();
            for (TPlayers::iterator iter = players->begin(); iter != players->end(); iter++)
            {
                cellController->getCell(&cell)->removePlayer((*iter).second, true);
            }
        }
        else
            cellController->getCell(&cell)->removePlayer(Players::getPlayer(pid), true);
    }
}


// All methods below are deprecated versions of methods from above

void WorldstateFunctions::ReadLastWorldstate() noexcept
{
    ReadReceivedWorldstate();
}

void WorldstateFunctions::CopyLastWorldstateToStore() noexcept
{
    CopyReceivedWorldstateToStore();
}
