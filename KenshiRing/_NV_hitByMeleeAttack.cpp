#include "HookKR.h"

HitMaterialType(*Character_NV_hitByMeleeAttack_orig)(Character* thsptr, CutDirection dir, Damages& damage, Character* who, CombatTechniqueData* attack, int comboID) = nullptr;

HitMaterialType Character_NV_hitByMeleeAttack_hook(Character* thsptr, CutDirection dir, Damages& damage, Character* who, CombatTechniqueData* attack, int comboID)
{
	HookListener::MeleeHitContext newMeleeContent;
	newMeleeContent.attacker = who;
	newMeleeContent.comboID = &comboID;
	newMeleeContent.damage = &damage;
	newMeleeContent.self = thsptr;
	newMeleeContent.сombatTechniqueData = attack;
	newMeleeContent.сutDirection = &dir;

	for (auto& currentFunction : beforeOriginal_Character_NV_hitByMeleeAttach)
	{
		currentFunction(newMeleeContent);
	}

	auto returnVal = Character_NV_hitByMeleeAttack_orig(thsptr, dir, damage, who, attack, comboID);

	for (auto& currentFunction : afterOriginal_Character_NV_hitByMeleeAttach)
	{
		currentFunction(newMeleeContent);
	}

	return returnVal;
}
