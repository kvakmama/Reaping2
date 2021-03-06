#include "platform/i_platform.h"
#include "network/position_message_handler_sub_system.h"
#include "core/opt.h"
#include "position_message.h"
#include "core/i_position_component.h"
namespace network {

PositionMessageHandlerSubSystem::PositionMessageHandlerSubSystem()
    : MessageHandlerSubSystem()
{

}

void PositionMessageHandlerSubSystem::Init()
{

}

void PositionMessageHandlerSubSystem::Execute( Message const& message )
{
    PositionMessage const& msg = static_cast<PositionMessage const&>( message );
    //        L1("executing position: %d \n",msg.mSenderId );
    if ( mProgramState.mMode == ProgramState::Server
         || ( mProgramState.mMode == ProgramState::Client && msg.mActorGUID != mProgramState.mControlledActorGUID ) )
    {
        Opt<Actor> actor = mScene.GetActor( msg.mActorGUID );
        if ( !actor.IsValid() )
        {
            L1( "cannot find actor with GUID: (that is not possible) %d \n", msg.mActorGUID );
            return;
        }

        Opt<IPositionComponent> positionC( actor->Get<IPositionComponent>() );
        if ( !positionC.IsValid() )
        {
            L1( "position is called on an actor that has no position_component \n" );
            return;
        }
        positionC->SetX( msg.mX / PRECISION );
        positionC->SetY( msg.mY / PRECISION );
    }
}

} // namespace network

