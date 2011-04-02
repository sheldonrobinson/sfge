template <typename T>
void* Constructer(const T *t)
{
	if (!t)
		return new T;

	return new T(*t);
}

template <typename T>
void* PlacementConstructer(void *where, const T *t)
{
	assert(where);

	if (!t)
		return new (where) T;

	return new (where) T(*t);
}

template <typename T>
void Deleter(T *t)
{
	delete t;
}

template <typename T>
void TypeRegistry::RegisterType(const TypeName &typeName, size_t sizeType, bool hasCtorOrDtor)
{
	TypeRegistryHolder::const_iterator it = GetTypeRegistryHolder().find(typeName);
	if (it != GetTypeRegistryHolder().end())
	{
		assert("Type already registered!" && it == GetTypeRegistryHolder().end());
		return;
	}

	const TypeId tId = mNextId++;
	TypeInfo tInfo(tId, sizeType, hasCtorOrDtor);
	if (hasCtorOrDtor)
	{
		tInfo.mDefaultCtor		= reinterpret_cast<Ctor>(Constructer<T>);
		tInfo.mPlacementCtor	= reinterpret_cast<PlacemtCtor>(PlacementConstructer<T>);
		tInfo.mDtor				= reinterpret_cast<Dtor>(Deleter<T>);
	}
	GetTypeRegistryHolder().insert(make_pair(typeName, tInfo));
}
