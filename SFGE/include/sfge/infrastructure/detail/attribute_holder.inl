template <typename T>
void AttributeHolder::CheckTypes() const
{
	const TypeRegistry::TypeId otherTypeId = TypeRegistration<T>::Get();
	assert(otherTypeId == mTypeInfo.mId);
}

template <typename T>
void AttributeHolder::SetValue(const T &v)
{
	CheckTypes<T>();
	ValueHolder<T, static_cast<bool>(sizeof(T) > sizeof(T*))>::Store(mValue, v);
}

template <typename T>
const T& AttributeHolder::GetValue() const
{
	CheckTypes<T>();
	return ValueHolder<T, static_cast<bool>(sizeof(T) > sizeof(T*))>::Load(mValue);
}

template <typename T>
T& AttributeHolder::GetValue()
{
	CheckTypes<T>();
	return ValueHolder<T, static_cast<bool>(sizeof(T) > sizeof(T*))>::Load(mValue);
}

// Store manipulator for types bigger than a pointer.
template <typename T>
struct AttributeHolder::ValueHolder<T, true>
{
	static void Store(void *store, const T &t)
	{
		*reinterpret_cast<T*>(store) = t;
	}

	static T& Load(void *store)
	{
		return *(reinterpret_cast<T*>(store));
	}
};

// Store manipulator for types smaller than or equat to the pointer's size.
template <typename T>
struct AttributeHolder::ValueHolder<T, false>
{
	static void Store(void *store, const T &t)
	{
		store = reinterpret_cast<void*>(t);
	}

	static T& Load(void *store)
	{
		return reinterpret_cast<T>(store);
	}
};
