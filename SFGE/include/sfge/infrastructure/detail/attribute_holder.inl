template <typename T>
void AttributeHolder::setValue(T v)
{
	mValue = ValueHolder<T, sizeof(T) > sizeof(T*)>::toStorage(v);
}

template <typename T>
T AttributeHolder::getValue()
{
	return ValueHolder<T, sizeof(T) > sizeof(T*)>::fromStorage(mValue);
}

template <typename T>
struct AttributeHolder::ValueHolder<T, true>
{
	static void* toStorage(const T &t)
	{
		return &t;
	}
	static T fromStorage(void *v)
	{
		return *t;
	}
};

template <typename T>
struct AttributeHolder::ValueHolder<T, false>
{
	static void* toStorage(const T &t)
	{
		return reinterpret_cast<void*>(t);
	}
	static T fromStorage(void *v)
	{
		return reinterpret_cast<T>(v);
	}
};
