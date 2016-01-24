/***
 * 
 * Copyright 10/12/2015 William Taylor wi11berto@yahoo.co.uk
 *  
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *  
 *    http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
***/

#include "CppUnitTest.h"
#include "TestData.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace ioc;

namespace IoCTests {
	TEST_CLASS(IoC_ExceptionsTest) {
	public:
		TEST_METHOD(IoC_Exceptions_TestMessage) {
			auto hash{ 100 };

			try {
				throw IoC_InterfaceException(typeid(Interface), hash);
			} catch (IoC_InterfaceException e) {
				std::string type = typeid(Interface).name();
				std::string message = (e.what());
				
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