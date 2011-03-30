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
void Attribute<T>::operator=(const T &v)
{
	mHolder->SetValue(v);
}

template <typename T>
Attribute<T>::operator T() const
{
	return mHolder->GetValue();
}
