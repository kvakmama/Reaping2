#include "room_desc.h"
#include "i_room.h"

namespace map {


RoomDesc::RoomDesc()
{

}

void RoomDesc::SetCellCount( int32_t cellCount )
{
    mCellCount = cellCount;
    mCells.clear();
    mCells.resize( mCellCount );
    for (int32_t y = 0; y < mCellCount; ++y)
    {
        mCells[y].resize( mCellCount );
        for (int32_t x = 0; x < mCellCount; ++x)
        {
            mCells[y][x].mDescCoord = glm::vec2( x, y );
        }
    }
}

int32_t RoomDesc::GetCellCount() const
{
    return mCellCount;
}

void RoomDesc::SetCellSize( int32_t cellSize )
{
    mCellSize = cellSize;
}

int32_t RoomDesc::GetCellSize() const
{
    return mCellSize;
}

RoomDesc::Properties_t const& RoomDesc::GetProperties() const
{
    return mPossibleProperties;
}


void RoomDesc::SetProperties( Properties_t const& properties )
{
    mPossibleProperties = properties;
}


bool RoomDesc::HasProperty( RoomProperty::Type prop ) const
{
    return mPossibleProperties.find( prop ) != mPossibleProperties.end();
}

void RoomDesc::ClearProperties()
{
    mPossibleProperties.clear();
}


void RoomDesc::AddProperty( RoomProperty::Type prop )
{
    mPossibleProperties.insert( prop );
}

map::Cell& RoomDesc::GetCell( int32_t x, int32_t y )
{
    return mCells[y][x];
}


map::Cell const& RoomDesc::GetCell( int32_t x, int32_t y ) const
{
    return mCells[y][x];
}


map::Cell& RoomDesc::GetCell( glm::vec2 pos )
{
    return mCells[pos.y][pos.x];
}


map::Cell const& RoomDesc::GetCell( glm::vec2 pos ) const
{
    return mCells[pos.y][pos.x];
}

bool RoomDesc::IsFilled( int32_t x, int32_t y ) const
{
    return GetCell( x, y ).mFilled;
}


bool RoomDesc::IsFilled( glm::vec2 pos ) const
{
    return GetCell( pos ).mFilled;
}

void RoomDesc::ClearCellEntrances()
{
    for (auto& row : mCells)
    {
        for (auto& cell : row)
        {
            cell.mPossibleEntrances.clear();
        }
    }
}

Opt<IRoom> RoomDesc::GetRoom()
{
    return mRoom;
}


void RoomDesc::SetRoom( Opt<IRoom> room )
{
    mRoom = room;
}


void RoomDesc::Load( Json::Value& setters )
{
    mPossibleProperties.clear();
    Json::Value const& properties = setters["plain_properties"];
    if (properties.isArray())
    {
        for (auto& prop : properties)
        {
            AddProperty( RoomProperty::Get()(AutoId( prop.asString() )) );
        }
    }
    int i = 0;
    if (Json::GetInt( setters["cell_count"], i ))
    {
        SetCellCount( i );
    }
    if (Json::GetInt( setters["cell_size"], i ))
    {
        SetCellSize( i );
    }
    auto& cells = setters["cells"];
    if (cells.isArray())
    {
        for (auto& cell : cells)
        {
            int x = 0;
            int y = 0;
            if (Json::GetInt( cell["x"], x ) && Json::GetInt( cell["y"], y ))
            {
                GetCell( x, y ).Load( cell );
            }
        }
    }

}

void Cell::AddEntrance( EntranceType::Type const& entrance )
{
    mPossibleEntrances.insert( entrance );
}


void Cell::SetEntrances( Entrances_t const& entrances )
{
    mPossibleEntrances = entrances;
}


bool Cell::HasEntrance( EntranceType::Type const& entrance ) const
{
    return mPossibleEntrances.find( entrance ) != mPossibleEntrances.end();
}


Cell::Entrances_t const& Cell::GetEntrances() const
{
    return mPossibleEntrances;
}

void Cell::SetFilled( bool filled )
{
    mFilled = filled;
}


bool Cell::IsFilled()
{
    return mFilled;
}


void Cell::Load( Json::Value& setters )
{
    int i = 0;
    if (Json::GetInt( setters["x"], i ))
    {
        mDescCoord.x = i;
    }
    if (Json::GetInt( setters["y"], i ))
    {
        mDescCoord.y = i;
    }
    mPossibleEntrances.clear();
    auto const& entrances = setters["entrances"];
    if (entrances.isArray())
    {
        for (auto& entrance : entrances)
        {
            AddEntrance( EntranceType::Get()(AutoId( entrance.asString() )) );
        }
    }
}

} // namespace map
