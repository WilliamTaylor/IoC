#include "CppUnitTest.h"
#include "test-data.h"

using Microsoft::VisualStudio::CppUnitTestFramework::Assert;

namespace dil 
{
    namespace tests 
    {
        TEST_CLASS(entry_test) 
        {
        public:
            TEST_METHOD(entry_test_hash_test_one) 
            {
                const auto& type_info = typeid(Interface);
                const auto container = make_injection_container();
                entry e(container.get(), make_single_instance());
                e.createTypeInfo<Interface, Mapping>(); 
                Assert::AreEqual(type_info.hash_code(), e.getInterfaceType().hash_code());
            }

            TEST_METHOD(entry_test_hash_test_two) 
            {
                const auto& type_info = typeid(Mapping);
                const auto container = make_injection_container();
                entry e(container.get(), make_single_instance());
                e.createTypeInfo<Interface, Mapping>();
                Assert::AreEqual(type_info.hash_code(), e.getImplementationType().hash_code());
            }
        };
    }
}