#ifndef SFGE_SPRITE_ANIMATION_BEHAVIOUR_HPP
#define SFGE_SPRITE_ANIMATION_BEHAVIOUR_HPP

#include "sfge/infrastructure/behaviour.hpp"
#include "sfge/infrastructure/infrastructure_fwd.hpp"
#include "sfge/infrastructure/message.hpp"

#include <SFML/Graphics/Rect.hpp>

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace sfge
{
	class SpriteAnimationBehaviour : public sfge::Behaviour
	{
	public:
		SpriteAnimationBehaviour(sfge::GameObjectWeakPtr owner = sfge::GameObjectPtr());
		
		virtual void OnParamsReceived(const sfge::Parameters &params)	override;
		virtual void OnUpdate(float dt) override;

	private:
		enum PlayMode
		{
			PM_Loop,
			PM_Once,
			PM_PingPong,
			PM_PingPong_Once,
		};

		struct AnimFrame
		{
			float			mDuration;
			sf::IntRect		mFrameRect;
			sf::Vector2f	mOrigin;
		};
		typedef std::vector<AnimFrame> AnimFrames;

		struct Animation
		{
			AnimFrames	mAnimFrames;
			PlayMode	mPlayMode;
		};
		typedef std::shared_ptr<Animation>	AnimationPtr;

		typedef std::map<std::string, AnimationPtr>	AnimationDict;

	private:
		void	ParseAnimation(const sfge::Parameters &animDef);
		void	ParseAnimationFrames(AnimationPtr out, const sfge::Parameters &animFrameDefs);
		void	ResetCurrentAnim();
		void	EnableCurrentAnimFrame();
		void	OnAttributeChanged(const Message &msg);

	private:
		AnimationDict	mAnimationDict;

		AnimationPtr	mCurrentAnim;
		size_t			mCurrentFrameIndex;
		float			mElapsedTime;
		int				mDirection;
	};
}

#endif
