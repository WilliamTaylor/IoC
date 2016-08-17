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

#ifdef EXPORT_DLL
    #define DIL_EXPORTS __declspec(dllexport) 
#else
    #define DIL_EXPORTS __declspec(dllimport) 
#endif

#define DIL_LIB_REVISION 0
#define DIL_LIB_MAJOR 1
#define DIL_LIB_MINOR 1

namespace dil {
    class container;
}
