#pragma once

#include "dil-header.h"

namespace dil 
{
    class DIL_EXPORTS interface_exception : std::exception
    {
    public:
        interface_exception(const type_info& info, size_t hash);

        const std::type_index& interfaceType() const;
        const std::string& exceptionMessage() const;
        const size_t hash() const;
        const char * what() const throw() override;
    private:
        std::type_index* typeindex;
        std::string message;
        size_t hashcode;

        void createExceptionMessage();
    };
}

