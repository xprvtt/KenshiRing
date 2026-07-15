#pragma once
#include "CoreKenshiRing.h"

namespace ConfigIKR // config inventory - kenshi ring
{
    /// <summary>
    /// m_width и m_height
    /// </summary>
    struct Size2D
    {
        int m_width;
        int m_height;
        Size2D() :m_width(0), m_height(0) {};
        Size2D(int w, int h) : m_width(w), m_height(h) {};

        bool operator<(const Size2D& other) const
        {
            return (m_width * m_height) < (other.m_width * other.m_height);
        }
        bool operator==(const Size2D& other) const
        {
            return m_width == other.m_width && m_height == other.m_height;
        }
        bool operator<=(const Size2D& other) const
        {
            return m_width <= other.m_width && m_height <= other.m_height;
        }
    };

    /// <summary>
    /// свойства нового добавляемого слота
    /// </summary>
    struct PropertySectionKR {
        std::string m_name;
        Size2D m_sizeSection;
        AttachSlot m_sectionAttach;
        int m_limit;
        bool m_equipCallbacks;
        bool m_isContainerSection;
        bool m_enabled;

        bool operator<(const PropertySectionKR& o) const
        {
            return std::tie(m_sizeSection, m_limit, m_name, m_sectionAttach, m_equipCallbacks, m_isContainerSection, m_enabled)
                   < std::tie(o.m_sizeSection, o.m_limit, o.m_name, o.m_sectionAttach, o.m_equipCallbacks, o.m_isContainerSection,o.m_enabled);
        }

        bool operator==(const PropertySectionKR& other) const
        {
            return m_name               == other.m_name &&
                   m_sizeSection        == other.m_sizeSection &&
                   m_sectionAttach      == other.m_sectionAttach &&
                   m_limit              == other.m_limit &&
                   m_equipCallbacks     == other.m_equipCallbacks &&
                   m_isContainerSection == other.m_isContainerSection &&
                   m_enabled            == other.m_enabled;
        }

        PropertySectionKR() : m_name("PropertySectionKR_NO_NAME"), m_sizeSection(Size2D(0, 0)), m_sectionAttach(AttachSlot::ATTACH_NONE), m_equipCallbacks(false), 
            m_isContainerSection(false), m_enabled(false), m_limit(0){}

        PropertySectionKR(std::string name, Size2D size, AttachSlot attach, bool equipCallbacks, bool isContainer, bool enabled, int limit)        
            : m_name(name), m_sizeSection(size), m_sectionAttach(attach), m_equipCallbacks(equipCallbacks), m_isContainerSection(isContainer), m_enabled(enabled), m_limit(limit) {}

    };


    class Container2D
    {
    public:
        Container2D(int w, int h) : width(w), height(h), mapItem(h, std::vector<char>(w, '.')) {}
        Container2D(Size2D size) : width(size.m_width), height(size.m_height), mapItem(size.m_height, std::vector<char>(size.m_width, '.')) {}

        bool place(Size2D s, char id = 'X')
        {
            for (int y = 0; y <= height - s.m_height; ++y)
            {
                for (int x = 0; x <= width - s.m_width; ++x)
                {
                    if (canPlace(x, y, s))
                    {
                        toPlace(x, y, s, id);
                        return true;
                    }
                }
            }
            return false;
        }

        bool canPlace(int x, int y, Size2D s)
        {
            if (x + s.m_width > width || y + s.m_height > height)
            {
                return false;
            }
            for (int yy = y; yy < y + s.m_height; ++yy)
            {
                for (int xx = x; xx < x + s.m_width; ++xx)
                {
                    if (mapItem[yy][xx] != '.')
                    {
                        return false;
                    }
                }
            }
            return true;
        }
        //void print()
        //{
        //    for (int y = 0; y < mapItem.size(); y++)
        //    {
        //        for (int x = 0; x < mapItem[y].size(); x++)
        //        {
        //            KR_RELEASE_LOG(mapItem[y][x] + " ");
        //        }
        //        KR_RELEASE_LOG("\n");
        //    }
        //}

    private:
        std::vector<std::vector<char>> mapItem;
        int width, height;

        void toPlace(int x, int y, Size2D s, char id)
        {
            for (int yy = y; yy < y + s.m_height; yy++)
            {
                for (int xx = x; xx < x + s.m_width; xx++)
                {
                    mapItem[yy][xx] = id;
                }
            }
        }
    };
}

