#include "platform/i_platform.h"
#include "engine/sub_system_factory.h"
#include "engine/sub_system.h"
#include "platform/auto_id.h"
// #include "engine/controllers/player_controller_system.h"
// #include "engine/controllers/random_controller_system.h"
// #include "engine/controllers/target_player_controller_system.h"

using platform::AutoId;
namespace engine {

SubSystemFactory::SubSystemFactory()
{
    Bind( AutoId("default_sub_system"), &CreateSubSystem<DefaultSubSystem> );
    SetDefault( AutoId("default_sub_system") );

//     Bind( AutoId("player_controller_system"), &CreateSystem<PlayerControllerSystem>);
//     Bind( AutoId("random_controller_system"), &CreateSystem<RandomControllerSystem>);
//     Bind( AutoId("target_player_controller_system"), &CreateSystem<TargetPlayerControllerSystem>);

}

} // namespace engine