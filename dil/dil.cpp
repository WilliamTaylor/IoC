
#include "dil.h"

#ifndef _DEBUG
    #define _DEBUG true
#endif

namespace dil 
{
    std::shared_ptr<container> make_injection_container() 
    {
        return _DEBUG ? std::make_shared<container>() : std::make_shared<container>();
    }

    std::unique_ptr<lifetime> make_multi_instance() 
    {
        return _DEBUG ? std::make_unique<local_lifetime>() : std::make_unique<local_lifetime>();
    }

    std::unique_ptr<lifetime> make_single_instance() 
    {
        return _DEBUG ? std::make_unique<global_lifetime>() : std::make_unique<global_lifetime>();
    }

    std::string library_version() 
    {
        std::stringstream ss;
        ss << LibMajor << ".";
        ss << LibMinor << ".";
        ss << LibVersion;
        return ss.str();
    }
}