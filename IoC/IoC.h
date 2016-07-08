
#pragma once

#include "IoC_Container.h"
#include "IoC_GlobalLifetime.h"
#include "IoC_LocalLifetime.h"
#include "IoC_GenericConstraints.h"

namespace ioc {
    IOC_EXPORTS std::shared_ptr<IoC_Container> make_injection_container();
    IOC_EXPORTS std::unique_ptr<IoC_Lifetime> make_single_instance();
    IOC_EXPORTS std::unique_ptr<IoC_Lifetime> make_multi_instance();
    IOC_EXPORTS std::string library_version();
}