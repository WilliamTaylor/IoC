
#include "dil.h"

namespace dil 
{
    std::shared_ptr<container> make_injection_container() 
    {
        return std::make_shared<container>();
    }

    std::unique_ptr<lifetime> make_multi_instance() 
    {
        return std::make_unique<local_lifetime>();
    }

    std::unique_ptr<lifetime> make_single_instance() 
    {
        return std::make_unique<global_lifetime>();
    }

    std::string version() 
    {
        std::stringstream ss;
        ss << LibMajor << ".";
        ss << LibMinor << ".";
        ss << LibVersion;
        return ss.str();
    }
}