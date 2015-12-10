/***
 * 
 * Copyright 10/12/2015 William wi11berto@yahoo.co.uk
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


#pragma once

#include "IoC_Header.h"

namespace ioc {
	class IoC_Lifetime;

	class IOC_EXPORTS IoC_Entry {
		private:
			std::function<IoC_Type()> init_handler;
			std::type_index* interface_info;
			std::type_index* mapping_info;

			IoC_Lifetime * lifetime;
		public:
			IoC_Entry();
			~IoC_Entry();

			std::function<IoC_Type()> getInitHandler();

			void setInitHandler(std::function<IoC_Type()> function);
			void setTypeInfo(const std::type_info& i, const std::type_info& m);
			void setLifetime(IoC_Lifetime * lifetime);

			size_t getInterfaceHashCode();
			size_t getMappingHashCode();

			IoC_Type getInstance();
		private: 
			std::type_index* deleteIfAllocated(std::type_index*);
	};
}
