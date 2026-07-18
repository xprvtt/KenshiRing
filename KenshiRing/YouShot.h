#include "ConfigHookExtension.h"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define ADD_LOGIC_S(__NAME_EFFECT__, __FUNCT__, __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __VICTIM__, __HARPOON__, __ON_PURPOSE__, __HIT_TARGET__) \
if(HookExtension::fastRandom100() <= __CHANCE__ && HookExtension::compareStringForEffect(__NAME_EFFECT__, __NAME_COLOR__)) \
{ \
    KR_DEBUG_LOG_L9("TRIGGER: " + __AUTO_ITEM__->getName() + " NAME: " + __NAME_EFFECT__)\
    KR_DEBUG_LOG_L9("SELF CHARACTER:" + (__SELF__).myRace->data->name + " OTHER CHARACTER: " + (__VICTIM__).myRace->data->name)\
    KR_LOG_CHECKPOINT;\
    __FUNCT__(__AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __VICTIM__, __HARPOON__, __ON_PURPOSE__, __HIT_TARGET__); \
    KR_LOG_CHECKPOINT;\
    continue; \
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define MAIN_MACROS_AFTER_SHOT(__NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __VICTIM__, __HARPOON__, __ON_PURPOSE__, __HIT_TARGET__) \
    ADD_LOGIC_S("#SniperShot", SniperShot,             __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __VICTIM__, __HARPOON__, __ON_PURPOSE__, __HIT_TARGET__) \
    ADD_LOGIC_S("#DivineShot", DivineShot,             __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __VICTIM__, __HARPOON__, __ON_PURPOSE__, __HIT_TARGET__) \
    ADD_LOGIC_S("#CharmShot", CharmShot,               __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __VICTIM__, __HARPOON__, __ON_PURPOSE__, __HIT_TARGET__) \
    ADD_LOGIC_S("#ConversionShot", ConversionShot,     __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __VICTIM__, __HARPOON__, __ON_PURPOSE__, __HIT_TARGET__) \
    ADD_LOGIC_S("#LifeStealingShot", LifeStealingShot, __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __VICTIM__, __HARPOON__, __ON_PURPOSE__, __HIT_TARGET__) \
    ADD_LOGIC_S("#Bonebreaker", Bonebreaker,           __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __VICTIM__, __HARPOON__, __ON_PURPOSE__, __HIT_TARGET__) \
    ADD_LOGIC_S("#SurgeonDream", SurgeonDream,         __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __VICTIM__, __HARPOON__, __ON_PURPOSE__, __HIT_TARGET__) \
    ADD_LOGIC_S("#PainfulShot", PainfulShot,           __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __VICTIM__, __HARPOON__, __ON_PURPOSE__, __HIT_TARGET__) \
    ADD_LOGIC_S("#BloodTollShot", BloodTollShot,       __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __VICTIM__, __HARPOON__, __ON_PURPOSE__, __HIT_TARGET__) \
    ADD_LOGIC_S("#DemonsShotToll", DemonsShotToll,     __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __VICTIM__, __HARPOON__, __ON_PURPOSE__, __HIT_TARGET__) \
    ADD_LOGIC_S("#ShotWanderingSoul", ShotWanderingSoul,__NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__,__AUTO_ITEM__,  __SELF__, __VICTIM__, __HARPOON__, __ON_PURPOSE__, __HIT_TARGET__) \
    ADD_LOGIC_S("#KhorneWanderingSoulShot", KhorneWanderingSoulShot, __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __VICTIM__, __HARPOON__, __ON_PURPOSE__, __HIT_TARGET__) \
    ADD_LOGIC_S("#AnnihilatingShot", AnnihilatingShot, __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __VICTIM__, __HARPOON__, __ON_PURPOSE__, __HIT_TARGET__) \

//may be useless
// __HARPOON__ - already used
// __ON_PURPOSE__ - already used
// __HIT_TARGET__ - result shot

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

inline void SniperShot(const float modificatorEffect, Item * itemThatCaused, Character& victim, Character& attacker, Harpoon& poon, bool& onPurpose, const bool isHitTarget)
{
    if (isHitTarget && onPurpose)
    {
        auto& anatomy = victim.medical.anatomy;

        MedicalSystem::HealthPartStatus* selected = nullptr;
        
        for (uint32_t i = 0; i < anatomy.size(); i++)
        {
            if (SuppKR::fastRandom(i) == 0)
            {
                selected = anatomy[i];
            }
        }
        if (selected)
        {
            selected->flesh -= selected->_maxHealth * modificatorEffect;
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

inline void DivineShot(const float modificatorEffect, Item* itemThatCaused, Character& victim, Character& attacker, Harpoon& poon, bool& onPurpose, const bool isHitTarget)
{
    if (isHitTarget && onPurpose)
    {
        auto& anatomy = victim.medical.anatomy;
        for (uint32_t i = 0; i < anatomy.size(); i++)
        {
            anatomy[i]->fleshStun += anatomy[i]->_maxHealth * modificatorEffect;
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

inline void CharmShot(const float modificatorEffect, Item* itemThatCaused, Character& victim, Character& attacker, Harpoon& poon, bool& onPurpose, const bool isHitTarget)
{
    if (isHitTarget && onPurpose)
    {
        victim.separateIntoMyOwnSquad(false);
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

inline void ConversionShot(const float modificatorEffect, Item* itemThatCaused, Character& victim, Character& attacker, Harpoon& poon, bool& onPurpose, const bool isHitTarget)
{
    if (isHitTarget && onPurpose)
    {
        victim.separateIntoMyOwnSquad(true);
        victim.setFaction(attacker.getFaction(), attacker.getPlatoon());
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

inline void LifeStealingShot(const float modificatorEffect, Item* itemThatCaused, Character& victim, Character& attacker, Harpoon& poon, bool& onPurpose, const bool isHitTarget)
{
    if (isHitTarget && onPurpose)
    {
        auto& anatomy = attacker.medical.anatomy;

        MedicalSystem::HealthPartStatus* selected = nullptr;

        for (uint32_t i = 0; i < anatomy.size(); i++)
        {
            auto* limb = anatomy[i];
            if (limb->flesh < limb->_maxHealth)
            {
                if (SuppKR::fastRandom(i) == 0)
                {
                    selected = limb;
                }
            }
        }
        if (selected)
        {
            selected->flesh += 50.f * modificatorEffect;
            if (selected->flesh > selected->_maxHealth)
            {
                selected->flesh = selected->_maxHealth;
            }
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

inline void Bonebreaker(const float modificatorEffect, Item* itemThatCaused, Character& victim, Character& attacker, Harpoon& poon, bool& onPurpose, const bool isHitTarget)
{
    if (isHitTarget && onPurpose)
    {
        victim.medical.amputate(HookExtension::amputateList[SuppKR::fastRandom(HookExtension::sizeAmputateList)], true, Ogre::Vector3(1.f, 1.f, 1.f));
        if (modificatorEffect >= 1.f)
        {
            victim.medical.amputate(HookExtension::amputateList[SuppKR::fastRandom(HookExtension::sizeAmputateList)], true, Ogre::Vector3(1.f, 1.f, 1.f));
            if (modificatorEffect >= 1.5f)
            {
                victim.medical.amputate(HookExtension::amputateList[SuppKR::fastRandom(HookExtension::sizeAmputateList)], true, Ogre::Vector3(1.f, 1.f, 1.f));
                if (modificatorEffect >= 2.f)
                {
                    victim.medical.amputate(HookExtension::amputateList[SuppKR::fastRandom(HookExtension::sizeAmputateList)], true, Ogre::Vector3(1.f, 1.f, 1.f));
                }
            }
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

inline void SurgeonDream(const float modificatorEffect, Item* itemThatCaused, Character& victim, Character& attacker, Harpoon& poon, bool& onPurpose, const bool isHitTarget)
{
    if (isHitTarget && onPurpose)
    {
        victim.medical.amputate(RobotLimbs::Limb::LEFT_ARM, true, Ogre::Vector3(1.f, 1.f, 1.f));
        victim.medical.amputate(RobotLimbs::Limb::LEFT_LEG, true, Ogre::Vector3(1.f, 1.f, 1.f));
        victim.medical.amputate(RobotLimbs::Limb::RIGHT_ARM, true, Ogre::Vector3(1.f, 1.f, 1.f));
        victim.medical.amputate(RobotLimbs::Limb::RIGHT_LEG, true, Ogre::Vector3(1.f, 1.f, 1.f));
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

inline void AnnihilatingShot(const float modificatorEffect, Item* itemThatCaused, Character& victim, Character& attacker, Harpoon& poon, bool& onPurpose, const bool isHitTarget)
{
    if (isHitTarget && onPurpose)
    {
        victim.medical.amputate(RobotLimbs::Limb::LEFT_ARM, true, Ogre::Vector3(1.f, 1.f, 1.f));
        victim.medical.amputate(RobotLimbs::Limb::LEFT_LEG, true, Ogre::Vector3(1.f, 1.f, 1.f));
        victim.medical.amputate(RobotLimbs::Limb::RIGHT_ARM, true, Ogre::Vector3(1.f, 1.f, 1.f));
        victim.medical.amputate(RobotLimbs::Limb::RIGHT_LEG, true, Ogre::Vector3(1.f, 1.f, 1.f));
        victim.inventory->clearAll(false, false);
        
        auto& anatomy = victim.medical.anatomy;

        for (uint32_t i = 0; i < anatomy.size(); i++)
        {
            anatomy[i]->flesh -= 500.f * (std::max(1.f - modificatorEffect, 0.f));
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// дебафы для нашего стрелка (или полудебаффы, смотря как посмотреть)

inline void PainfulShot(const float modificatorEffect, Item* itemThatCaused, Character& victim, Character& attacker, Harpoon& poon, bool& onPurpose, const bool isHitTarget)
{
    if (isHitTarget && onPurpose)
    {
        auto& anatomy = attacker.medical.anatomy;

        for (uint32_t i = 0; i < anatomy.size(); i++)
        {
            anatomy[i]->flesh -= 10.f * modificatorEffect;
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

inline void DemonsShotToll(const float modificatorEffect, Item* itemThatCaused, Character& victim, Character& attacker, Harpoon& poon, bool& onPurpose, const bool isHitTarget)
{
    if (isHitTarget && onPurpose)
    {
        attacker.medical.amputate(RobotLimbs::Limb::LEFT_ARM, true, Ogre::Vector3(1.f, 1.f, 1.f));
        attacker.medical.amputate(RobotLimbs::Limb::LEFT_LEG, true, Ogre::Vector3(1.f, 1.f, 1.f));
        attacker.medical.amputate(RobotLimbs::Limb::RIGHT_ARM, true, Ogre::Vector3(1.f, 1.f, 1.f));
        attacker.medical.amputate(RobotLimbs::Limb::RIGHT_LEG, true, Ogre::Vector3(1.f, 1.f, 1.f));
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

inline void BloodTollShot(const float modificatorEffect, Item* itemThatCaused, Character& victim, Character& attacker, Harpoon& poon, bool& onPurpose, const bool isHitTarget)
{
    if (isHitTarget && onPurpose)
    {
        victim.medical.amputate(HookExtension::amputateList[SuppKR::fastRandom(HookExtension::sizeAmputateList)], true, Ogre::Vector3(1.f, 1.f, 1.f));
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

inline void ShotWanderingSoul(const float modificatorEffect, Item* itemThatCaused, Character& victim, Character& attacker, Harpoon& poon, bool& onPurpose, const bool isHitTarget)
{
    if (isHitTarget && onPurpose)
    {
        const RaceData* vRaca = victim.getRace();
        const RaceData* aRaca = attacker.getRace();

        if (!vRaca && !aRaca) // костыль, нужен более прочный костыль
        {
            return;
        }
        if (vRaca->raceGroup != aRaca->raceGroup)
        {
            return;
        }

        victim.separateIntoMyOwnSquad(true);
        victim.setFaction(attacker.getFaction(), attacker.getPlatoon());

        auto& anatomy = attacker.medical.anatomy;
        for (uint32_t i = 0; i < anatomy.size(); i++)
        {
            anatomy[i]->applyDamage(Damages(100.f, 100.f, 100.f, 100.f, 100.f));
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

inline void KhorneWanderingSoulShot(const float modificatorEffect, Item* itemThatCaused, Character& victim, Character& attacker, Harpoon& poon, bool& onPurpose, const bool isHitTarget)
{
    if (isHitTarget && onPurpose)
    {
        victim.separateIntoMyOwnSquad(true);
        victim.setFaction(attacker.getFaction(), attacker.getPlatoon());

        auto& an1 = attacker.medical.anatomy;
        for (uint32_t i = 0; i < an1.size(); i++)
        {
            an1[i]->applyDamage(Damages(200.f, 200.f, 200.f, 200.f, 200.f));
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
