#ifndef INCLUDED_ENGINE_MAP_SYSTEM_H
#define INCLUDED_ENGINE_MAP_SYSTEM_H

#include "core/scene.h"
#include "engine/system.h"
#include "map_element.h"
#include "map_element_factory.h"
#include "core/map_load_event.h"

namespace map {

using namespace ::boost::multi_index;
class MapElementHolder
{
public:

    struct MapElementOrderer
    { 
        typedef int32_t result_type;
        result_type operator()(const Opt<MapElement>& mapElement)const
        {
            return mapElement->GetType();
        }
    };
    struct UIDOrderer
    { 
        typedef int32_t result_type;
        result_type operator()(const Opt<MapElement>& mapElement)const
        {
            return mapElement->GetUID();
        }
    };
    typedef multi_index_container<
        Opt<MapElement>,
        indexed_by<
            ordered_non_unique<
                composite_key<
                    Opt<MapElement>,
                    MapElementHolder::MapElementOrderer
                >
            >,
            ordered_non_unique<
                composite_key<
                    Opt<MapElement>,
                    MapElementHolder::UIDOrderer
                >
            >
        >
    > MapElementList_t;
    MapElementList_t mAllMapElements;

};

typedef MapElementHolder::MapElementList_t MapElementList_t;

template<int N>
class MapElementListFilter
{
public:
    typedef MapElementList_t::const_iterator const_iterator;
protected:
    MapElementList_t::const_iterator mI;
    MapElementList_t::const_iterator mE;
    size_t mSize;
public:
    MapElementListFilter(MapElementList_t const& mapElementlist)
    {
        mI=mapElementlist.begin();
        mE=mapElementlist.end();
        mSize=mapElementlist.size();
    }
    const_iterator begin()
    {
        return mI;
    }
    const_iterator end()
    {
        return mE;
    }
    size_t size()
    {
        return mSize;
    }
};

template<>
class MapElementListFilter<0>
{
public:
    typedef MapElementList_t::nth_index<0>::type::const_iterator const_iterator;
protected:
    const_iterator mI;
    const_iterator mE;
    size_t mSize;
public:
    MapElementListFilter(MapElementList_t const& mapElementlist, int32_t mapElementStaticType)
    {
        boost::tie(mI,mE)=mapElementlist.get<0>().equal_range(boost::make_tuple(mapElementStaticType));
        mSize=std::distance(mI,mE);
    }
    const_iterator begin()
    {
        return mI;
    }
    const_iterator end()
    {
        return mE;
    }
    size_t size()
    {
        return mSize;
    }
};
template<>
class MapElementListFilter<1>
{
public:
    typedef MapElementList_t::nth_index<1>::type::const_iterator const_iterator;
protected:
    const_iterator mI;
    const_iterator mE;
    size_t mSize;
public:
    MapElementListFilter(MapElementList_t const& mapElementlist, int32_t mapElementUID)
    {
        boost::tie(mI,mE)=mapElementlist.get<1>().equal_range(boost::make_tuple(mapElementUID));
        mSize=std::distance(mI,mE);
    }
    const_iterator begin()
    {
        return mI;
    }
    const_iterator end()
    {
        return mE;
    }
    size_t size()
    {
        return mSize;
    }
};

class MapSystem : public engine::System
{
public:
    DEFINE_SYSTEM_BASE(MapSystem)
    MapSystem();
    ~MapSystem();
    enum MapElementIndex
    {
        All=0,
        UID=1
    };
    static Opt<MapSystem> Get();
    MapElementList_t& GetMapElementList();
    void RemoveMapElement(int32_t spawnedActorGUID);
protected:
    virtual void Init();
    virtual void Update( double DeltaTime );
    bool AddMapElementFromOneTextureDesc(Json::Value& mapElementDesc);
private:
    void ClearMapElements();
    Scene& mScene;
    MapElementHolder mMapElementHolder;
    MapElementFactory& mMapElementFactory;
    AutoReg mOnMapLoad;
    void OnMapLoad(core::MapLoadEvent const& Evt);

};

} // namespace map

#endif//INCLUDED_ENGINE_MAP_SYSTEM_H

