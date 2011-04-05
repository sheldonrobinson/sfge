#ifndef SFGE_INFRASTRUCTURE_BUILTIN_ATTRIBUTES_HPP
#define SFGE_INFRASTRUCTURE_BUILTIN_ATTRIBUTES_HPP

namespace sfge
{
	enum AttributeKey
	{
		AK_Position,		//!< Relates to TransformBehaviour; used to denote the game object's world position
		AK_Scale,			//!< Relates to TransformBehaviour; used to denote the game object's world scale
		AK_LayerIndex,		//!< Relates to TransformBehaviour; used to denote the game object's depth
		AK_Color,			//!< Relates to RenderShapeBehaviour & RenderSpriteBehaviour; used to denote the game object's color
		AK_Origin,			//!< Relates to RenderSpriteBehaviour; used to denote the sprite's origin (aka sprite's base point)
		AK_SpriteRegion,	//!< Relates to RenderSpriteBehaviour; used to denote the sprite's current region to use (aka sprite's frame)

		AK_User,			//!< Attribute ids in user code must start from this value.
	};
}

#endif
