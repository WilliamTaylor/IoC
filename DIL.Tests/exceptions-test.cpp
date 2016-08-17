#include "CppUnitTest.h"
#include "test-data.h"

using Microsoft::VisualStudio::CppUnitTestFramework::Assert;

namespace dil 
{
    namespace tests
    {
        TEST_CLASS(exceptions_test) 
        {
        public:
            TEST_METHOD(exceptions_test_message) 
            {
                const auto hash{100};

                try
                {
                    throw interface_exception(typeid(Interface), hash);
                } 
                catch (interface_exception e) 
                {
                    std::string type = typeid(Interface).name();
                    std::string message = e.what();
                
                    if (message.find(std::to_string(hash)) == std::string::npos)
                    {
                        Assert::Fail(L"Error couldnt find type hash in exception message.");
                    }

                    if (message.find(type) == std::string::npos)
                    {
                        Assert::Fail(L"Error couldnt find type name in exception message.");
                    }
                }
            }
        };
    }
}