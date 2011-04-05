#include "sfge/behaviours/sprite_animation_behaviour.hpp"

#include "sfge/infrastructure/builtin_attributes.hpp"
#include "sfge/infrastructure/game_object.hpp"
#include "sfge/utilities/exception_str.hpp"

#include <algorithm>

using namespace boost;
using namespace sf;
using namespace std;

namespace sfge
{

SpriteAnimationBehaviour::SpriteAnimationBehaviour(GameObjectWeakPtr owner)
	: Behaviour(owner), mElapsedTime(0.f), mCurrentFrameIndex(0)
{
}

void SpriteAnimationBehaviour::OnParamsReceived(const Parameters &params)
{
	// Empty Parameters used as default return value
	const Parameters defParams;

	const Parameters &animsBlock = params.get_child("anims", defParams);
	if (animsBlock.empty())
		return;

	for_each(animsBlock.begin(), animsBlock.end(),
		[&] (const Parameters::value_type &animBlock)
		{
			// Extract animation's name
			const Parameters &animParams = animBlock.second;
			const std::string &name = animParams.get("animName", "");
			if (name.empty())
				throw ExceptionStr("Anonymous animation found!");
			if (mAnimationDict.find(name) != mAnimationDict.end())
				throw ExceptionStr("Animation '" + name + "' already declared");

			// Parse animation definition (frames composing the animation)
			const Parameters &animFrames = animParams.get_child("animFrames", defParams);
			if (animFrames.empty())
				mAnimationDict.insert(make_pair(name, nullptr));
			else
				mAnimationDict.insert(make_pair(name, ParseAnimation(animFrames)));
		} );

	if (mAnimationDict.size() > 0)
	{
		mCurrentAnim		= mAnimationDict.begin()->second;
		mElapsedTime		= 0.f;
		mCurrentFrameIndex	= 0;

		EnableCurrentAnim();
	}
}

SpriteAnimationBehaviour::AnimationPtr SpriteAnimationBehaviour::ParseAnimation(const sfge::Parameters &animFrameDefs)
{
	AnimationPtr animFrames(new Animation());
	if (animFrameDefs.empty())
		return animFrames;
	
	for_each(animFrameDefs.begin(), animFrameDefs.end(),
		[&] (const Parameters::value_type &animFrameDef)
		{
			if (animFrameDef.second.empty())
				throw ExceptionStr("Empty animation frame found");

			const float duration	= animFrameDef.second.get("duration", 0.f);
			const Parameters &rect	= animFrameDef.second.get_child("rect", Parameters());
			const float ox			= animFrameDef.second.get("ox", 0.f);
			const float oy			= animFrameDef.second.get("oy", 0.f);

			if (rect.empty())
				throw ExceptionStr("Animation frame without \"rect\" are forbidden");
			if (rect.size() != 4)
				throw ExceptionStr("\"rect\" attributes of animation frame must have 4 int components");

			Parameters::const_assoc_iterator rectIt = rect.ordered_begin();

			AnimFrame frame;
			frame.mDuration			= duration;
			frame.mOrigin.x			= ox;
			frame.mOrigin.y			= oy;
			frame.mFrameRect.Left	= rectIt->second.get_value<int>(0);		++rectIt;
			frame.mFrameRect.Top	= rectIt->second.get_value<int>(0);		++rectIt;
			frame.mFrameRect.Width	= rectIt->second.get_value<int>(0);		++rectIt;
			frame.mFrameRect.Height	= rectIt->second.get_value<int>(0);

			animFrames->push_back(frame);
		} );

	return animFrames;
}

void SpriteAnimationBehaviour::OnUpdate(float dt)
{
	if (!mCurrentAnim || mCurrentAnim->empty())
		return;

	const AnimFrame &currFrame = mCurrentAnim->at(mCurrentFrameIndex);

	if (mElapsedTime < currFrame.mDuration)
	{
		mElapsedTime += dt;
		return;
	}

	// Go to next frame
	mCurrentFrameIndex++;

	// TODO cycle mode!
	if (mCurrentFrameIndex == mCurrentAnim->size())
		mCurrentFrameIndex = 0;
	mElapsedTime = 0.f;

	EnableCurrentAnim();
}

void SpriteAnimationBehaviour::EnableCurrentAnim()
{
	const AnimFrame &currFrame = mCurrentAnim->at(mCurrentFrameIndex);

	Attribute<IntRect> region = GetAttribute<IntRect>(AK_SpriteRegion);
	assert(region.IsValid());
	region = currFrame.mFrameRect;

	Attribute<Vector2f> origin = GetAttribute<Vector2f>(AK_Origin);
	assert(origin.IsValid());
	origin = currFrame.mOrigin;
}

}
