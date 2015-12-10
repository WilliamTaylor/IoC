
#include "IoC.h"

namespace ioc {
	IOC_EXPORTS std::shared_ptr<IoC_Container> make_injection_container(bool singleton) {
		static IoC_Container * singleContainer = nullptr;
		if (singleton || singleContainer != nullptr) {
			singleContainer = singleContainer != nullptr ? singleContainer : new IoC_Container();
			return std::shared_ptr<IoC_Container>(singleContainer);
		}
		else {
			return std::shared_ptr<IoC_Container>(new IoC_Container());
		}
	}

	IOC_EXPORTS IoC_LocalLifetime * make_multi_instance() {
		return new IoC_LocalLifetime();
	}

	IOC_EXPORTS IoC_GlobalLifetime * make_single_instance() {
		return new IoC_GlobalLifetime();
	}
}