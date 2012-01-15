#include <algorithm>
#include <iomanip>
#include <iterator>

#include <stdio.h>

#ifdef WIN32
#include <Windows.h>
#endif // WIN32

#include "sfge/utilities/profilerstreams.hpp"

using namespace std;

namespace
{
    static const int DurationPrecision  = 10;
}

namespace sfge
{
namespace ProfilerStreams
{

// -------------------------------------------
// OStream

OStream::OStream(std::ostream &os, streamsize sectionNameWidth)
    : m_Stream(os), m_SectionNameWidth(sectionNameWidth)
{
}
        
void OStream::StartReport()
{
    // Setup ostream
    m_OriginalFmtFlags = m_Stream.flags();
    m_Stream.setf(ios::left,  ios::adjustfield);
    m_Stream.setf(ios::fixed, ios::floatfield);

    m_OriginalPrecision = m_Stream.precision();
    m_Stream.precision(DurationPrecision);

    m_OriginalFiller = m_Stream.fill();

    // Print header
    if (m_SectionNameWidth > 0)
        m_Stream << setw(m_SectionNameWidth);
    m_Stream << "Sections" << "Duration" << endl << endl;
    m_Stream.fill('.');
}

void OStream::Report(const std::string &sectionName, int sonLevel, double duration)
{
    fill_n(ostream_iterator<char>(m_Stream), sonLevel, '-');

    if (m_SectionNameWidth > 0)
        m_Stream << setw(m_SectionNameWidth - sonLevel);
    m_Stream << sectionName << duration << "s" << endl;
}

void OStream::EndReport()
{
    m_Stream.fill       (m_OriginalFiller);
    m_Stream.precision  (m_OriginalPrecision);
    m_Stream.flags      (m_OriginalFmtFlags);
}

// -------------------------------------------
// BinaryOStream

BinaryOStream::BinaryOStream(std::ostream &os)
    : m_Stream(os)
{
}
        
void BinaryOStream::StartReport()
{
}

void BinaryOStream::Report(const std::string &sectionName, int sonLevel, double duration)
{
    m_Stream.write(reinterpret_cast<const char*>(&sonLevel), sizeof(int));
    m_Stream.write(sectionName.c_str(), sectionName.length() + 1);
    m_Stream.write(reinterpret_cast<const char*>(&duration), sizeof(double));
}

void BinaryOStream::EndReport()
{
}

// -------------------------------------------
// DebugOutput

#ifdef WIN32

void DebugOutput::StartReport()
{
}

void DebugOutput::Report(const std::string &sectionName, int sonLevel, double duration)
{
    // Create indent string
    char indentBuf[64];
    memset(indentBuf, 0, 64);
    for (int i = 0; i != sonLevel; i++)
        indentBuf[i] = '-';

    const size_t BufSize = 512;
    char buffer[BufSize];
    memset(buffer, 0, BufSize);

    sprintf(buffer, "[PROFILER] %s%s : %.*f\n", indentBuf, sectionName.c_str(), DurationPrecision, duration);

    OutputDebugStringA(buffer);
}

void DebugOutput::EndReport()
{
}

#endif // WIN32

} // namespace ProfilerStreams
} // namespace sfge
