#ifndef _PROFILER_HPP_NEEDS_IMPL
#error "profiler.inl" must not be included directly.
#endif

template <typename ReporterT>
void Profiler::Report(ReporterT &reporter, bool clearResults)
{
    std::vector<size_t> parentsDepth(m_SectionData.size(), 0);
    size_t idx = 0;
    
    reporter.StartReport();
    for(SectionDataCont::const_iterator cit = m_SectionData.cbegin();
        cit != m_SectionData.cend();
        ++cit, ++idx)
    {
        // Compute duration as seconds
#ifdef WIN32
        const double durationSecs = static_cast<double>(cit->m_TicksCount.QuadPart) / m_Frequency.QuadPart;
#endif

        // Check & eventually update current depth
        if (cit->m_ParentSectionID != std::numeric_limits<size_t>::max())
            parentsDepth[idx] = parentsDepth[cit->m_ParentSectionID] + 1;
        
        // Report this section
        reporter.Report(m_SectionNames[cit->m_NameID], parentsDepth[idx], durationSecs);
    }
    reporter.EndReport();

    // Clear profiler's data if requested
    if (clearResults)
    {
        m_SectionNames.clear();
        m_SectionData.clear();

        m_ActiveSectionID = std::numeric_limits<size_t>::max();
    }
}
