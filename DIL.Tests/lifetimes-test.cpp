#include "CppUnitTest.h"
#include "test-data.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace dil {
    namespace tests {
        TEST_CLASS(lifetimes_test) {
        public:
            TEST_METHOD(lifetimes_test_global_lifetime) {
                dil::entry e(dil::make_injection_container().get(), dil::make_single_instance());
                e.setTypeInformation<Interface, Mapping>();
                e.setCreateHandler<Mapping>();
                e.setDeleteHandler<Mapping>();
                Assert::AreEqual(e.getInstance(), e.getInstance());
            }

            TEST_METHOD(lifetimes_test_local_lifetime) {
                dil::entry e(dil::make_injection_container().get(), dil::make_multi_instance());
                e.setTypeInformation<Interface, Mapping>();
                e.setCreateHandler<Mapping>(); 
                e.setDeleteHandler<Mapping>();
                Assert::AreNotEqual(e.getInstance(), e.getInstance());
            }
        };
    }
}