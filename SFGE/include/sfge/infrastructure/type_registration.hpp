#ifndef SFGE_INFRASTRUCTURE_TYPE_REGISTRATION_HPP
#define SFGE_INFRASTRUCTURE_TYPE_REGISTRATION_HPP

#include "sfge/infrastructure/type_registry.hpp"

namespace sfge
{
	void InitTypesStub();

	template<typename T>
	struct TypeRegistration
	{
		TypeRegistration() { static_assert(false, "Using TypeRegistration<> on an undefined/incompletely defined type! Use the DEFINE_TYPEID_QUERY & IMPLEMENT_TYPEID_QUERY macros to fully implement your type."); }
		static TypeRegistry::TypeId Get()
		{
			static_assert(false, "Using TypeRegistration<> on an undefined/incompletely defined type! Use the DEFINE_TYPEID_QUERY & IMPLEMENT_TYPEID_QUERY macros to fully implement your type.");
		}
	};

// Users should use the shortcuts macros defined below
#define _DEFINE_TYPE(Type, IsComplex) \
	template<> struct sfge::TypeRegistration<Type> \
	{ \
		typedef sfge::TypeRegistration<Type> self_type; \
		\
		TypeRegistration() { sfge::TypeRegistry::RegisterType<Type>(#Type, sizeof(Type), IsComplex); } \
		\
		static sfge::TypeRegistry::TypeId Get() \
		{ \
			return sfge::TypeRegistry::GetTypeInfoFor(#Type).mId; \
		} \
		\
		static const sfge::TypeRegistry::TypeInfo& GetFullInfos() \
		{ \
			return sfge::TypeRegistry::GetTypeInfoFor(#Type); \
		} \
		\
		static self_type tag; \
	};

#define DEFINE_POD_TYPEID(Type)			_DEFINE_TYPE(Type, false)
#define DEFINE_COMPLEX_TYPEID(Type)		_DEFINE_TYPE(Type, true)

#define IMPLEMENT_TYPEID_QUERY(Type)	sfge::TypeRegistration<Type>::self_type	sfge::TypeRegistration<Type>::tag;
}

#endif
