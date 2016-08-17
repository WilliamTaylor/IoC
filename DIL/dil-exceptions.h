#pragma once

#include "dil-header.h"

namespace dil {
    class DIL_EXPORTS interface_exception : std::exception
    {
        std::type_index * typeDetails;
        std::string msg;
        size_t hashCode;
    public:
        interface_exception(const type_info& info, size_t hash);
        const char * what() const throw() override;
    private:
        void generateMessage();
    };
}

