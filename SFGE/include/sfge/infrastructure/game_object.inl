template <typename T>
void GameObject::RegisterAttribute(size_t attributeKey, const TypeRegistry::TypeInfo &typeInfo, const T *defaultVal)
{
	assert(mAttributes.find(attributeKey) == mAttributes.end() && "Attribute key already registered!");

	detail::AttributeHolderPtr posHolder(new detail::AttributeHolder(typeInfo, defaultVal));
	mAttributes.insert(std::make_pair(attributeKey, posHolder));
}

template <typename T>
Attribute<T> GameObject::GetAttribute(size_t attributeKey)
{
	Attributes::iterator attribIt = mAttributes.find(attributeKey);
	if (attribIt == mAttributes.end())
	{
		assert("Can't find attribute!" && attribIt == mAttributes.end());
		return  Attribute<T>(detail::AttributeHolder::InvalidHolderPtr);
	}

	// Check types
	const TypeRegistry::TypeId otherTypeId = TypeRegistration<T>::Get();
	assert("Trying to get an attribute using the wrong type!" && otherTypeId == attribIt->second->GetTypeId());

	return Attribute<T>(attribIt->second);
}
