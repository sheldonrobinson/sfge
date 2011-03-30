template <typename T>
void AttributeHolder::SetValue(const T &v)
{
	assert(sizeof(T) == mTypeInfo.second);
	ValueHolder<T, static_cast<bool>(sizeof(T) > sizeof(T*))>::Store(mValue, v);
}

template <typename T>
const T& AttributeHolder::GetValue() const
{
	assert(sizeof(T) == mTypeInfo.second);
	return ValueHolder<T, static_cast<bool>(sizeof(T) > sizeof(T*))>::Load(mValue);
}

template <typename T>
T& AttributeHolder::GetValue()
{
	assert(sizeof(T) == mTypeInfo.second);
	return ValueHolder<T, static_cast<bool>(sizeof(T) > sizeof(T*))>::LoadRef(mValue);
}

// Store manipulator for types bigger than a pointer.
template <typename T>
struct AttributeHolder::ValueHolder<T, true>
{
	static void Store(void *store, const T &t)
	{
		*reinterpret_cast<T*>(store) = t;
	}

	static const T& Load(void *store)
	{
		return *(reinterpret_cast<T*>(store));
	}

	static T& LoadRef(void *store)
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

	static const T& Load(void *store)
	{
		return reinterpret_cast<T>(store);
	}

	static T& LoadRef(void *store)
	{
		return reinterpret_cast<T>(store);
	}
};
