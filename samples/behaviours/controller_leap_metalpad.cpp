#include "controller_leap_metalpad.hpp"

#include <iostream>

#include <boost/optional.hpp>

#include <Leap.h>

#include <sfge/infrastructure/builtin_attributes.hpp>
#include <sfge/infrastructure/data_store.hpp>
#include <sfge/graphics/graphic_system.hpp>

using namespace sfge;

struct ControllerLeapMetalPad::Impl : private Leap::Listener
{
    Leap::Controller m_Controller;
    boost::optional<Leap::Vector> m_LastNormalizedPos;

    Impl()
    {
        m_Controller.addListener(*this);
    }

    ~Impl()
    {
        m_Controller.removeListener(*this);
    }
    
    virtual void onInit         (const Leap::Controller&) { std::cout << "[LEAP] Initialized" << std::endl; }
    virtual void onConnect      (const Leap::Controller&) { std::cout << "[LEAP] Device connected." << std::endl; }
    virtual void onDisconnect   (const Leap::Controller&) { std::cout << "[LEAP] Device disconnected" << std::endl; }
    virtual void onExit         (const Leap::Controller&) { std::cout << "[LEAP] Listener detached" << std::endl; }
    virtual void onFrame        (const Leap::Controller&)
    {
        const Leap::Frame frame(m_Controller.frame(0));
        const Leap::Hand hand(frame.hands().rightmost());
        if (!hand.isValid())
        {
            m_LastNormalizedPos.reset();
            return;
        }

        const Leap::Vector pos(hand.palmPosition());
        m_LastNormalizedPos = frame.interactionBox().normalizePoint(pos);
    }
};

ControllerLeapMetalPad::ControllerLeapMetalPad(GameObjectWeakPtr owner)
	: Behaviour(owner), m_Impl(new Impl)
{
}

void ControllerLeapMetalPad::OnUpdate(float /*dt*/)
{
    Attribute<sf::Color> col = GetAttribute<sf::Color>(AK_Color);
    if (!m_Impl->m_LastNormalizedPos.is_initialized())
    {
        col = sf::Color::White;
        return;
    }

    col->r = static_cast<sf::Uint8>(255 * m_Impl->m_LastNormalizedPos->x);
    col->g = static_cast<sf::Uint8>(255 * m_Impl->m_LastNormalizedPos->y);
    col->b = static_cast<sf::Uint8>(255 * m_Impl->m_LastNormalizedPos->z);
    
	Attribute<sf::Vector2f> pos = GetAttribute<sf::Vector2f>(AK_Position);
	if(pos.IsValid())
    {
        const sf::Vector2u renderArea(GraphicSystem::getSingleton().GetCurrentRenderTarget().getSize());
        pos->x = m_Impl->m_LastNormalizedPos->x * renderArea.x;
		pos->y = m_Impl->m_LastNormalizedPos->z * renderArea.y;
    }


    // Get mouse coord in our render window
    /*const sf::Vector2i newPos = sf::Mouse::getPosition(GraphicSystem::getSingleton().GetCurrentRenderWindow());

    if (newPos != mPrevMousePos)
	{
		Attribute<Vector2f> pos = GetAttribute<Vector2f>(AK_Position);
		if(pos.IsValid())
        {
            pos->x = static_cast<float>(newPos.x);
		    pos->y = static_cast<float>(newPos.y);
        }

        mPrevMousePos = newPos;
	}

	const bool mouseLeftPressed	= sf::Mouse::isButtonPressed(sf::Mouse::Left);
	if (!mPrevLButtonState.is_initialized() || mouseLeftPressed != mPrevLButtonState)
	{
		Attribute<Color> col = GetAttribute<Color>(AK_Color);
		if (col.IsValid())
		    col = mouseLeftPressed ? Color::Blue : Color::Red;

		mPrevLButtonState = mouseLeftPressed;
	}*/
}
