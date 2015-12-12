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
#include "IoC_LocalLifetime.h"
#include "IoC_Exceptions.h"
#include "IoC_Lifetime.h"
#include "IoC_Header.h"
#include "IoC_Entry.h"

namespace ioc {
	class IOC_EXPORTS IoC_Container {
		private:
			std::map<size_t, IoC_Entry *> mappings;
		public:
			IoC_Container();
			virtual ~IoC_Container();

			template<typename Dependency, typename... Dependencies>
			IoC_Container * query(Dependency ** first, Dependencies... args);
			
			template<typename Dependency>
			IoC_Container * query(Dependency ** dependency);

			template<typename Interface, typename Mapping>
			IoC_Container * supply(IoC_Lifetime * lifespan = new IoC_LocalLifetime());

			template<typename Interface>
			bool supplied(size_t * hashOutput = nullptr);
			
			template<typename Interface>
			Interface * fetch();
		private:
			size_t hash(const std::string& v);
	};

	template<typename Dependency>
	IoC_Container * ioc::IoC_Container::query(Dependency ** dependency) {
		IsInterface<Dependency>();
		try {
			auto object = fetch<Dependency>();
			(*dependency) = object;
		} catch (IoC_InterfaceException e) {
			(*dependency) = nullptr;
		}

		return this;
	}

	template<typename Interface, typename Mapping>
	IoC_Container * ioc::IoC_Container::supply(IoC_Lifetime * scope) {
		Implements<Interface, Mapping>();
		
		auto iocEntry = new IoC_Entry();
		iocEntry->setTypeInfo(typeid(Interface), typeid(Mapping));
		iocEntry->setDeleteHandler([&](IoC_Type pointer){ delete static_cast<Mapping *>(pointer); });
		iocEntry->setCreateHandler([&](){ return static_cast<IoC_Type>(new Mapping(this)); });
		iocEntry->setLifetime(scope);

		size_t hash = 0;

		if (supplied<Interface>(&hash))
		{
			delete mappings[hash];
			mappings[hash] = nullptr;
		}

		mappings[hash] = iocEntry;
		return this;
	}

	template<typename Interface>
	bool ioc::IoC_Container::supplied(size_t * hashOutput) {
		IsInterface<Interface>();

		auto hash = typeid(Interface).hash_code();

		if (hashOutput != nullptr)
		{
			(*hashOutput) = hash;
		}

		return mappings.count(hash) != 0;
	}

	template<typename Interface>
	Interface * ioc::IoC_Container::fetch() {
		IsInterface<Interface>();

		const auto& info = typeid(Interface);
		auto hash = info.hash_code();

		if (mappings.count(hash) > 0)
		{
			return static_cast<Interface *>(mappings[hash]->getInstance());
		}
		else
		{
			throw IoC_InterfaceException(info, hash);
		}

		return nullptr;
	}

	template<typename Dependency, typename... Dependencies>
	IoC_Container * ioc::IoC_Container::query(Dependency ** first, Dependencies... args) {
		IsInterface<Dependency>();
		return query(first)->query(args...);
	}
}
