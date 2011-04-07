#ifndef SFGE_UTILITIES_LOG_HPP
#define SFGE_UTILITIES_LOG_HPP

#include "sfge/utilities/delegate.hpp"

#include <fstream>
#include <memory>
#include <string>
#include <vector>

namespace sfge
{
	class Log
	{
	public:
		typedef delegate<void(const std::string &)>		LogListener;

	public:
		Log(const std::string &name);
		~Log();

		const std::string&	GetName() const		{ return mName; }

		void Write(const std::string &str);

		void DuplicateToCout(bool enable);
		void AddListener(LogListener listener);
		void RemoveListener(LogListener listener);

		friend Log& operator<<(Log &logger, const std::string &str);
		friend Log& operator<<(Log &logger, const char * str);
		friend Log& operator<<(Log &logger, size_t val);

	private:
		typedef std::vector<LogListener>	LogListeners;

	private:
		std::string		mName;
		std::ofstream	mOut;

		LogListeners	mListeners;
		LogListener		mCoutListener;
	};

	typedef std::shared_ptr<Log> LogPtr;

	LogPtr& operator<<(LogPtr &logger, const std::string &str);
	LogPtr& operator<<(LogPtr &logger, const char * str);
	LogPtr& operator<<(LogPtr &logger, size_t val);
}

#endif
