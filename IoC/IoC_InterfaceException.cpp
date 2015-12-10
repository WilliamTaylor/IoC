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

#include "IoC_InterfaceException.h"

ioc::IoC_InterfaceException::IoC_InterfaceException(const std::type_info& info, size_t hash)
{
	this->typeDetails = new std::type_index(info);
	this->hashCode = hash;

	generateMessage();
}

void ioc::IoC_InterfaceException::generateMessage()
{
	std::stringstream ss;
	
	ss << "Error no interface has been registered with this container. ";
	ss << "Check '";
	ss << typeDetails->name();
	ss << "' is registered with this container and has a type mapping. ";
	ss << "Hash code generated was -> ";
	ss << hashCode;

	msg = ss.str();
}

const char * ioc::IoC_InterfaceException::what() const throw()
{
	return msg.c_str();
}
