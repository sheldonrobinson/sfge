template <typename T>
Attribute<T> GameObject::GetAttribute(size_t attributeKey)
{
	Attributes::iterator attribIt = mAttributes.find(attributeKey);
	if (attribIt == mAttributes.end())
	{
		assert("Can't find attribute!" && attribIt == mAttributes.end());
		return  Attribute<T>(detail::AttributeHolder::InvalidHolderPtr);
	}

	return Attribute<T>(attribIt->second);
}
