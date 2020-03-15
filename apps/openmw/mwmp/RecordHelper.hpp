#ifndef OPENMW_RECORDHELPER_HPP
#define OPENMW_RECORDHELPER_HPP

#include <components/openmw-mp/Base/BaseWorldstate.hpp>

#include "../mwbase/environment.hpp"

namespace RecordHelper
{
    void overrideRecord(const mwmp::ActivatorRecord& record);
    void overrideRecord(const mwmp::ApparatusRecord& record);
    void overrideRecord(const mwmp::ArmorRecord& record);
    void overrideRecord(const mwmp::BodyPartRecord& record);
    void overrideRecord(const mwmp::BookRecord& record);
    void overrideRecord(const mwmp::CellRecord& record);
    void overrideRecord(const mwmp::ClothingRecord& record);
    void overrideRecord(const mwmp::ContainerRecord& record);
    void overrideRecord(const mwmp::CreatureRecord& record);
    void overrideRecord(const mwmp::DoorRecord& record);
    void overrideRecord(const mwmp::EnchantmentRecord& record);
    void overrideRecord(const mwmp::IngredientRecord& record);
    void overrideRecord(const mwmp::LightRecord& record);
    void overrideRecord(const mwmp::LockpickRecord& record);
    void overrideRecord(const mwmp::MiscellaneousRecord& record);
    void overrideRecord(const mwmp::NpcRecord& record);
    void overrideRecord(const mwmp::PotionRecord& record);
    void overrideRecord(const mwmp::ProbeRecord& record);
    void overrideRecord(const mwmp::RepairRecord& record);
    void overrideRecord(const mwmp::ScriptRecord& record);
    void overrideRecord(const mwmp::SpellRecord& record);
    void overrideRecord(const mwmp::StaticRecord& record);
    void overrideRecord(const mwmp::WeaponRecord& record);
    void overrideRecord(const mwmp::SoundRecord& record);

    template<class RecordType>
    void overrideRecord(const RecordType &record)
    {
        MWBase::World *world = MWBase::Environment::get().getWorld();

        world->getModifiableStore().overrideRecord(record);
    }

    template<class RecordType>
    const RecordType *createRecord(const RecordType &record)
    {
        MWBase::World *world = MWBase::Environment::get().getWorld();

        return world->createRecord(record);
    }

    template<class RecordType>
    bool doesRecordIdExist(const std::string& id)
    {
        MWBase::World *world = MWBase::Environment::get().getWorld();

        return world->getStore().get<RecordType>().search(id);
    }
}


#endif //OPENMW_RECORDHELPER_HPP
