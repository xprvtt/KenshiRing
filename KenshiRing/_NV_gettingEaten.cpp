#include "HookKR.h"

bool (*Character_NV_gettingEaten_orig)(Character* thsptr, float amount, Character* eater) = nullptr;

bool Character_NV_gettingEaten_hook(Character* thsptr, float amount, Character* eater)
{
	HookListener::EatenContext newMeleeContent;
	newMeleeContent.self = thsptr;
	newMeleeContent.eater = eater;
	newMeleeContent.amount = &amount;

	for (auto& currentFunction : beforeOriginal_Character_NV_gettingEaten)
	{
		currentFunction(newMeleeContent);
	}

	auto returnVal = Character_NV_gettingEaten_orig(thsptr, amount, eater);

	for (auto& currentFunction : afterOriginal_Character_NV_gettingEaten)
	{
		currentFunction(newMeleeContent);
	}

	return returnVal;
}
