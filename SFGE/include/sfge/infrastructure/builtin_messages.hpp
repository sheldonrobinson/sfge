#ifndef SFGE_INFRASTRUCTURE_BUILTIN_MESSAGES_HPP
#define SFGE_INFRASTRUCTURE_BUILTIN_MESSAGES_HPP

namespace sfge
{
	enum MessageID
	{
		MID_AttributeChanged,	//!< Message's data will store the attribute key of the source object
		MID_MouseWheelTurned,	//!< Message's data will store the number of ticks

		MID_User,			//!< Attribute ids in user code must start from this value.
	};
}

#endif
