#include "platform/i_platform.h"
#include "engine/controllers/player_controller_sub_system.h"
#include "engine/engine.h"
#include "platform/auto_id.h"
#include "input/keyboard.h"
#include "core/player_controller_component.h"
#include "core/i_move_component.h"
#include "core/i_position_component.h"
#include "core/i_inventory_component.h"
#include "core/weapon.h"

namespace engine {

PlayerControllerSubSystem::PlayerControllerSubSystem()
    : mScene( Scene::Get() )
{

}

void PlayerControllerSubSystem::Init()
{
    mKeyboard=Engine::Get().GetSystem<KeyboardSystem>();
    mMouse=Engine::Get().GetSystem<MouseSystem>();
    mMouseMoveId = EventServer<WorldMouseMoveEvent>::Get().Subscribe( boost::bind( &PlayerControllerSubSystem::OnMouseMoveEvent, this, _1 ) );

}

void PlayerControllerSubSystem::Update(Actor& actor, double DeltaTime)
{
    Opt<PlayerControllerComponent> playerControllerC = actor.Get<PlayerControllerComponent>();
    if (!playerControllerC.IsValid()||!playerControllerC->IsEnabled())
    {
        return;
    }
    SetSpeedAndOrientation(actor);
    Shoot(actor);
    SetOrientation(actor);
}

void PlayerControllerSubSystem::OnMouseMoveEvent(const WorldMouseMoveEvent& Event)
{
    mX = Event.Pos.x;
    mY = Event.Pos.y;
}

void PlayerControllerSubSystem::SetSpeedAndOrientation(Actor &actor)
{
    uint32_t mCurrentMovement = 0;
    if( mKeyboard->GetKey(GLFW_KEY_W).State==KeyState::Down)
    {
        mCurrentMovement |= MF_Up;
    }
    if( mKeyboard->GetKey(GLFW_KEY_A).State==KeyState::Down )
    {
        mCurrentMovement |= MF_Left;
    }
    if( mKeyboard->GetKey(GLFW_KEY_S).State==KeyState::Down )
    {
        mCurrentMovement |= MF_Down;
    }
    if( mKeyboard->GetKey(GLFW_KEY_D).State==KeyState::Down )
    {
        mCurrentMovement |= MF_Right;
    }

    int x = ( ( mCurrentMovement & MF_Left ) ? -1 : 0 ) + ( ( mCurrentMovement & MF_Right ) ? 1 : 0 );
    int y = ( ( mCurrentMovement & MF_Up ) ? 1 : 0 ) + ( ( mCurrentMovement & MF_Down ) ? -1 : 0 );
    actor.Get<IMoveComponent>()->SetSpeed( std::max<double>( std::abs( x ), std::abs( y ) )*.35 );

    double Heading = 0;
    static const double pi = boost::math::constants::pi<double>();
    if( x == 0 )
    {
        Heading = ( y < 0 ) ? -pi / 2 : pi / 2;
    }
    else if( y == 0 )
    {
        Heading = ( x < 0 ) ? -pi : 0;
    }
    else if( y > 0 )
    {
        Heading = ( x < 0 ) ? pi * 0.75 : pi / 4;
    }
    else
    {
        Heading = ( x < 0 ) ? pi * 1.25 : pi * 1.75;
    }
    actor.Get<IMoveComponent>()->SetHeading( Heading );
}

void PlayerControllerSubSystem::Shoot(Actor &actor)
{
    Opt<IInventoryComponent> inventoryC=actor.Get<IInventoryComponent>();
    BOOST_ASSERT(inventoryC.IsValid());
    Opt<Weapon> weapon=inventoryC->GetSelectedWeapon();
    if (!weapon.IsValid())
    {
        return;
    }

    if (mMouse->IsButtonPressed( MouseSystem::Button_Left ))
    {
        weapon->SetShoot(true);
        weapon->SetShootAlt(false);
    }
    else if (mMouse->IsButtonPressed( MouseSystem::Button_Right ))
    {
        weapon->SetShoot(false);
        weapon->SetShootAlt(true);
    }
    else
    {
        weapon->SetShoot(false);
        weapon->SetShootAlt(false);
    }
}

void PlayerControllerSubSystem::SetOrientation(Actor &actor)
{
    Opt<IPositionComponent> actorPositionC = actor.Get<IPositionComponent>();
    double Rot = atan2( mY - actorPositionC->GetY(), mX - actorPositionC->GetX() );
    actorPositionC->SetOrientation( Rot );
}

} // namespace engine
