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

#include <functional>
#include <typeindex>  
#include <algorithm>
#include <assert.h>
#include <iostream>
#include <type_traits>
#include <iterator>
#include <exception>
#include <chrono>
#include <typeinfo>  
#include <sstream>
#include <string>
#include <memory>
#include <vector>
#include <map>

#pragma warning(disable: 4540)
#pragma warning(disable: 4275)
#pragma warning(disable: 4273)
#pragma warning(disable: 4251)
#pragma warning(disable: 4005)

#ifdef IOC_EXPORTS
	#define IOC_EXPORTS __declspec(dllexport) 
#else
	#define IOC_EXPORTS __declspec(dllimport) 
#endif

#define IOC_LIB_REVISION 0
#define IOC_LIB_MAJOR 1
#define IOC_LIB_MINOR 0

namespace ioc {
	typedef long long IoC_ID;
	typedef void * IoC_Type;

	class IoC_Container;
}
