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
#include "IoC.h"

#pragma comment(lib, "IoC.lib")

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace ioc;

namespace IoCTests {
	TEST_CLASS(IoC_ContainerTest) {
	public:
		TEST_METHOD(IoC_Container_TestingFetchFunction1) {
			auto errorNote = L"Error IoC_InterfaceException was not thrown.";
			auto container = make_injection_container();

			try {
				container->fetch<Interface>();

				Assert::Fail(errorNote);
			} catch (...) {}
		}

		TEST_METHOD(IoC_Container_TestingFetchFunction2) {
			try {
				auto container = make_injection_container();
				container->supply<Interface, Mapping>();
				auto object = container->fetch<Interface>();

				if (object == nullptr)
				{
					Assert::Fail(L"Error returned object shouldnt be null");
				}
			} catch (IoC_InterfaceException e) {
				Assert::Fail(L"Error IoC_InterfaceException was thrown");
			}
		}

		TEST_METHOD(IoC_Container_TestingSupply1) {
			try {
				auto container = make_injection_container();
				container->supply<Interface, Mapping>();
				
				if (!container->supplied<Interface>())
				{
					Assert::Fail(L"Error Interface has not be supplied successfully");
				}
			} catch (...) {
				Assert::Fail(L"Error exception was thrown");
			}
		}

		TEST_METHOD(IoC_Container_TestingSupply2) {
			try {
				auto container = make_injection_container();

				if (container->supplied<Interface>())
				{
					Assert::Fail(L"Error nothing has been supplied should have returned false.");
				}
			} catch (...) {
				Assert::Fail(L"Error exception was thrown");
			}
		}
	};
}
