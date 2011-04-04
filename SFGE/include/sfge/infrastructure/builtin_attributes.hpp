#ifndef SFGE_INFRASTRUCTURE_BUILTIN_ATTRIBUTES_HPP
#define SFGE_INFRASTRUCTURE_BUILTIN_ATTRIBUTES_HPP

namespace sfge
{
	enum AttributeKey
	{
		AK_Position,
		AK_Scale,
		AK_Color,
		AK_Origin,
		AK_LayerIndex,

		AK_User,			//!< Attribute ids in user code must start from this value.
	};
}

#endif
