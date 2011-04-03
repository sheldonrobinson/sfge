template <typename T>
Attribute<T>::Attribute(detail::AttributeHolderPtr holder,
						GameObjectWeakPtr owner, size_t attrKey) :
	mHolder(holder), mOwner(owner),
	mAttributeKey(attrKey), mPotentiallyModified(false)
{
}

template <typename T>
Attribute<T>::~Attribute()
{
	if (mPotentiallyModified)
	{
		Message msg;
		msg.mMessageID	= MID_AttributeChanged;
		msg.mSource		= mOwner;
		msg.mMsgData	= mAttributeKey;

		MessageManager::getSingleton().Queue(msg);
	}
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
	mPotentiallyModified = true;
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
	mPotentiallyModified = true;
	mHolder->SetValue(v);
}

template <typename T>
Attribute<T>::operator T() const
{
	return mHolder->GetValue<T>();
}

template <typename T>
Attribute<T>::operator bool() const
{
	return IsValid();
}
