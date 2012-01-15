#ifndef SFGE_UTILITIES_PROFILERSTREAMS_HPP
#define SFGE_UTILITIES_PROFILERSTREAMS_HPP

#include <ostream>
#include <string>

namespace sfge
{

namespace ProfilerStreams
{
    //! Output \link Profiler profiler's \endlink results to a std::ostream&.
    /*! Please, note that this class will output a text file. For binary output, have a look at BinaryOStream.
        Sample usage:
        \code
Profiler prof;
prof.StartSection("MySection");
MyVeryExpensiveFunc();
prof.EndSection();
prof.Report(ProfilerStreams::OStream(std::cout), false); // Will write the results to cout
prof.Report(ProfilerStreams::OStream(std::ofstream("report.txt")); // Will write the results into "report.txt"
        \endcode
     */
    class OStream
    {
    public:
        //! Construct an OStream reporter, using stream \p os; the sections' names are in a column of width \p sectionNameWidth
        OStream(std::ostream &os, std::streamsize sectionNameWidth = 65);
        
        void StartReport();
        void Report(const std::string &sectionName, int sonLevel, double duration);
        void EndReport();

    private:
        std::ostream    &   m_Stream;
        std::streamsize     m_SectionNameWidth;

        // Save ostream's state
        std::streamsize             m_OriginalPrecision;
        std::ios_base::fmtflags     m_OriginalFmtFlags;
        char                        m_OriginalFiller;
    };

    //! Basically acts the same way as OStream, but output the results in binary format (ie, using ostream::write)
    /*! Output format description:
        - depth as int
        - section's name as null-terminated string
        - section's duration in seconds as double
     */
    class BinaryOStream
    {
    public:
        //! Construct a BinaryOStream reporter, using stream \p os.
        BinaryOStream(std::ostream &os);
        
        void StartReport();
        void Report(const std::string &sectionName, int sonLevel, double duration);
        void EndReport();

    private:
        std::ostream    &   m_Stream;
    };

#ifdef WIN32
    //! Output profiler's results to Windows' debug stream.
    class DebugOutput
    {
    public:
        void StartReport();
        void Report(const std::string &sectionName, int sonLevel, double duration);
        void EndReport();
    };
#endif // WIN32

} // namespace ProfilerStreams

} // namespace sfge

#endif // SFGE_UTILITIES_PROFILERSTREAMS_HPP
