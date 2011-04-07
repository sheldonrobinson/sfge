#include "sfge/utilities/log_manager.hpp"

#include <iostream>

using namespace std;

namespace sfge
{

LogManager* LogManager::ms_Singleton = 0;

LogManager::LogManager()
{
	LogPtr defaultLogger(new Log("SFGE"));
	mLoggers.insert(make_pair("SFGE", defaultLogger));
	mDefaultLogger = defaultLogger;
	mDefaultLogger->DuplicateToCout(true);
}

void LogManager::Init()
{
	new LogManager();
}

void LogManager::AddLogger(LogPtr logger)
{
	mLoggers.insert(make_pair(logger->GetName(), logger));
}

void LogManager::RemoveLogger(LogPtr logger)
{
	if (mDefaultLogger.get() == logger.get())
	{
		mDefaultLogger << "Tried to remove default logger from available loggers.\n";
		return;
	}

	mLoggers.erase(logger->GetName());
}

LogPtr LogManager::GetDefaultLogger() const
{
	return mDefaultLogger;
}

void LogManager::Write(const std::string &str)
{
	mDefaultLogger->Write(str);
}

LogManager& sfge::operator<<(LogManager &logMgr, const std::string &str)
{
	logMgr.Write(str);
	return logMgr;
}

LogManager& sfge::operator<<(LogManager &logMgr, const char *str)
{
	logMgr.Write(string(str));
	return logMgr;
}

LogManager& sfge::operator<<(LogManager &logMgr, size_t val)
{
	logMgr.mDefaultLogger << val;
	return logMgr;
}

}
