#include "CppUnitTest.h"
#include "test-data.h"

using Microsoft::VisualStudio::CppUnitTestFramework::Assert;

namespace dil 
{
    namespace tests
    {
        TEST_CLASS(container_test) 
        {
        public:
            TEST_METHOD(container_memory_cleanup_function) 
            {
                auto errorNote = L"Error Mapping was not deleted properly.";

                try
                {
                    {
                        auto container = make_injection_container();
                        container->supply<Interface, Mapping>();
                        container->fetch<Interface>()->method();
                    }
                
                    Assert::IsTrue(Mapping::deleted, errorNote);
                }
                catch (...) 
                {
                    Assert::Fail(L"Unexpected error in test");
                }
            }

            TEST_METHOD(container_testing_fetch_function_one) 
            {
                auto errorNote = L"Error IoC_InterfaceException was not thrown.";
                auto container = make_injection_container();

                try
                {
                    container->fetch<Interface>();
                    Assert::Fail(errorNote);
                } 
                catch (...) 
                {
                    // This should be hit therefor skipping over the Assert::Fail call.
                }
            }

            TEST_METHOD(container_testing_fetch_function_two) 
            {
                try 
                {
                    auto container = make_injection_container();
                    container->supply<Interface, Mapping>();
                    auto object = container->fetch<Interface>();

                    Assert::IsNotNull(object, L"Error returned object shouldnt be null");
                }
                catch (interface_exception e)
                {
                    Assert::Fail(L"Error IoC_InterfaceException was thrown");
                }
            }

            TEST_METHOD(container_testing_supply_one) 
            {
                try 
                {
                    auto container = make_injection_container();
                    container->supply<Interface, Mapping>();
            
                    Assert::IsTrue(container->supplied<Interface>(), L"Error Interface has not be supplied successfully");
                } 
                catch (...)
                {
                    Assert::Fail(L"Error exception was thrown");
                }
            }

            TEST_METHOD(container_testing_supply_two) 
            {
                try 
                {
                    Assert::IsFalse(make_injection_container()->supplied<Interface>(), L"Error nothing has been supplied should have returned false.");
                } catch (...) {
                    Assert::Fail(L"Error exception was thrown");
                }
            }
        };
    }
}
