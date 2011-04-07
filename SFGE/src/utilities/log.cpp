#include "sfge/utilities/log.hpp"

#include <algorithm>
#include <iostream>
#include <sstream>

using namespace std;

namespace sfge
{

namespace
{
void logToCout(const std::string&msg)
{
	cout << msg;
}
}

Log::Log(const string &name)
	: mName(name), mOut(name + ".log")
{
	mCoutListener = LogListener::from_function<&logToCout>();
}

Log::~Log()
{
}

void Log::Write(const string &str)
{
	for_each(mListeners.begin(), mListeners.end(),
		[&] (const LogListener &listener) { listener(str); } );

	mOut << str;

	mOut.flush();
}

void Log::DuplicateToCout(bool enable)
{
	if (enable)
		AddListener(mCoutListener);
	else
		RemoveListener(mCoutListener);
}

void Log::AddListener(LogListener listener)
{
	mListeners.push_back(listener);
}

void Log::RemoveListener(LogListener listener)
{
	mListeners.erase(remove(mListeners.begin(), mListeners.end(), listener), mListeners.end());
}

// Stream operators
Log& sfge::operator<<(Log &logger, const string &str)
{
	logger.Write(str);
	return logger;
}

Log& sfge::operator<<(Log &logger, const char * str)
{
	logger.Write(str);
	return logger;
}

Log& sfge::operator<<(Log &logger, size_t val)
{
	ostringstream oss;
	oss << val;
	logger.Write(oss.str());
	return logger;
}

// shared_ptr overloads
LogPtr& sfge::operator<<(LogPtr &logger, const std::string &str)
{
	*logger << str;
	return logger;
}

LogPtr& sfge::operator<<(LogPtr &logger, const char * str)
{
	*logger << str;
	return logger;
}

LogPtr& sfge::operator<<(LogPtr &logger, size_t val)
{
	*logger << val;
	return logger;
}

}
