#ifndef SFGE_UTILITIES_EXCEPTION_STR_HPP
#define SFGE_UTILITIES_EXCEPTION_STR_HPP

#include <exception>
#include <string>

namespace sfge
{
	class ExceptionStr : public std::exception
	{
	public:
		ExceptionStr(const std::string &text)
			: mText(text)
		{
		}

		virtual const char *what() const override
		{
			return mText.c_str();
		}

	private:
		std::string mText;
	};
}

#endif
