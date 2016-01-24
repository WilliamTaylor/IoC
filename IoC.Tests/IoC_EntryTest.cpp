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
	TEST_CLASS(IoC_EntryTest) {
	public:
		TEST_METHOD(IoC_EntryTest_HashTest1) {
			const auto& type_info = typeid(Interface);
			IoC_Entry e(make_injection_container().get(), make_single_instance());
			e.setTypeInformation<Interface, Mapping>(); 
			Assert::AreEqual(type_info.hash_code(), e.getInterfaceHashCode());
		}

		TEST_METHOD(IoC_EntryTest_HashTest2) {
			const auto& type_info = typeid(Mapping);
			IoC_Entry e(make_injection_container().get(), make_single_instance());
			e.setTypeInformation<Interface, Mapping>();
			Assert::AreEqual(type_info.hash_code(), e.getMappingHashCode());
		}
	};
}