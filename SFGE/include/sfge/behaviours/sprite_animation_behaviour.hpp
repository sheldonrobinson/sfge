#ifndef SFGE_SPRITE_ANIMATION_BEHAVIOUR_HPP
#define SFGE_SPRITE_ANIMATION_BEHAVIOUR_HPP

#include <sfge/infrastructure/behaviour.hpp>
#include <sfge/infrastructure/infrastructure_fwd.hpp>

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
		struct AnimFrame
		{
			float			mDuration;
			sf::IntRect		mFrameRect;
			sf::Vector2f	mOrigin;
		};

		typedef std::vector<AnimFrame>		Animation;
		typedef std::shared_ptr<Animation>	AnimationPtr;

		typedef std::map<std::string, AnimationPtr>	AnimationDict;

	private:
		AnimationPtr	ParseAnimation(const sfge::Parameters &animFrameDefs);
		void			EnableCurrentAnim();

	private:
		AnimationDict	mAnimationDict;

		AnimationPtr	mCurrentAnim;
		size_t			mCurrentFrameIndex;
		float			mElapsedTime;
	};
}

#endif
