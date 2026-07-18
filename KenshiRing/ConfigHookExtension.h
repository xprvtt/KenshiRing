
#pragma once
#include "CoreKenshiRing.h"

//-------------------------------------------------------------------------------------------------------

namespace HookExtension
{
    inline bool compareStringForEffect(const std::string& expected, const std::string& value)
    {
        KR_DEBUG_LOG_L10(value + " -> attainable effect: " + expected);
        if (value.size() <= 13 || value[0] != '#') // # - обозначаем наши эффекты, после самого названия есть 13 символов по вашему усмотрению как вы будете их использовать
        {
            KR_DEBUG_LOG_L10("\t|_ not approved");
            return false;
        }
        const size_t compareSize = value.size() - 13;
        if (expected.size() != compareSize)
        {
            KR_DEBUG_LOG_L10("\t|_ not approved");
            return false;
        }
        KR_DEBUG_CODE_L10
        (
            auto res = std::memcmp(expected.data(), value.data(), compareSize) == 0;
            if (res)
            {
                KR_DEBUG_LOG_L10("\t|_  approved");
            }
            else
            {
                KR_DEBUG_LOG_L10("\t|_ not approved");
            }
            return res;
        )
        return std::memcmp(expected.data(), value.data(), compareSize) == 0;
    }

    inline int fastRandom100()
    {
        static uint32_t s2 = static_cast<uint32_t>(time(nullptr));
        s2 ^= s2 << 13;
        s2 ^= s2 >> 17;
        s2 ^= s2 << 5;
        return s2 % 101;
    }


    static const RobotLimbs::Limb amputateList[] =
    {
        RobotLimbs::LEFT_ARM,
        RobotLimbs::RIGHT_ARM,
        RobotLimbs::LEFT_LEG,
        RobotLimbs::RIGHT_LEG
    };

    static const int sizeAmputateList = sizeof(amputateList) / sizeof(amputateList[0]);
}

//-------------------------------------------------------------------------------------------------------
