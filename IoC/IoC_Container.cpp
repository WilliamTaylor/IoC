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

#include "IoC_Container.h"

ioc::IoC_Container::IoC_Container()
{
}

ioc::IoC_Container::~IoC_Container()
{
	using element = std::pair<size_t, IoC_Entry *>;
	auto predicate = [](element& a, element& b) {
		return a.second->getID() < b.second->getID();
	};

	std::vector<std::pair<size_t, IoC_Entry *>> entries;
	std::copy(mappings.begin(), mappings.end(), std::back_inserter(entries));
	std::sort(entries.begin(), entries.end(), predicate);

	for (auto& entry : entries) {
		delete entry.second;
		entry.second = nullptr;
	}

	mappings.clear();
	entries.clear();
}

size_t ioc::IoC_Container::hash(const std::string& v)
{
	return std::hash<std::string>()(v);
}
