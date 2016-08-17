#include "CppUnitTest.h"
#include "test-data.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IoCTests {
    namespace tests {
        TEST_CLASS(entry_test) {
        public:
            TEST_METHOD(entry_test_hash_test_one) {
                const auto& type_info = typeid(Interface);
                dil::entry e(dil::make_injection_container().get(), dil::make_single_instance());
                e.setTypeInformation<Interface, Mapping>(); 
                Assert::AreEqual(type_info.hash_code(), e.getInterfaceHashCode());
            }

            TEST_METHOD(entry_test_hash_test_two) {
                const auto& type_info = typeid(Mapping);
                dil::entry e(dil::make_injection_container().get(), dil::make_single_instance());
                e.setTypeInformation<Interface, Mapping>();
                Assert::AreEqual(type_info.hash_code(), e.getMappingHashCode());
            }
        };
    }
}