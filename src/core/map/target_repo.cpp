#include "platform/i_platform.h"
#include "target_repo.h"
#include "wall_target.h"
#include "ctf_soldier_spawn_target.h"
#include "../ctf_program_state.h"
#include "pickup_target.h"
#include "flag_spawn_target.h"
#include "soldier_spawn_target.h"

using platform::AutoId;

namespace map {

DefaultTarget const TargetRepo::mDefault = DefaultTarget();

TargetRepo::TargetRepo()
    : Repository<ITarget>( mDefault )
    , mTargetFactory( TargetFactory::Get() )
{
    Init();

}

void TargetRepo::Init()
{
    using boost::filesystem::path;
    const path targets("targets.json");
    Json::Value Root;
    // Read in targets.json
    try
    {
        Filesys& FSys = Filesys::Get();
        AutoFile JsonFile = FSys.Open( targets );
        JsonReader Reader( *JsonFile );
        if ( !Reader.IsValid() )
        {
            throw std::string("Invalid JSON file");
        }
        Root = Reader.GetRoot();
        if (!Root.isArray())
        {
            throw std::string("JSON contain an array as a root element");
        }
    }
    catch( const std::exception& e)
    {
        L1("Exception caught while reading %s: %s\n", targets.filename().string().c_str(), e.what());
        throw;
    }

    // initialize all the targets from the JSON file
    for ( auto const& item : Root )
    {
        try
        {
            std::string target_name;
            if (!Json::GetStr(item["target_name"], target_name ))
            {
                continue;
            }
            std::string name;
            if (!Json::GetStr(item["name"], name ))
            {
                continue;
            }
            int32_t target_autoid = AutoId(target_name);
            int32_t autoid = AutoId( name );
            auto target = mTargetFactory( target_autoid );
            const Json::Value& setters = item["setters"];
            if ( target->Load(setters) )
            {
                mElements.insert( autoid , target.release());
            }
        }
        catch( const std::exception& e )
        {
            L1("Exception caught while initializing targets: %s\n", e.what());
            continue;
        }
    }
}


void DefaultTarget::Update( double DeltaTime )
{

}

DefaultTarget::DefaultTarget()
    : ITarget( -1 )
{

}

void DefaultTarget::PutTarget( glm::vec2 position )
{

}

bool DefaultTarget::Load( const Json::Value& )
{
}

} // namespace map

