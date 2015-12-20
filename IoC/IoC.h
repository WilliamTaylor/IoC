
#pragma once

#include "IoC_Container.h"
#include "IoC_GlobalLifetime.h"
#include "IoC_LocalLifetime.h"
#include "IoC_GenericConstraints.h"

namespace ioc {
	IOC_EXPORTS std::shared_ptr<IoC_Container> make_injection_container(bool singleton = false);
	IOC_EXPORTS std::string get_library_version();

	IOC_EXPORTS IoC_GlobalLifetime * make_single_instance();
	IOC_EXPORTS IoC_LocalLifetime * make_multi_instance();
}