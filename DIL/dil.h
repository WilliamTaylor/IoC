
#pragma once

#include "dil-container.h"
#include "dil-lifetimes.h"
#include "dil-generic-constraints.h"

namespace dil {
    DIL_EXPORTS std::shared_ptr<container> make_injection_container();
    DIL_EXPORTS std::unique_ptr<lifetime> make_single_instance();
    DIL_EXPORTS std::unique_ptr<lifetime> make_multi_instance();
    DIL_EXPORTS std::string library_version();
}