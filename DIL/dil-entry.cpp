/***
 * 
 * Copyright 10/12/2015 William wi11berto@yahoo.co.uk
 *  
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *  
 *    http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
***/


#include "dil-lifetimes.h"
#include "dil-entry.h"

using namespace std::chrono;

dil::entry::entry(dil::container * container, std::unique_ptr<dil::lifetime> life)
  : interfaceInfo(nullptr), 
    interfaceName(""),
    mappingInfo(nullptr), 
    mappingName("")
{	
    this->container = container;
    this->lifetime = move(life);

    auto clock = system_clock::now();
    auto duration = clock.time_since_epoch();
    entryID = duration.count();
}

dil::entry::~entry()
{	
    lifetime->deleteInstance(this);

    delete interfaceInfo;
    delete mappingInfo;
}

std::string dil::entry::getInterfaceName() const
{
    return interfaceName;
}

std::string dil::entry::getMappingName() const
{
    return mappingName;
}

long long dil::entry::getID() const
{ 
    return entryID; 
}

std::function<void(void *)> dil::entry::getDeleteHandler() const
{
    return deleteHandler;
}

std::function<void *()> dil::entry::getCreateHandler() const
{
    return createHandler;
}

void * dil::entry::getInstance()
{
    return lifetime->getInstance(this);
}

size_t dil::entry::getInterfaceHashCode() const
{
    if (interfaceInfo == nullptr)
    {
        throw std::exception("Couldnt get hash code due to null typeinfo");
    }

    return interfaceInfo->hash_code();
}

size_t dil::entry::getMappingHashCode() const
{
    if (mappingInfo == nullptr)
    {
        throw std::exception("Couldnt get hash code due to null typeinfo");
    }

    return mappingInfo->hash_code();
}
