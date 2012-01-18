#ifndef SFGE_UTILITIES_PROFILER_HPP
#define SFGE_UTILITIES_PROFILER_HPP

#ifdef _WIN32
#include <windows.h>
#undef max
#else // WIN32
#error Profiler not supported for current platform :(
#endif // WIN32

#include <limits>
#include <map>
#include <string>
#include <vector>

namespace sfge
{
//! Custom sections profiler, allows nested sections.
/*! Sample usage:
    \code
Profiler prof;
prof.StartSection("MySection");
MyVeryExpensiveFunc();
prof.EndSection();
prof.Report(ProfilerStreams::OStream(cout, 25), false);  // Will write the results to cout
    \endcode
    Will report:
    \verbatim
Sections                 Duration

MySection................6.29711476s
    \endverbatim

    \section Reporter
    As you can see in the example, profiler doesn't work alone; you need a \e ReporterT class.
    ReporterT must provide these 3 methods:
    - StartReport()
    - Report(const std::string &sectionName, int sonLevel, double duration) where:
        - sectionName is the name of the section, as specfied in StartSection (or if no name was specified, "<anonymous>" is reported)
        - sonLevel is the depth of the section in the sections hierarchy
        - duration is the section's duration in seconds
    - EndReport()
    .
    See ProfilerStreams::OStream for an example.
 */
    class Profiler
    {
    public:
        //! Create a new Profiler, reserving the memory needed for \p baseSectionSize SectionData results.
        Profiler(size_t baseSectionSize = 16384);

        //! Starts a new named section; if already in a section, this will create a nested section.
        /*! \warning \p name must not be empty! (assert raised in debug, nothing in release) */
        void    StartSection(const std::string &name = std::string("<anonymous>"));

        //! Ends current section.
        void    EndSection();

        //! Report results using a custom \p reporter.
        /*! If \p clearResults is true, stored data is cleared. */
        template <typename ReporterT>
        void    Report(ReporterT &reporter, bool clearResults = true);

    private:
        //! <Name's hash, Name>
        typedef std::map<size_t, std::string> SectionNameDict;

        //! Store some information about profiled section.
        /*! \warning This structure's size vary based on OS; eg, on Windows, a LARGE_INTEGER is added. */
        struct SectionData
        {
            SectionData(size_t psid = std::numeric_limits<size_t>::max(),
                        size_t nid = std::numeric_limits<size_t>::max());
        
            size_t          m_ParentSectionID;  //!< Index of parent section, or numeric_limits<size_t>::max() if none.
            size_t          m_NameID;           //!< Index of section's name, or numeric_limits<size_t>::max() if none.
    #ifdef _WIN32
            LARGE_INTEGER   m_TicksCount;       //!< Start time or duration when section ended, expressed as tick count.
    #endif
        };
        typedef std::vector<SectionData> SectionDataCont;

    private:
    #ifdef _WIN32
        LARGE_INTEGER   m_Frequency;            //!< Number of ticks/seconds of the timer
    #endif

        size_t          m_ActiveSectionID;      //!< Index of current section, or numeric_limits<size_t>::max() if none.

        SectionNameDict     m_SectionNames;     //!< List of sections' name
        SectionDataCont     m_SectionData;      //!< List of profiled sections
    };

#define _PROFILER_HPP_NEEDS_IMPL
#include "profiler.inl"
#undef _PROFILER_HPP_NEEDS_IMPL

} // namespace sfge

#endif // SFGE_UTILITIES_PROFILER_HPP
