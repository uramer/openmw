#ifndef OPENMW_BASESTRUCTS_HPP
#define OPENMW_BASESTRUCTS_HPP

#include <string>

#include <components/esm/loadcell.hpp>
#include <components/esm/statstate.hpp>

#include <RakNetTypes.h>

namespace mwmp
{
    enum PACKET_ORIGIN
    {
        CLIENT_GAMEPLAY = 0,
        CLIENT_CONSOLE = 1,
        CLIENT_DIALOGUE = 2,
        CLIENT_SCRIPT_LOCAL = 3,
        CLIENT_SCRIPT_GLOBAL = 4,
        SERVER_SCRIPT = 5
    };

    struct Time
    {
        float hour;
        int day;
        int month;
        int year;

        int daysPassed;
        float timeScale;
    };

    struct Item
    {
        std::string refId;
        int count;
        int charge;
        float enchantmentCharge;
        std::string soul;

        inline bool operator==(const Item& rhs)
        {
            return refId == rhs.refId && count == rhs.count && charge == rhs.charge &&
                enchantmentCharge == rhs.enchantmentCharge && soul == rhs.soul;
        }
    };
    
    struct Target
    {
        bool isPlayer;

        std::string refId;
        unsigned int refNum;
        unsigned int mpNum;

        std::string name; // Remove this once the server can get names corresponding to different refIds

        RakNet::RakNetGUID guid;
    };

    class Attack
    {
    public:

        Target target;

        enum TYPE
        {
            MELEE = 0,
            RANGED
        };

        char type;
        std::string attackAnimation;

        std::string rangedWeaponId;
        std::string rangedAmmoId;

        ESM::Position hitPosition;

        float damage;
        float attackStrength;

        bool isHit = false;
        bool success = false;
        bool block = false;
        
        bool pressed = false;
        bool instant = false;
        bool knockdown = false;
        bool applyWeaponEnchantment = false;
        bool applyAmmoEnchantment = false;

        bool shouldSend = false;
    };

    class Cast
    {
    public:

        Target target;

        char type; // 0 - regular magic, 1 - item magic
        enum TYPE
        {
            REGULAR = 0,
            ITEM
        };

        std::string spellId; // id of spell (e.g. "fireball")
        std::string itemId;

        ESM::Position hitPosition;

        bool isHit;
        bool success;
        bool pressed;
        bool instant;

        bool shouldSend;
    };

    struct Animation
    {
        std::string groupname;
        int mode;
        int count;
        bool persist;
    };

    struct SimpleCreatureStats
    {
        ESM::StatState<float> mDynamic[3];
        bool mDead;
        bool mDeathAnimationFinished;
    };
}

#endif //OPENMW_BASESTRUCTS_HPP
