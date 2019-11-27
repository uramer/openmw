#ifndef OPENMW_WORLDSTATE_HPP
#define OPENMW_WORLDSTATE_HPP

#include <components/openmw-mp/Base/BaseWorldstate.hpp>

namespace mwmp
{
    class Networking;
    class Worldstate : public BaseWorldstate
    {
    public:

        Worldstate();
        virtual ~Worldstate();

        void addRecords();

        bool containsExploredMapTile(int cellX, int cellY);
        void markExploredMapTile(int cellX, int cellY);

        void setKills();
        void setMapExplored();
        void setWeather();

        void sendMapExplored(int cellX, int cellY, const std::vector<char>& imageData);
        void sendWeather(std::string region, int currentWeather, int nextWeather, int queuedWeather, float transitionFactor);

        void sendEnchantmentRecord(const ESM::Enchantment* enchantment);
        void sendPotionRecord(const ESM::Potion* potion);
        void sendSpellRecord(const ESM::Spell* spell);

        void sendArmorRecord(const ESM::Armor* armor, std::string baseRefId = "");
        void sendBookRecord(const ESM::Book* book, std::string baseRefId = "");
        void sendClothingRecord(const ESM::Clothing* clothing, std::string baseRefId = "");
        void sendWeaponRecord(const ESM::Weapon* weapon, std::string baseRefId = "");

    private:

        std::vector<MapTile> exploredMapTiles;

        Networking *getNetworking();

    };
}

#endif //OPENMW_WORLDSTATE_HPP
