
/*
*
* KRHookExtension выступает в роли легкого (нет) добавления дополнительной логики в хуки в зависимости от эффекта добавленного в предмет
* Вы можете бесконечно добавлять свои функции до выполнения оригинального хука или после его выполнения
* дополнительная логика будет выпоняться последовательно относительно своего добавления в основной макрос
* 
* How do I use it ?
* 
* //----------------------------------------//
* // общий пример добавления эффекта в игру //
* //----------------------------------------//
*
* 1. создайсте свою функцию с параметрами "inline void yourNameFunction(Param& p1, Param& p2, Param& p3, Param& p4, ... )" В Setup -> CustomEffects -> "Category" -> name.h
* name.h разделены по смыслу между собой в зависимости от логики воспроизведения (ДО, ПОСЛЕ)
* 
* 2. измените входящие данные, которые вы выхотите (Param& p1 ... )
* 
* 3. придумайте название вашему эффекту (функции), с начинающегося символа # например "#yourNameEffectFoo"
* 
* 4. добавьте свою функцию через макрос ADD_LOGIC_"NAME"("#yourNameEffectFoo", yourNameFunction), в основной макрос MAIN_MACROS_"NAME"(__PARAM_P1_, __PARAM_P2_, __PARAM_P3_, __PARAM_P4_, ... )
*    пример :
*
*       #define MAIN_MACROS(__PARAM_P1_, __PARAM_P2_, __PARAM_P2_, __PARAM_P3_, __PARAM_P4_, ... ) \
*                  ADD_LOGIC_"NAME"() \
*                  ADD_LOGIC_"NAME"() \
*       here    -> ADD_LOGIC_"NAME"("#yourNameEffectFoo", yourNameFunction, __PARAM_P1__, ...) \
*                  ADD_LOGIC_"NAME"() \
*                  ADD_LOGIC_"NAME"() \
*       or here -> ADD_LOGIC_"NAME"("#yourNameEffectFoo", yourNameFunction, __PARAM_P1__, ...))
*
* 5. учитывайте символ \ после ADD_LOGIC_"NAME"(), он обеспечивает перенос строки это для удобства чтения
* 
* 6. оптимизация. Eсли вы добавляете "часто вызываемую" функцию(effect) добавьте ее выше остальных, если же она реже всех то ниже
*    пример: "#effect_1" наложен на огромное колличество предметов, для оптимизации использован if( foo(); continue;) подход вместо vector<pair<string, function>>
*    изходя из этого чем выше находится частоиспользуемая функция тем меньше затрат на прохождение цепочки if-if-if-if-if ....
* 
* 7. после выполнения этих этапов в игре появится эффект с вашей логикой и при определенных условиях они будут срабатывать
*    пример расписан в Setup -> CustomEffects -> Attack -> LogicBeforeTakingHit.h
* 
* 8 Описание принципа работы
* 8.1 игра проверяет наличие предметов в секциях инвентаря -> не в пространстве ВНУТРИ рюкзака, не в инвентаре персонажа "main" , и не в новом слоте Pocket "KR_pocket"
* 8.2 далее игра проверяет наличие параметра Color у предмета, это наиболее удачный и быстрый при выполнении вариант, чем парсинг строк с описанием
* 
* //--------------------------------------------//
* // Общий пример добавления эффекта к предмету //
* //--------------------------------------------//
*
* 1. запустите FSC 
* 
* 2. создайте предмет Item который МОЖНО ЭКИПИРОВАТЬ И У КОТОРОГО МОЖНО ДОБАВИТЬ ДОПОЛНИТЕЛЬНЫЙ ПАРАМЕТР "color"
*    прикреления рассмотренные ниже вызывают вылет игры
*     2.2 предметы armour с прикреплением: 
*         ATTACH_NONE  
*         ATTACH_LEFT_ARM
*         ATTACH_RIGHT_ARM
*         ATTACH_LEFT_LEG
*         ATTACH_RIGHT_LEG 
*         ATTACH_WEAPON
*     2.3 предметы Bags с прикреплением: (?) 
* 
* 3. добавьте дополнительный параметр color в правой части окна настройки предмета
* 
* 4. создайте новый color с именем эффекта выбранным раньше, в начало добавьте символ #, получится так "#yourNameEffectFoo", так же добавтье в конец к нему 8 любых символа, например "-050-100" 
*    для упрощения ориентировке между одинаковыми названиями, 
*    итоговое значение что то вроде "#yourNameEffectFoo-050-100" или "#yourNameEffectFoo12345678" или "#yourNameEffectFoo----====" по вашему желанию
* 
* 5. так как игра будет сравнивать "#yourNameEffectFoo" добавленный программно, и имя color у "#yourNameEffectFoo-050-100" без последних 8 символов, 
*    это сделано для того чтобы удобно ориентироваться между одинаковыми эффектами но с разным шансом срабатывания и модификатором
*
* 6. измените ПЕРВОЕ значение у параметра color1 (0-100), это КРАСНЫЙ цвет, у нашего "#yourNameEffectFoo-050-100" - например на 50 (так как мы ранее обозначили его в "-050" для удобства)
*    это шанс срабатывания вашего эффекта у предмета
*    вы так же можете выбрать любое значение шанса в диапазоне от 0 до 100 (или до 255, но всё что выше 100, будет считаться, что шанс срабатывания 100%)
* 
* 7. измените ВТОРОЕ значение у параметра color1 (0-255), это ЗЕЛЕНЫЙ цвет, у нашего "#yourNameEffectFoo-050-100" - например на 100 (так как мы ранее обозначили его в "-100" для удобства)
*    это модификатор силы вашего эффекта, должен передаваться в вашу функцию, в виде "float modificator" от 0.f до 2.55f соответственно
*    вы можете использовать его по желанию, чтобы так же добавить разнообразия вашему эффекту, чтобы его ослабить или усилить
* 
*/

