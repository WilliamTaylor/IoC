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
	: state(Unlocked)
{
}

ioc::IoC_Container::IoC_Container(ioc::IoC_Container&& container)
	: state(Unlocked)
{
	for(auto& e : container.mappings)
	{
		this->mappings[e.first] = move(e.second);
	}

	container.state = Locked;
	container.mappings.clear();
}

void ioc::IoC_Container::unlock()
{
	state = Unlocked;
}

void ioc::IoC_Container::lock()
{
	state = Locked;
}

ioc::IoC_Container::~IoC_Container()
{
	using pair = std::pair<size_t, std::unique_ptr<IoC_Entry>>;

	std::vector<pair> entries;
	for(auto& e : mappings) {
		entries.push_back(pair(e.first, move(e.second)));
	}

	sort(entries.begin(), entries.end(), [](pair& a, pair& b) {
		return a.second->getID() < b.second->getID();
	});

	mappings.clear();
	entries.clear();
}

size_t ioc::IoC_Container::size() const
{
	return mappings.size();
}

size_t ioc::IoC_Container::hash(const std::string& v) const
{
	return std::hash<std::string>()(v);
}
