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


#include "IoC_GlobalLifetime.h"
#include "IoC_LocalLifetime.h"
#include "IoC_Entry.h"

using namespace std::chrono;

ioc::IoC_Entry::IoC_Entry(IoC_Container * container, std::unique_ptr<IoC_Lifetime> life)
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

ioc::IoC_Entry::~IoC_Entry()
{	
    lifetime->deleteInstance(this);

    delete interfaceInfo;
    delete mappingInfo;
}

std::string ioc::IoC_Entry::getInterfaceName() const
{
    return interfaceName;
}

std::string ioc::IoC_Entry::getMappingName() const
{
    return mappingName;
}

long long ioc::IoC_Entry::getID() const
{ 
    return entryID; 
}

std::function<void(void *)> ioc::IoC_Entry::getDeleteHandler() const
{
    return deleteHandler;
}

std::function<void *()> ioc::IoC_Entry::getCreateHandler() const
{
    return createHandler;
}

void * ioc::IoC_Entry::getInstance()
{
    return lifetime->getInstance(this);
}

size_t ioc::IoC_Entry::getInterfaceHashCode() const
{
    if (interfaceInfo == nullptr)
    {
        throw std::exception("Couldnt get hash code due to null typeinfo");
    }

    return interfaceInfo->hash_code();
}

size_t ioc::IoC_Entry::getMappingHashCode() const
{
    if (mappingInfo == nullptr)
    {
        throw std::exception("Couldnt get hash code due to null typeinfo");
    }

    return mappingInfo->hash_code();
}
