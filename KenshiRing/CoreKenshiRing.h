#pragma once

#include <vector>
#include <map>
#include <unordered_map>
#include <Windows.h>
#include <sstream>
#include <string>

#pragma warning(disable : 4091)
#pragma warning(disable : 4482)

#include <core/Functions.h>
#include <Debug.h>

#include <kenshi/Character.h>
#include <kenshi/Enums.h>
#include <kenshi/GameData.h>
#include <kenshi/Inventory.h>
#include <kenshi/RootObjectFactory.h>
#include <kenshi/util/lektor.h>
#include <kenshi/Item.h>
#include <kenshi/Damages.h>
#include <kenshi/RaceData.h>
#include <kenshi/Platoon.h>
#include <kenshi/combat/CombatTechniqueData.h>
#include <mygui/common/baselayout/BaseLayout.h>

#include "CoreMacrosHelper.h"

namespace SuppKR //Support functions for Kenshi Ring Mod
{
    template<typename T>
    std::string toStringV100(T v)
    {
        std::ostringstream oss;
        oss << v;
        return oss.str();
    }

    inline int fastRandom(int max)
    {
        static uint32_t s = static_cast<uint32_t>(time(nullptr));

        s ^= s << 13;
        s ^= s >> 17;
        s ^= s << 5;

        return s % (max + 1);
    }

    template<typename T>
    void lektorPushBack(lektor<T>& lek, const T& val)
    {
        if (lek.count == lek.maxSize)
        {
            uint32_t newSize = lek.maxSize ? lek.maxSize * 2 : 20;
            T* ptr = (T*)realloc(lek.stuff, sizeof(T) * newSize);
            
            if (!ptr)
            {
                throw std::bad_alloc();
            }
            
            lek.stuff = ptr;
            lek.maxSize = newSize;
        }
        lek.stuff[lek.count++] = val;
    }
}

// инициализация конфигурации мода
void setup();