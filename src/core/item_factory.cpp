#include "platform/i_platform.h"
#include "core/rocket_launcher.h"
#include "core/plasma_gun.h"
#include "core/pistol.h"
#include "core/item.h"
#include "grenade_normal_item.h"
#include "flash_normal_item.h"
#include "shotgun.h"
#include "ion_gun.h"
#include "cloak_normal_item.h"
#include "gatling_gun.h"
#include "gauss_gun.h"
#include "lucky_rocket.h"
#include "blue_grenade_normal_item.h"

ItemFactory::ItemFactory()
{
    Bind<DefaultItem>( AutoId( "default_item" ) );
    SetDefault( AutoId( "default_item" ) );
    Bind( AutoId("plasma_gun"), &CreateItem<PlasmaGun>);
    Bind<Pistol>( AutoId( "pistol" ) );
    Bind<Shotgun>( AutoId( "shotgun" ) );
    Bind<RocketLauncher>(AutoId("rocket_launcher"));
    Bind<IonGun>(AutoId("ion_gun"));
    Bind<GatlingGun>( AutoId( "gatling_gun" ) );
    Bind<GaussGun>( AutoId( "gauss_gun" ) );
    Bind<LuckyRocket>(AutoId("lucky_rocket"));

    Bind<GrenadeNormalItem>(AutoId("grenade_normal_item"));
    Bind<FlashNormalItem>(AutoId("flash_normal_item"));
    Bind<CloakNormalItem>(AutoId("cloak_normal_item"));
    Bind<BlueGrenadeNormalItem>(AutoId("blue_grenade_normal_item"));
}
