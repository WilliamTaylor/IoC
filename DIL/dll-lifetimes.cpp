

#include "dil-lifetimes.h"
#include "dil-container.h"
#include "dil-entry.h"

dil::local_lifetime::local_lifetime()
{
}

dil::local_lifetime::~local_lifetime()
{
    instances.clear();
}

void dil::local_lifetime::deleteInstance(entry * entry)
{
    auto release = entry->getDeleteHandler();

    for (auto& ptr : instances) {
        release(ptr);
    }
}

void * dil::local_lifetime::getInstance(entry * entry)
{
    auto type = entry->getCreateHandler()();
    instances.push_back(type);
    return type;
}


dil::global_lifetime::global_lifetime()
    : instance(nullptr)
{
}

dil::global_lifetime::~global_lifetime()
{
}

void dil::global_lifetime::deleteInstance(entry * entry)
{
    if (instance != nullptr)
    {
        entry->getDeleteHandler()(instance);
        instance = nullptr;
    }
}

void * dil::global_lifetime::getInstance(dil::entry * entry)
{
    if (instance == nullptr)
    {
        instance = entry->getCreateHandler()();
    }

    return instance;
}
