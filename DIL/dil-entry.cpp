#include "dil-lifetimes.h"
#include "dil-entry.h"

using namespace std::chrono;

dil::entry::entry(dil::container * cont, std::unique_ptr<dil::lifetime> life) :
    implementationType(nullptr),
    interfaceType(nullptr)
{	   
    const auto clock = system_clock::now();
    const auto duration = clock.time_since_epoch();

    timeRegistered = duration.count();
    lifetimeScope = move(life);
    container = cont;
}

dil::entry::~entry()
{	
    lifetimeScope->release(this);

    delete implementationType;
    delete interfaceType;
}

long long dil::entry::getTimeRegisted() const
{ 
    return timeRegistered; 
}

std::function<void(void *)> dil::entry::getDeleteClosure() const
{
    return deleteClosure;
}

std::function<void *()> dil::entry::getCreateClosure() const
{
    return createClosure;
}

void * dil::entry::ptr()
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
