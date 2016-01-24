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

#pragma once

#include <iostream>
#include <string>
#include "IoC.h"

#pragma comment(lib, "IoC.lib")

class INameService {
public:
	virtual ~INameService() {}
	virtual std::string name() = 0;
};

class IAgeService {
public:
	virtual ~IAgeService() {}
	virtual int age() = 0;
};

class IBirthService {
public:
	virtual ~IBirthService() {}
	virtual std::string country() = 0;
};

class IPrinter {
public:
	virtual ~IPrinter() {}
	virtual void print() = 0;
};

class DummyNameService : public INameService {
public:
	explicit DummyNameService(ioc::IoC_Container * container) {}
	std::string name() override { return "Bob"; }
	~DummyNameService() {
		std::cout << "delete DummyNameService" << std::endl;
	}
};

class DummyAgeService : public IAgeService {
public:
	explicit DummyAgeService(ioc::IoC_Container * container) {}
	int age() override { return 25; }
	~DummyAgeService() {
		std::cout << "delete DummyAgeService" << std::endl;
	}
};

class DummyBirthService : public IBirthService {
public:
	explicit DummyBirthService(ioc::IoC_Container * container) {}
	~DummyBirthService() { 
		std::cout << "delete DummyBirthService" << std::endl;
	}
	std::string country() override { return "Bobtown"; }
};

class MyNameService : public INameService {
public:
	explicit MyNameService(ioc::IoC_Container * container) {}
	std::string name() override { return "William Taylor"; }
	~MyNameService() {
		std::cout << "delete MyNameService" << std::endl;
	}
};

class MyAgeService : public IAgeService {
public:
	explicit MyAgeService(ioc::IoC_Container * container) {}
	int age() override { return 21; }
	~MyAgeService() {
		std::cout << "delete MyAgeService" << std::endl;
	}
};

class MyBirthService : public IBirthService {
public:
	explicit MyBirthService(ioc::IoC_Container * container) {}
	std::string country() override { return "London"; }
	~MyBirthService() {
		std::cout << "delete MyBirthService" << std::endl;
	}
};
