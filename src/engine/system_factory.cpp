#include "platform/i_platform.h"
#include "engine/system_factory.h"
#include "engine/system.h"
#include "engine/collision_system.h"
#include "platform/auto_id.h"
#include "input/keyboard.h"
#include "engine/controllers/player_controller_sub_system.h"
#include "engine/controllers/random_controller_sub_system.h"
#include "engine/controllers/target_player_controller_sub_system.h"
#include "engine/controllers/controller_system.h"
#include "engine/items/inventory_system.h"
#include "engine/drop_on_death_system.h"
#include "engine/health_system.h"
#include "engine/remove_on_death_system.h"
#include "engine/explode_on_death_system.h"
#include "engine/fade_out_system.h"
#include "engine/move_system.h"
#include "engine/acceleration_system.h"
#include "input/mouse.h"
#include "main/window.h"
#include "platform/timer.h"
#include "engine/frame_counter_system.h"
#include "render/renderer.h"
#include "network/server_system.h"
#include "network/client_system.h"
#include "network/message_handler_sub_system_holder.h"
#include "network/lifecycle_sender_system.h"
#include "network/position_message_sender_system.h"
#include "network/move_message_sender_system.h"
#include "network/player_controller_message.h"
#include "network/create_actor_message_sender_system.h"
#include "network/damage_taken_message.h"
#include "network/orientation_message.h"
#include "network/heading_message.h"
#include "network/pickup_message.h"
#include "network/ping_message.h"
#include "network/revive_message.h"
#include "explosion_system.h"
#include "stop_on_death_system.h"
#include "target_holder_system.h"
#include "removed_actors_system.h"
#include "listen_child_death_system.h"
#include "notify_parent_on_death_system.h"
#include "network/flash_message.h"
#include "engine/buffs_engine/buff_holder_system.h"
#include "network/heal_taken_message.h"
#include "soldier_properties_system.h"
#include "network/soldier_properties_message.h"
#include "network/client_datas_message.h"
#include "network/health_message.h"
#include "network/accuracy_message.h"
#include "local_system.h"
#include "soldier_spawn_system.h"
#include "network/set_ownership_message.h"


using platform::AutoId;
namespace engine {

SystemFactory::SystemFactory()
{
    Bind( AutoId("default_system"), &CreateSystem<DefaultSystem> );
    SetDefault( AutoId("default_system") );

    Bind( AutoId("window_system"), &CreateSystem<WindowSystem>);
    Bind( AutoId("timer_server_system"), &CreateSystem<TimerServerSystem>);
    Bind( AutoId("frame_counter_system"), &CreateSystem<FrameCounterSystem>);
    Bind( AutoId("renderer_system"), &CreateSystem<RendererSystem>);

    Bind( AutoId("collision_system"), &CreateSystem<CollisionSystem>);
    Bind( AutoId("keyboard_system"), &CreateSystem<KeyboardSystem>);
    Bind( AutoId("mouse_system"), &CreateSystem<MouseSystem>);
    Bind( AutoId("controller_system"), &CreateSystem<ControllerSystem>);
    Bind( AutoId("inventory_system"), &CreateSystem<InventorySystem>);

    Bind( AutoId("drop_on_death_system"), &CreateSystem<DropOnDeathSystem>);
    Bind( AutoId("remove_on_death_system"), &CreateSystem<RemoveOnDeathSystem>);
    Bind( AutoId("explode_on_death_system"), &CreateSystem<ExplodeOnDeathSystem>);
    Bind( AutoId("stop_on_death_system"), &CreateSystem<StopOnDeathSystem>);

    Bind( AutoId("notify_parent_on_death_system"), &CreateSystem<NotifyParentOnDeathSystem>);

    Bind( AutoId("listen_child_death_system"), &CreateSystem<ListenChildDeathSystem>);

    Bind( AutoId("health_system"), &CreateSystem<HealthSystem>);
    Bind( AutoId("fade_out_system"), &CreateSystem<FadeOutSystem>);
    Bind( AutoId("move_system"), &CreateSystem<MoveSystem>);
    Bind( AutoId("acceleration_system"), &CreateSystem<AccelerationSystem>);
    Bind( AutoId("explosion_system"), &CreateSystem<ExplosionSystem>);

    Bind( AutoId("server_system"), &CreateSystem<network::ServerSystem>);
    Bind( AutoId("client_system"), &CreateSystem<network::ClientSystem>);
    Bind( AutoId("local_system"), &CreateSystem<LocalSystem>);

    Bind( AutoId("soldier_properties_system"), &CreateSystem<SoldierPropertiesSystem>);
    Bind( AutoId("soldier_spawn_system"), &CreateSystem<SoldierSpawnSystem>);

    Bind( AutoId("lifecycle_sender_system"), &CreateSystem<network::LifecycleSenderSystem>);
    Bind( AutoId("message_handler_sub_system_holder"), &CreateSystem<network::MessageHandlerSubSystemHolder>);
    Bind( AutoId("position_message_sender_system"), &CreateSystem<network::PositionMessageSenderSystem>);
    Bind( AutoId("move_message_sender_system"), &CreateSystem<network::MoveMessageSenderSystem>);
    Bind( AutoId("player_controller_message_sender_system"), &CreateSystem<network::PlayerControllerMessageSenderSystem>);
    Bind( AutoId("create_actor_message_sender_system"), &CreateSystem<network::CreateActorMessageSenderSystem>);
    Bind( AutoId("damage_taken_message_sender_system"), &CreateSystem<network::DamageTakenMessageSenderSystem>);
    Bind( AutoId("heal_taken_message_sender_system"), &CreateSystem<network::HealTakenMessageSenderSystem>);
    Bind( AutoId("orientation_message_sender_system"), &CreateSystem<network::OrientationMessageSenderSystem>);
    Bind( AutoId("heading_message_sender_system"), &CreateSystem<network::HeadingMessageSenderSystem>);
    Bind( AutoId("pickup_message_sender_system"), &CreateSystem<network::PickupMessageSenderSystem>);
    Bind( AutoId("ping_message_sender_system"), &CreateSystem<network::PingMessageSenderSystem>);
    Bind( AutoId("revive_message_sender_system"), &CreateSystem<network::ReviveMessageSenderSystem>);
    Bind( AutoId("flash_message_sender_system"), &CreateSystem<network::FlashMessageSenderSystem>);
    Bind( AutoId("soldier_properties_message_sender_system"), &CreateSystem<network::SoldierPropertiesMessageSenderSystem>);
    Bind( AutoId("client_datas_message_sender_system"), &CreateSystem<network::ClientDatasMessageSenderSystem>);
    Bind( AutoId("health_message_sender_system"), &CreateSystem<network::HealthMessageSenderSystem>);
    Bind( AutoId("accuracy_message_sender_system"), &CreateSystem<network::AccuracyMessageSenderSystem>);
    Bind( AutoId("set_ownership_message_sender_system"), &CreateSystem<network::SetOwnershipMessageSenderSystem>);

    Bind( AutoId("target_holder_system"), &CreateSystem<TargetHolderSystem>);
    Bind( AutoId("removed_actors_system"), &CreateSystem<RemovedActorsSystem>);

    Bind( AutoId("buff_holder_system"), &CreateSystem<BuffHolderSystem>);
    
}

} // namespace engine
