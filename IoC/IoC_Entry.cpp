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

ioc::IoC_Entry::IoC_Entry() 
  : interface_info(nullptr),
	mapping_info(nullptr),
	lifetime(nullptr)
{
}

ioc::IoC_Entry::~IoC_Entry()
{
	deleteIfAllocated(interface_info);
	deleteIfAllocated(mapping_info);
	
	lifetime->deleteInstance(this);
	
	delete lifetime;
}

std::function<void(ioc::IoC_Type)> ioc::IoC_Entry::getDeleteHandler()
{
	return delete_handler;
}

void ioc::IoC_Entry::setCreateHandler(std::function<ioc::IoC_Type()> function)
{
	this->create_handler = function;
}

void ioc::IoC_Entry::setDeleteHandler(std::function<void(ioc::IoC_Type)> function)
{
	this->delete_handler = function;
}

void ioc::IoC_Entry::setTypeInfo(const std::type_info& interface, const std::type_info& mapping)
{
	interface_info = deleteIfAllocated(interface_info);
	mapping_info = deleteIfAllocated(mapping_info);

	this->interface_info = new std::type_index(interface);
	this->mapping_info = new std::type_index(mapping);
}

void ioc::IoC_Entry::setLifetime(IoC_Lifetime * lifetime)
{
	this->lifetime = lifetime;
}

std::type_index * ioc::IoC_Entry::deleteIfAllocated(std::type_index * type_index)
{
	if (type_index != nullptr)
	{
		delete type_index;
	}

	return nullptr;
}

std::function<ioc::IoC_Type()> ioc::IoC_Entry::getCreateHandler()
{
	return create_handler;
}

ioc::IoC_Type ioc::IoC_Entry::getInstance()
{
	return lifetime->getInstance(this);
}

size_t ioc::IoC_Entry::getInterfaceHashCode()
{
	if (interface_info == nullptr)
	{
		throw std::exception("Couldnt get hash code due to null typeinfo");
	}

	return interface_info->hash_code();
}

size_t ioc::IoC_Entry::getMappingHashCode()
{
	if (mapping_info == nullptr)
	{
		throw std::exception("Couldnt get hash code due to null typeinfo");
	}

	return mapping_info->hash_code();
}
