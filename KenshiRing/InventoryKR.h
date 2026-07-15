//-----------------------------------------------------
//
// Класс управляющий новыми слотами
//
// Для безопасного добавления логики перейдите в setup.cpp и используйте макросы из SetupMacrosHelper.h
// 
//-----------------------------------------------------

#pragma once
#include "ConfigureInventory.h"

// TODO: добавить в InventoryKR проверку доступности слотов в layout чтобы избежать краш (!)
class InventoryKR
{
public:


    static InventoryKR& instance()
    {
        static InventoryKR inst;
        return inst;
    }
    
    void manualAddSection(ConfigIKR::PropertySectionKR propertyNewSection)
    {
        if (freezeNewSections)
        {
            KR_ERROR_LOG("Cannot add a new section – FREEZE instance." + propertyNewSection.m_name);
            return;
        }
        if (propertyNewSection.m_name.empty())
        {
            KR_ERROR_LOG("Cannot add a new section – undefined m_name." + propertyNewSection.m_name);
            return;
        }
        if (isExist(propertyNewSection.m_name))
        {
            KR_ERROR_LOG("Cannot add a new section - Section: " + propertyNewSection.m_name + ", is exist.");
            return;
        }
        if (!findWidgetInLayout(layoutPath, propertyNewSection.m_name))
        {
            KR_ERROR_LOG("Cannot add a new section - m_name: " + propertyNewSection.m_name + ", not found in .layout: " + layoutPath);
            return;
        }
        newSectionInventory.push_back(propertyNewSection);
        KR_DEBUG_LOG_L3_1("Section added - " + propertyNewSection.m_name);
    }
    void setGameSection(const ConfigIKR::PropertySectionKR& gameSectionsInventory)
    {
        if (freezeGameSections)
        {
            KR_ERROR_LOG("Cannot add a game section – FREEZE instance." + gameSectionsInventory.m_name);
            return;
        }
        this->gameSectionsInventory.push_back(gameSectionsInventory);
    }

    /// <summary>
    /// после использования невозможно будет добавить новые слоты
    /// небольшая мера предосторожности
    /// </summary>
    /// <returns></returns>
    const std::vector<ConfigIKR::PropertySectionKR>& getNewSections()
    {
        freezeNewSections = true;
        return newSectionInventory;
    }
    const std::vector<ConfigIKR::PropertySectionKR>& getGameSections()
    {
        freezeGameSections = true;
        return gameSectionsInventory;
    }
    const std::unordered_map<AttachSlot, std::set<ConfigIKR::PropertySectionKR>>& getSortAllSection() const
    {
        return m_sortAllSection;
    }

    const std::set<ConfigIKR::PropertySectionKR>& getAllSectionForAttach(AttachSlot slot) const
    {
        auto it = m_sortAllSection.find(slot);

        if (it == m_sortAllSection.end())
        {
            KR_ERROR_LOG("InventoryKR -> AttachSlot not found");
        }
        return it->second;
    }

    void  sortSections()
    {
        for (size_t i = 0; i < newSectionInventory.size(); i++)
        {
            ConfigIKR::PropertySectionKR* section = &newSectionInventory[i];
            m_sortAllSection[section->m_sectionAttach].emplace(*section);
        }

        for (size_t i = 0; i < gameSectionsInventory.size(); i++)
        {
            ConfigIKR::PropertySectionKR* section = &gameSectionsInventory[i];
            m_sortAllSection[section->m_sectionAttach].emplace(*section);
        }
    }


protected:

    std::string layoutPath;

    std::vector<ConfigIKR::PropertySectionKR> newSectionInventory;
    std::vector<ConfigIKR::PropertySectionKR> gameSectionsInventory;

    std::unordered_map<AttachSlot, std::set<ConfigIKR::PropertySectionKR>> m_sortAllSection;

    bool freezeNewSections;
    bool freezeGameSections;

    InventoryKR()
    {
        freezeGameSections = false;
        freezeNewSections = false;

        // move to "setup"?
        layoutPath = "mods/KenshiRing/gui/layout/Kenshi_InventoryCharacterWindow.layout";
    };
    //InventoryKR(const InventoryKR&) = delete;
    //InventoryKR& operator=(const InventoryKR&) = delete;

    bool isExist(std::string nameSection)
    {
        if (newSectionInventory.empty()) 
        {
            return false;
        }

        for (size_t it = 0; it < newSectionInventory.size(); it++)
        {
            if (newSectionInventory[it].m_name == nameSection)
            {
                return true;
            }
        }

        return false;
    }

    /// <summary>
    /// проверяет есть ли данный виджет в .layout названием targetName
    /// </summary>
    /// <param m_name="filePath"></param>
    /// <param m_name="targetName"></param>
    /// <returns></returns>
    bool findWidgetInLayout(const std::string& filePath, const std::string& targetName)
    {
        return true;
    }
};


