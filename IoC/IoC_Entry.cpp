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

ioc::IoC_Entry::IoC_Entry(IoC_Container * container, IoC_Lifetime * lifetime)
  : parentContainer(container),
	lifetime(lifetime),
	interfaceInfo(nullptr),
	interfaceName(""),
	mappingInfo(nullptr),
	mappingName("")
{	
	system_clock::time_point clock = system_clock::now();
	system_clock::duration duraction = clock.time_since_epoch();
	entryID = duraction.count();
}

ioc::IoC_Entry::~IoC_Entry()
{	
	lifetime->deleteInstance(this);

	delete interfaceInfo;
	delete mappingInfo;
	delete lifetime;
}

std::string ioc::IoC_Entry::getInterfaceName()
{
	return interfaceName;
}

std::string ioc::IoC_Entry::getMappingName()
{
	return mappingName;
}


ioc::IoC_ID ioc::IoC_Entry::getID()
{ 
	return entryID; 
}

std::function<void(ioc::IoC_Type)> ioc::IoC_Entry::getDeleteHandler()
{
	return deleteHandler;
}

std::function<ioc::IoC_Type()> ioc::IoC_Entry::getCreateHandler()
{
	return createHandler;
}

ioc::IoC_Type ioc::IoC_Entry::getInstance()
{
	return lifetime->getInstance(this);
}

size_t ioc::IoC_Entry::getInterfaceHashCode()
{
	if (interfaceInfo == nullptr)
	{
		throw std::exception("Couldnt get hash code due to null typeinfo");
	}

	return interfaceInfo->hash_code();
}

size_t ioc::IoC_Entry::getMappingHashCode()
{
	if (mappingInfo == nullptr)
	{
		throw std::exception("Couldnt get hash code due to null typeinfo");
	}

	return mappingInfo->hash_code();
}