//-------------------------------------------------------------------------------------------------------

#pragma once

#include "YouAttacking.h"
#include "YouTakingHit.h"

#include "AnimalEatingYou.h"

#include "Doctoring.h"
#include "RecievingHelp.h"
#include "Rigging.h"

#include "EnemyAttackTarget.h"

#include "GetShot.h"
#include "YouShot.h"

//-------------------------------------------------------------------------------------------------------

#define FOR_EACH_COLOR(__CHARACTER_PTR__, __MAIN_MACROS_FOR_METHOD__)\
KR_DEBUG_LOG_L9("FOR_EACH_COLOR");\
for (auto it = __CHARACTER_PTR__->inventory->sections.begin(); it != __CHARACTER_PTR__->inventory->sections.end(); ++it)\
{\
    KR_DEBUG_LOG_L9("\t" + it->first);\
    if (it->second->limitedSlot != AttachSlot::ATTACH_NONE)\
    {\
        auto& sec = it->second->items;\
        for (auto it1 = sec.begin(); it1 != sec.end(); it1++)\
        {\
            Item& item = *it1->item;\
            GameData* data = item.getGameData();\
            const auto* gameDataReferal = data->getReferenceList("color"); \
            KR_DEBUG_LOG_L9("\t\t" + data->name + " color size: " + SuppKR::toStringV100(gameDataReferal->size()));\
            if (gameDataReferal)\
            {\
                for (auto it = gameDataReferal->begin(); it != gameDataReferal->end(); ++it)\
                {\
                    const GameDataReference& colodata = *it;\
                    const auto& colorVal = colodata.ptr->getColor("color 1");\
                    int __AUTO_CHANCE__ = (int)(colorVal.r *255.f);\
                    float __AUTO_MODIFICATOR__ = colorVal.g * 255.f / 100;\
                    std::string& __AUTO_NAME__ = colodata.ptr->name;\
                    Item* __AUTO_ITEM__ = &item;\
                    __MAIN_MACROS_FOR_METHOD__;\
                }\
            }\
        }\
    }\
}

//-------------------------------------------------------------------------------------------------------
