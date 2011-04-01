#ifndef SFGE_INFRASTRUCTURE_TYPE_REGISTRATION_HPP
#define SFGE_INFRASTRUCTURE_TYPE_REGISTRATION_HPP

#include "sfge/infrastructure/type_registry.hpp"

#include <boost/static_assert.hpp>

namespace sfge
{
	void InitTypesStub();

	template<typename T>
	struct TypeRegistration
	{
		TypeRegistration() { BOOST_STATIC_ASSERT(0 && "Using TypeRegistration<> on an undefined/incompletely defined type! Use the DEFINE_TYPEID_QUERY & IMPLEMENT_TYPEID_QUERY macros to fully implement your type."); }
		static TypeRegistry::TypeId Get()
		{
			BOOST_STATIC_ASSERT(0 && "Using TypeRegistration<> on an undefined/incompletely defined type! Use the DEFINE_TYPEID_QUERY & IMPLEMENT_TYPEID_QUERY macros to fully implement your type.");
		}
	};

#define DEFINE_TYPEID_QUERY(Type, HasCtorOrDtor) \
	template<> struct sfge::TypeRegistration<Type> \
	{ \
		typedef sfge::TypeRegistration<Type> self_type; \
		\
		TypeRegistration() { sfge::TypeRegistry::RegisterType(#Type, sizeof(Type), HasCtorOrDtor); } \
		\
		static sfge::TypeRegistry::TypeId Get() \
		{ \
			return sfge::TypeRegistry::GetTypeInfoFor(#Type).mId; \
		} \
		\
		static self_type tag; \
	};

#define IMPLEMENT_TYPEID_QUERY(Type)	sfge::TypeRegistration<Type>::self_type	sfge::TypeRegistration<Type>::tag;
}

#endif
