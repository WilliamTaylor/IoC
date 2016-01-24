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

#include "IoC_Header.h"

namespace ioc {
	template<class Object>
	struct IsInterface {
		IsInterface() {
			static_assert(std::is_abstract<Object>(), "Object must be an interface/abstract class!");
		}
	};

	template<class Interface, class Implementee>
	struct Implements {
		Implements() {
			IsInterface<Interface>();
			static_assert(std::is_base_of<Interface, Implementee>(), "Implementee doesnt implement Interface");
		}
	};

	template<class Object>
	struct IsClass {
		IsClass() {
			static_assert(std::is_class<Object>(), "Object must be a class");
		}
	};
}
