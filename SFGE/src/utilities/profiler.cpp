#include <cassert>
#include <xfunctional>

#include "sfge/utilities/profiler.hpp"

using namespace std;

namespace sfge
{

Profiler::SectionData::SectionData(size_t psid, size_t nid)
    : m_ParentSectionID(psid), m_NameID(nid)
{
#ifdef WIN32
    QueryPerformanceCounter(&m_TicksCount);
#endif
}

Profiler::Profiler(size_t baseSectionSize)
    : m_ActiveSectionID(numeric_limits<size_t>::max())
{
    m_SectionData.reserve(baseSectionSize);

#ifdef WIN32
    QueryPerformanceFrequency(&m_Frequency);
#endif
}

void Profiler::StartSection(const string &name)
{
    assert(!name.empty());

    SectionNameDict::iterator it = m_SectionNames.insert(SectionNameDict::value_type(hash<string>()(name), name)).first;
    m_SectionData.push_back(SectionData(m_ActiveSectionID, it->first));

    m_ActiveSectionID = m_SectionData.size() - 1;
}

void Profiler::EndSection()
{
    if (numeric_limits<size_t>::max() == m_ActiveSectionID)
        return;
    
    SectionData &sd = m_SectionData[m_ActiveSectionID];
    m_ActiveSectionID = sd.m_ParentSectionID;
    
#ifdef WIN32
    LARGE_INTEGER end;
    QueryPerformanceCounter(&end);
    sd.m_TicksCount.QuadPart = end.QuadPart - sd.m_TicksCount.QuadPart;
#endif
}

}