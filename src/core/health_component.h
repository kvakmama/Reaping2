#ifndef INCLUDED_CORE_HEALTH_COMPONENT_H
#define INCLUDED_CORE_HEALTH_COMPONENT_H

#include "core/i_health_component.h"
#include "core/property_loader.h"

class HealthComponent : public IHealthComponent
{
public:
    virtual void Update( double Seconds );
    virtual int32_t const& GetHP()const;
    virtual void SetHP( int32_t Hp );
    virtual bool IsAlive()const;
    virtual double GetTimeOfDeath()const;
    virtual bool NeedDelete()const;
protected:
    HealthComponent();
    friend class ComponentFactory;

    int32_t mHP;
    bool mAlive;
    double mTimeOfDeath;
    bool mNeedDelete;
};

class HealthComponentLoader: public ComponentLoader<HealthComponent>
{
    virtual void BindValues();
protected:
    HealthComponentLoader();
    friend class ComponentLoaderFactory;
};

#endif//INCLUDED_CORE_HEALTH_COMPONENT_H