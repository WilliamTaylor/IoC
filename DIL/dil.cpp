
#include "dil.h"

namespace dil {
    std::shared_ptr<container> make_injection_container() {
        return _DEBUG ? std::make_shared<container>() : std::make_shared<container>();
    }

    std::unique_ptr<lifetime> make_multi_instance() {
        return _DEBUG ? std::make_unique<local_lifetime>() : std::make_unique<local_lifetime>();
    }

    std::unique_ptr<lifetime> make_single_instance() {
        return _DEBUG ? std::make_unique<global_lifetime>() : std::make_unique<global_lifetime>();
    }

    std::string library_version() {
        auto revision_version { DIL_LIB_REVISION };
        auto major_version { DIL_LIB_MAJOR };
        auto minor_version { DIL_LIB_MINOR };

        std::stringstream ss;
        ss << major_version << ".";
        ss << minor_version << ".";
        ss << revision_version;
        return ss.str();
    }
}