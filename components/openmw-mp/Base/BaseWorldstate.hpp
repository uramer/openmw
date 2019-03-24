#ifndef OPENMW_BASEWORLDSTATE_HPP
#define OPENMW_BASEWORLDSTATE_HPP

#include <vector>

#include <components/esm/loadalch.hpp>
#include <components/esm/loadarmo.hpp>
#include <components/esm/loadbook.hpp>
#include <components/esm/loadclot.hpp>
#include <components/esm/loadcrea.hpp>
#include <components/esm/loadench.hpp>
#include <components/esm/loadmisc.hpp>
#include <components/esm/loadnpc.hpp>
#include <components/esm/loadspel.hpp>
#include <components/esm/loadweap.hpp>

#include <components/openmw-mp/Base/BaseStructs.hpp>

#include <RakNetTypes.h>

namespace mwmp
{
    enum RECORD_TYPE
    {
        ARMOR,
        BOOK,
        CLOTHING,
        CREATURE,
        ENCHANTMENT,
        MISCELLANEOUS,
        NPC,
        POTION,
        SPELL,
        WEAPON
    };

    // When using an existing record as a base, this struct tracks which changes
    // need to be made to it
    //
    // Note: These can't be replaced with checks for empty strings or numerical
    //       values of 0 because you want to be able to blank out strings or
    //       set values of 0 through overrides, i.e. if someone is in the
    //       Mages Guild faction, you want to be able to remove them from it
    //       by using a blank faction string as an override
    //
    //       There are, however, a few values that are not allowed to be blanked
    //       out in a record, such as races or classes for NPCs, and those
    //       should rely on checks for empty strings instead of having a
    //       boolean here
    struct BaseOverrides
    {
        bool hasSubtype = false;
        bool hasName = false;
        bool hasModel = false;
        bool hasIcon = false;
        bool hasScript = false;
        bool hasEnchantmentId = false;
        bool hasEnchantmentCharge = false;

        bool hasEffects = false;
        bool hasBodyParts = false;
        bool hasInventory = false;

        bool hasAutoCalc = false;
        bool hasCharge = false;
        bool hasCost = false;
        bool hasFlags = false;
        bool hasValue = false;
        bool hasWeight = false;

        bool hasArmorRating = false;
        bool hasHealth = false;

        bool hasDamageChop = false;
        bool hasDamageSlash = false;
        bool hasDamageThrust = false;
        bool hasReach = false;
        bool hasSpeed = false;

        bool hasKeyState = false;
        bool hasScrollState = false;
        bool hasSkillId = false;
        bool hasText = false;

        bool hasHair = false;
        bool hasHead = false;
        bool hasGender = false;
        bool hasFaction = false;

        bool hasLevel = false;
        bool hasMagicka = false;
        bool hasFatigue = false;
        bool hasAiFight = false;
    };

    struct ArmorRecord
    {
        ESM::Armor data;
        std::string baseId;
        BaseOverrides baseOverrides;
    };

    struct BookRecord
    {
        ESM::Book data;
        std::string baseId;
        BaseOverrides baseOverrides;
    };

    struct ClothingRecord
    {
        ESM::Clothing data;
        std::string baseId;
        BaseOverrides baseOverrides;
    };

    struct CreatureRecord
    {
        ESM::Creature data;
        std::string baseId;
        std::string inventoryBaseId;
        std::vector<mwmp::Item> inventory;
        BaseOverrides baseOverrides;
    };

    struct EnchantmentRecord
    {
        ESM::Enchantment data;
        std::string baseId;
        BaseOverrides baseOverrides;
    };

    struct MiscellaneousRecord
    {
        ESM::Miscellaneous data;
        std::string baseId;
        BaseOverrides baseOverrides;
    };

    struct NpcRecord
    {
        ESM::NPC data;
        std::string baseId;
        std::string inventoryBaseId;
        std::vector<mwmp::Item> inventory;
        BaseOverrides baseOverrides;
    };

    struct PotionRecord
    {
        ESM::Potion data;
        std::string baseId;
        BaseOverrides baseOverrides;
    };

    struct SpellRecord
    {
        ESM::Spell data;
        std::string baseId;
        BaseOverrides baseOverrides;
    };

    struct WeaponRecord
    {
        ESM::Weapon data;
        std::string baseId;
        BaseOverrides baseOverrides;
    };

    static const int maxImageDataSize = 1800;

    struct MapTile
    {
        int x;
        int y;
        std::vector<char> imageData;
    };

    struct Weather
    {
        std::string region;
        unsigned int currentWeather;
        unsigned int nextWeather;
        unsigned int queuedWeather;
        float transitionFactor;
    };

    class BaseWorldstate
    {
    public:

        BaseWorldstate()
        {
            time.year = -1;
            time.month = -1;
            time.day = -1;
            time.hour = -1;

            time.daysPassed = -1;
            time.timeScale = -1;
        }

        RakNet::RakNetGUID guid;

        mwmp::Time time;

        bool hasPlayerCollision;
        bool hasActorCollision;
        bool hasPlacedObjectCollision;
        bool useActorCollisionForPlacedObjects;

        std::string authorityRegion;

        std::vector<std::string> enforcedCollisionRefIds;

        std::vector<MapTile> mapTiles;

        bool forceWeather;
        Weather weather;

        unsigned short recordsType;
        unsigned int recordsCount;

        std::vector<ArmorRecord> armorRecords;
        std::vector<BookRecord> bookRecords;
        std::vector<ClothingRecord> clothingRecords;
        std::vector<CreatureRecord> creatureRecords;
        std::vector<EnchantmentRecord> enchantmentRecords;
        std::vector<MiscellaneousRecord> miscellaneousRecords;
        std::vector<NpcRecord> npcRecords;
        std::vector<PotionRecord> potionRecords;
        std::vector<SpellRecord> spellRecords;
        std::vector<WeaponRecord> weaponRecords;

        std::vector<ESM::Cell> cellsToReset;

        bool isValid;
    };
}

#endif //OPENMW_BASEWORLDSTATE_HPP
