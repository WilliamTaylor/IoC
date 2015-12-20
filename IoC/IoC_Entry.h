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

#pragma once

#include "IoC_GenericConstraints.h"
#include "IoC_Header.h"

namespace ioc {
	class IoC_Container;
	class IoC_Lifetime;

	class IOC_EXPORTS IoC_Entry
	{
	private:
		std::function<void(IoC_Type)> deleteHandler;
		std::function<IoC_Type()> createHandler;
		std::type_index * interfaceInfo;
		std::type_index * mappingInfo;
		std::string interfaceName;
		std::string mappingName;
	private:
		IoC_Container * parentContainer;
		IoC_Lifetime * lifetime;
		IoC_ID entryID;
	public:
		IoC_Entry(IoC_Container * container, IoC_Lifetime * lifetime);
		~IoC_Entry();

		template<typename Class> 
		IoC_Entry * setDeleteHandler();

		template<typename Class> 
		IoC_Entry * setCreateHandler();

		template<typename Interface, typename Mapping>
		IoC_Entry * setTypeInformation();
	public:
		std::function<void(IoC_Type)> getDeleteHandler();
		std::function<IoC_Type()> getCreateHandler();
		std::string getInterfaceName();
		std::string getMappingName();

		size_t getInterfaceHashCode();
		size_t getMappingHashCode();

		IoC_Type getInstance();
		IoC_ID getID();
	};

	template<typename Interface, typename Mapping>
	IoC_Entry * IoC_Entry::setTypeInformation() {
		Implements<Interface, Mapping>();
		if (interfaceInfo == nullptr && mappingInfo == nullptr) {
			interfaceInfo = new std::type_index(typeid(Interface));
			interfaceName = interfaceInfo->name();

			mappingInfo = new std::type_index(typeid(Mapping));
			mappingName = mappingInfo->name();
		}

		return this;
	}
	
	template<typename Class>
	IoC_Entry * IoC_Entry::setDeleteHandler() {
		this->deleteHandler = [&](IoC_Type pointer) {
			IsClass<Class>();
			if (pointer != nullptr) {
				delete static_cast<Class *>(pointer);
				pointer = nullptr;
			}
		};

		return this;
	}

	template<typename Class>
	IoC_Entry * IoC_Entry::setCreateHandler() {
		this->createHandler = [&]() {
			IsClass<Class>();
			return static_cast<IoC_Type>(new Class(this->parentContainer));
		};

		return this;
	}
}
