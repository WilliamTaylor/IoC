#pragma once

#include "dil-header.h"

namespace dil 
{
    template<typename Object>
    struct IsInterface 
    {
        constexpr IsInterface() 
        {
            static_assert(std::is_abstract<Object>(), "Object must be an interface/abstract class!");
        }
    };

    template<typename Interface, typename Implementee>
    struct Implements 
    {
        constexpr Implements() 
        {
            IsInterface<Interface>();
            static_assert(std::is_base_of<Interface, Implementee>(), "Implementee doesnt implement Interface");
        }
    };

    template<typename Object>
    struct IsClass 
    {
        constexpr IsClass() 
        {
            static_assert(std::is_class<Object>(), "Object must be a class");
        }
    };
}
