template <typename T>
Attribute<T>::Attribute(detail::AttributeHolderPtr holder)
	: mHolder(holder)
{
}

template <typename T>
bool Attribute<T>::IsValid() const
{
	return mHolder && mHolder->GetTypeId() != TypeRegistry::InvalidTypeId;
}

template <typename T>
const T& Attribute<T>::Get() const
{
	return mHolder->GetValue<T>();
}

template <typename T>
T& Attribute<T>::Get()
{
	return mHolder->GetValue<T>();
}

template <typename T>
T& Attribute<T>::operator*()
{
	return Get();
}

template <typename T>
const T& Attribute<T>::operator*() const
{
	return Get();
}

template <typename T>
T* Attribute<T>::operator->()
{
	return &Get();
}

template <typename T>
const T* const Attribute<T>::operator->() const
{
	return &Get();
}

template <typename T>
void Attribute<T>::operator=(const T &v)
{
	mHolder->SetValue(v);
}

template <typename T>
Attribute<T>::operator T() const
{
	return mHolder->GetValue<T>();
}
