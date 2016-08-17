#include "CppUnitTest.h"
#include "test-data.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace dil 
{
    namespace tests 
    {
        TEST_CLASS(lifetimes_test) 
        {
        public:
            TEST_METHOD(lifetimes_test_global_lifetime) 
            {
                entry e(make_injection_container().get(), make_single_instance());
                e.createTypeInfo<Interface, Mapping>();
                e.createNewClosure<Mapping>();
                e.createDeleteClosure<Mapping>();

                const auto ptr1 = e.getObject<Interface>();
                const auto ptr2 = e.getObject<Interface>();

                Assert::IsTrue(ptr1 == ptr2, L"Error objects are not the same");
            }

            TEST_METHOD(lifetimes_test_local_lifetime) 
            {
                entry e(make_injection_container().get(), make_multi_instance());
                e.createTypeInfo<Interface, Mapping>();
                e.createNewClosure<Mapping>(); 
                e.createDeleteClosure<Mapping>();
            
                const auto ptr1 = e.getObject<Interface>();
                const auto ptr2 = e.getObject<Interface>();
                
                Assert::IsTrue(ptr1 != ptr2, L"Error objects are the same");
            }
        };
    }
}