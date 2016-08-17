#include "dil-lifetimes.h"
#include "dil-entry.h"

dil::local_lifetime::local_lifetime()
{
}

dil::local_lifetime::~local_lifetime()
{
    allocated_objects.clear();
}

void dil::local_lifetime::release(entry * entry)
{
    const auto deleteClosure = entry->getDeleteClosure();

    for (auto& ptr : allocated_objects)
    {
        deleteClosure(ptr);
    }
}

dil::raw_pointer dil::local_lifetime::acquire(entry * entry)
{
    const auto createClosure = entry->getCreateClosure();

    if(createClosure != nullptr)
    {
        const auto newObject = createClosure();
        allocated_objects.push_back(newObject);
        return newObject;
    }

    return nullptr;
}


dil::global_lifetime::global_lifetime()
    : object(nullptr)
{
}

dil::global_lifetime::~global_lifetime()
{
}

void dil::global_lifetime::release(entry * entry)
{
    if (object != nullptr)
    {
        const auto deleteClosure = entry->getDeleteClosure();

        if(deleteClosure != nullptr)
        {
            deleteClosure(object);
            object = nullptr;
        }
    }
}

dil::raw_pointer dil::global_lifetime::acquire(dil::entry * entry)
{
    if (object == nullptr)
    {
        const auto createClosure = entry->getCreateClosure();

        if(createClosure != nullptr)
        {
            object = createClosure();
        }
    }

    return object;
}
