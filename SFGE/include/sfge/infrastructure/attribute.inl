template <typename T>
Attribute<T>::Attribute(detail::AttributeHolderPtr holder)
	: mHolder(holder)
{
}

template <typename T>
bool Attribute<T>::isValid() const
{
	return mHolder && mHolder->GetTypeId() != TypeRegistry::InvalidType;
}
