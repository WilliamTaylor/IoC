
#include "IoC.h"

namespace ioc {
    IOC_EXPORTS std::shared_ptr<IoC_Container> make_injection_container() {
        return _DEBUG ? std::make_shared<IoC_Container>() : std::make_shared<IoC_Container>();
    }

    IOC_EXPORTS std::unique_ptr<IoC_Lifetime> make_multi_instance() {
        return _DEBUG ? std::make_unique<IoC_LocalLifetime>() : std::make_unique<IoC_LocalLifetime>();
    }

    IOC_EXPORTS std::unique_ptr<IoC_Lifetime> make_single_instance() {
        return _DEBUG ? std::make_unique<IoC_GlobalLifetime>() : std::make_unique<IoC_GlobalLifetime>();
    }

    IOC_EXPORTS std::string library_version() {
        auto revision_version { IOC_LIB_REVISION };
        auto major_version { IOC_LIB_MAJOR };
        auto minor_version { IOC_LIB_MINOR };

        std::stringstream ss;
        ss << major_version << ".";
        ss << minor_version << ".";
        ss << revision_version;
        return ss.str();
    }
}