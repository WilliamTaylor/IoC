#pragma once

#include <functional>
#include <typeindex>  
#include <algorithm>
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

namespace dil 
{
    class container;

    using delete_closure = std::function<void(void *)>;
    using create_closure = std::function<void *()>;
    using raw_pointer = void *;
    using timestamp = long long;

    struct lifetime;

    const int LibVersion = 0;
    const int LibMajor = 2;
    const int LibMinor = 0;
}
