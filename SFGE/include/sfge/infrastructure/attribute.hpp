#ifndef SFGE_INFRASTRUCTURE_ATTRIBUTE_HPP
#define SFGE_INFRASTRUCTURE_ATTRIBUTE_HPP

#include <memory>

namespace sfge
{
	template <typename T>
	class Attribute;

	template <typename T>
	typedef std::shared_ptr< Attribute<T> >	AttributePtr;

	template <typename T>
	class Attribute
	{
	public:
		static AttributePtr Create();
		~Attribute();

	public:
		T	mValue;

	private:
		Attribute();
	};
}

#endif
