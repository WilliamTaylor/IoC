#include "dil-lifetimes.h"
#include "dil-entry.h"

using namespace std::chrono;

dil::entry::entry(dil::container * cont, std::unique_ptr<dil::lifetime> life) :
    implementationType(nullptr),
    interfaceType(nullptr)
{	   
    const auto systemTime = system_clock::now();
    const auto duration = systemTime.time_since_epoch();

    timeCreated = duration.count();
    lifetimeScope = move(life);
    container = cont;
}

dil::entry::~entry()
{	
    lifetimeScope->release(this);

    if(implementationType && interfaceType)
    {
        delete implementationType;
        delete interfaceType;
    }
}

dil::timestamp dil::entry::getTimeRegisted() const
{ 
    return timeCreated; 
}

dil::delete_closure dil::entry::getDeleteClosure() const
{
    return deleteClosure;
}

dil::create_closure dil::entry::getCreateClosure() const
{
    return createClosure;
}

dil::raw_pointer dil::entry::ptr()
{
    return lifetimeScope->acquire(this);
}

const std::type_index& dil::entry::getInterfaceType() const
{
    if (interfaceType == nullptr)
    {
        throw std::exception("No type info for entry!");
    }

    return *interfaceType;
}

const std::type_index& dil::entry::getImplementationType() const
{
    if (implementationType == nullptr)
    {
        throw std::exception("No type info for entry!");
    }

    return *implementationType;
}
