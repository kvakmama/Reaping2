#ifndef INCLUDED_MAP_JUNGLE_LEVEL_GENERATOR_H
#define INCLUDED_MAP_JUNGLE_LEVEL_GENERATOR_H

#include "platform/i_platform.h"
#include "i_level_generator.h"
#include "room_repo.h"
#include "room_desc.h"
#include "core/opt.h"

namespace map {


class JungleLevelGenerator: public ILevelGenerator
{
public:
    JungleLevelGenerator( int32_t Id );
    virtual void Generate();

private:
    ActorFactory& mActorFactory;
    RoomRepo& mRoomRepo;
    GGraph mGraph;
    typedef std::stack<int32_t> Route_t;
    typedef std::vector<int32_t> Visited_t;
    Visited_t mVisited;
    NeighbourRooms_t GetNeighbourRooms( int32_t roomIndex );
    void LinkRooms( Route_t route );
    void InsertEntrance( glm::vec2 pos, Cell::Entrance entrance );
    struct RouteProperties
    {
        int32_t minLength = 0;
        int32_t endChance = 0;
        int32_t chanceIncrease = 0;
    };
    Route_t CreateRoute( int32_t startIndex, RouteProperties const& properties );
    void CreateMainRoute();
    void CreateSideRoutes();
    void CreateStart();
    void GenerateTerrain();
    void PlaceRooms( glm::vec2 const& startPos );
    Opt<IRoom> PlaceARoom( glm::vec2 const& vec );
    void LogNodes( std::string log, FreeNodes_t const& nodes );
    void GenerateGraph();
};

} // namespace map

#endif//INCLUDED_MAP_JUNGLE_LEVEL_GENERATOR_H

