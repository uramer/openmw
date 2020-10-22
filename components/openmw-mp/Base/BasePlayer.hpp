#ifndef OPENMW_BASEPLAYER_HPP
#define OPENMW_BASEPLAYER_HPP

#include <components/esm/loadcell.hpp>
#include <components/esm/loadcrea.hpp>
#include <components/esm/loadnpc.hpp>
#include <components/esm/npcstats.hpp>
#include <components/esm/creaturestats.hpp>
#include <components/esm/loadclas.hpp>
#include <components/esm/loadspel.hpp>

#include <components/openmw-mp/Base/BaseStructs.hpp>

#include <RakNetTypes.h>

namespace mwmp
{
    struct CurrentContainer
    {
        std::string refId;
        unsigned int refNum;
        unsigned int mpNum;
        bool loot;
    };

    struct JournalItem
    {
        std::string quest;
        int index;
        enum JOURNAL_ITEM_TYPE
        {
            ENTRY = 0,
            INDEX = 1
        };

        std::string actorRefId;

        bool hasTimestamp;
        mwmp::Time timestamp;

        int type; // 0 - An entire entry, 1 - An index
    };

    struct Faction
    {
        std::string factionId;
        int rank;
        int reputation;
        bool isExpelled;
    };

    struct Topic
    {
        std::string topicId;
    };

    struct Kill
    {
        std::string refId;
        int number;
    };

    struct Book
    {
        std::string bookId;
    };

    struct QuickKey
    {
        std::string itemId;

        enum QUICKKEY_TYPE
        {   
            ITEM = 0,
            MAGIC = 1,
            ITEM_MAGIC = 2,
            UNASSIGNED = 3
        };

        unsigned short slot;
        int type;
    };

    struct CellState
    {
        ESM::Cell cell;

        enum CELL_STATE_ACTION
        {
            LOAD = 0,
            UNLOAD = 1
        };

        int type; // 0 - Cell load, 1 - Cell unload
    };

    struct JournalChanges
    {
        std::vector<JournalItem> journalItems;
        unsigned int count;
    };

    struct FactionChanges
    {
        std::vector<Faction> factions;
        unsigned int count;

        enum FACTION_ACTION
        {
            RANK = 0,
            EXPULSION = 1,
            REPUTATION = 2
        };

        int action; // 0 - Rank, 1 - Expulsion state, 2 - Both
    };

    struct TopicChanges
    {
        std::vector<Topic> topics;
        unsigned int count;
    };

    struct KillChanges
    {
        std::vector<Kill> kills;
        unsigned int count;
    };

    struct BookChanges
    {
        std::vector<Book> books;
        unsigned int count;
    };

    struct InventoryChanges
    {
        std::vector<Item> items;
        unsigned int count;
        enum ACTION_TYPE
        {
            SET = 0,
            ADD,
            REMOVE
        };
        int action; // 0 - Clear and set in entirety, 1 - Add item, 2 - Remove item
    };

    struct SpellbookChanges
    {
        std::vector<ESM::Spell> spells;
        unsigned int count;
        enum ACTION_TYPE
        {
            SET = 0,
            ADD,
            REMOVE
        };
        int action; // 0 - Clear and set in entirety, 1 - Add spell, 2 - Remove spell
    };

    struct QuickKeyChanges
    {
        std::vector<QuickKey> quickKeys;
        unsigned int count;
    };

    struct CellStateChanges
    {
        std::vector<CellState> cellStates;
        unsigned int count;
    };

    enum RESURRECT_TYPE
    {
        REGULAR = 0,
        IMPERIAL_SHRINE,
        TRIBUNAL_TEMPLE
    };

    enum MISCELLANEOUS_CHANGE_TYPE
    {
        MARK_LOCATION = 0,
        SELECTED_SPELL
    };

    class BasePlayer
    {
    public:

        struct CharGenState
        {
            int currentStage, endStage;
            bool isFinished;
        };

        struct GUIMessageBox
        {
            int id;
            int type;
            enum GUI_TYPE
            {
                MessageBox = 0,
                CustomMessageBox,
                InputDialog,
                PasswordDialog,
                ListBox
            };
            std::string label;
            std::string note;
            std::string buttons;

            std::string data;
        };

        BasePlayer(RakNet::RakNetGUID guid) : guid(guid)
        {
            inventoryChanges.action = 0;
            inventoryChanges.count = 0;
            spellbookChanges.action = 0;
            spellbookChanges.count = 0;

            exchangeFullInfo = false;
            displayCreatureName = false;
            resetStats = false;
            enforcedLogLevel = -1;
        }

        BasePlayer()
        {

        }

        RakNet::RakNetGUID guid;
        std::string serverPassword;

        GUIMessageBox guiMessageBox;

        // Track only the indexes of the attributes that have been changed,
        // with the attribute values themselves being stored in creatureStats.mAttributes
        std::vector<uint8_t> attributeIndexChanges;

        // Track only the indexes of the skills that have been changed,
        // with the skill values themselves being stored in npcStats.mSkills
        std::vector<uint8_t> skillIndexChanges;

        // Track only the indexes of the dynamic states that have been changed,
        // with the dynamicStats themselves being stored in creatureStats.mDynamic
        std::vector<uint8_t> statsDynamicIndexChanges;

        // Track only the indexes of the equipment items that have been changed,
        // with the items themselves being stored in equipmentItems
        std::vector<int> equipmentIndexChanges;

        bool exchangeFullInfo;

        InventoryChanges inventoryChanges;
        SpellbookChanges spellbookChanges;
        QuickKeyChanges quickKeyChanges;
        JournalChanges journalChanges;
        FactionChanges factionChanges;
        TopicChanges topicChanges;
        KillChanges killChanges;
        BookChanges bookChanges;
        CellStateChanges cellStateChanges;

        ESM::ActiveSpells activeSpells;
        CurrentContainer currentContainer;

        int difficulty;
        int enforcedLogLevel;
        float physicsFramerate;
        bool consoleAllowed;
        bool bedRestAllowed;
        bool wildernessRestAllowed;
        bool waitAllowed;

        bool ignorePosPacket;
        bool pauseMovement;

        unsigned int movementFlags;
        char movementAnim;
        char drawState;
        bool isFlying;

        ESM::Position position;
        ESM::Position direction;
        ESM::Position previousCellPosition;
        ESM::Position momentum;
        ESM::Cell cell;
        ESM::NPC npc;
        ESM::NpcStats npcStats;
        ESM::Creature creature;
        ESM::CreatureStats creatureStats;
        ESM::Class charClass;
        Item equipmentItems[19];
        Attack attack;
        std::string birthsign;
        std::string chatMessage;
        CharGenState charGenState;

        std::string sound;
        Animation animation;

        bool resetStats;
        float scale;
        bool isWerewolf;

        bool displayCreatureName;
        std::string creatureRefId;

        bool isChangingRegion;

        Target killer;

        int jailDays;
        bool ignoreJailTeleportation;
        bool ignoreJailSkillIncreases;
        std::string jailProgressText;
        std::string jailEndText;

        unsigned int resurrectType;
        unsigned int miscellaneousChangeType;

        ESM::Cell markCell;
        ESM::Position markPosition;
        std::string selectedSpellId;

        mwmp::Item usedItem;
    };
}

#endif //OPENMW_BASEPLAYER_HPP
