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

#include "IoC_GlobalLifetime.h"
#include "IoC_Container.h"

ioc::IoC_Type ioc::IoC_GlobalLifetime::instance = nullptr;

ioc::IoC_GlobalLifetime::IoC_GlobalLifetime()
{
}

ioc::IoC_GlobalLifetime::~IoC_GlobalLifetime()
{
}

void ioc::IoC_GlobalLifetime::deleteInstance(IoC_Entry * entry)
{
	if (instance != nullptr)
	{
		entry->getDeleteHandler()(instance);
		instance = nullptr;
	}
}

ioc::IoC_Type ioc::IoC_GlobalLifetime::getInstance(ioc::IoC_Entry * entry)
{
	if (instance == nullptr)
	{
		instance = entry->getCreateHandler()();
	}

	return instance;
}
