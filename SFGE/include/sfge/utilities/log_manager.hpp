#ifndef SFGE_UTILITIES_LOG_MANAGER_HPP
#define SFGE_UTILITIES_LOG_MANAGER_HPP

#include "sfge/utilities/singleton.hpp"
#include "sfge/utilities/log.hpp"

#include <map>
#include <string>

namespace sfge
{
	class LogManager : public Singleton<LogManager>
	{
	public:
		static void Init();

		void AddLogger(LogPtr logger);
		void RemoveLogger(LogPtr logger);

		LogPtr GetDefaultLogger() const;

		void Write(const std::string &str);

		friend LogManager& operator<<(LogManager &logMgr, const std::string &str);
		friend LogManager& operator<<(LogManager &logMgr, const char *str);
		friend LogManager& operator<<(LogManager &logMgr, size_t val);

	private:
		LogManager();

	private:
		typedef std::map<std::string, LogPtr>	Loggers;

	private:
		Loggers mLoggers;
		LogPtr	mDefaultLogger;
	};
}

#endif
