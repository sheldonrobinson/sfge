template <typename T>
ValueHolder::ValueHolder(const TypeRegistry::TypeInfo &typeInfo, const T *defaultVal)
{
	Init(typeInfo, defaultVal);
}

template <typename T>
ValueHolder::ValueHolder(const TypeRegistry::TypeInfo &typeInfo, const T &defaultVal)
{
	Init(typeInfo, &defaultVal);
}

template <typename T>
void ValueHolder::Init(const TypeRegistry::TypeInfo &typeInfo, const T *defaultVal)
{
	mTypeInfo = &typeInfo;

	// FIXME handle alignment
	if (mTypeInfo->IsBiggerThanPointer())
		mData.mValuePtr = malloc(mTypeInfo->mSize);

	if (mTypeInfo->mHasCtorOrDtor)
	{
		if (mTypeInfo->IsBiggerThanPointer())
			mTypeInfo->mPlacementCtor(mData.mValuePtr, defaultVal);
		else
			mTypeInfo->mPlacementCtor(&mData.mValue, defaultVal);
	}
}

template <typename T>
void ValueHolder::CheckTypes() const
{
	const TypeRegistry::TypeId otherTypeId = TypeRegistration<T>::Get();
	assert(otherTypeId == mTypeInfo->mId);
}

template <typename T>
void ValueHolder::SetValue(const T &v)
{
	// Allows the holded type to be modified iff the current type is the invalid one.
	if (*mTypeInfo == TypeRegistry::InvalidType)
		Init(TypeRegistration<T>::GetFullInfos(), (const T*)nullptr);

	CheckTypes<T>();
	TypeConverter<T, (sizeof(T) > sizeof(PointerT))>::Store(mData, v);
}

template <typename T>
const T& ValueHolder::GetValue() const
{
	CheckTypes<T>();
	return TypeConverter<T, (sizeof(T) > sizeof(PointerT))>::Load(mData);
}

template <typename T>
T& ValueHolder::GetValue()
{
	CheckTypes<T>();
	return TypeConverter<T, (sizeof(T) > sizeof(PointerT))>::Load(mData);
}

// Store manipulator for types bigger than a pointer.
template <typename T>
struct ValueHolder::TypeConverter<T, true>
{
	static void Store(Data &data, const T &t)
	{
		*reinterpret_cast<T*>(data.mValuePtr) = t;
	}

	static T& Load(Data &data)
	{
		return *(reinterpret_cast<T*>(data.mValuePtr));
	}

	static const T& Load(const Data &data)
	{
		return *(reinterpret_cast<const T*>(data.mValuePtr));
	}
};

// Store manipulator for types smaller than or equat to the pointer's size.
template <typename T>
struct ValueHolder::TypeConverter<T, false>
{
	static void Store(Data &data, const T &t)
	{
		data.mValue = *reinterpret_cast<const SmallTypeT*>(&t);
	}

	static T& Load(Data &data)
	{
		return *reinterpret_cast<T*>(&data.mValue);
	}

	static const T& Load(const Data &data)
	{
		return *reinterpret_cast<const T*>(&data.mValue);
	}
};
