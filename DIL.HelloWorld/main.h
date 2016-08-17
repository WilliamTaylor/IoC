#pragma once

#include <iostream>
#include <string>
#include "dil.h"

#pragma comment(lib, "dil.lib")

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
    explicit DummyNameService(dil::container * container) {}
    std::string name() override { return "Bob"; }
    ~DummyNameService() {
        std::cout << "delete DummyNameService" << std::endl;
    }
};

class DummyAgeService : public IAgeService {
public:
    explicit DummyAgeService(dil::container * container) {}
    int age() override { return 25; }
    ~DummyAgeService() {
        std::cout << "delete DummyAgeService" << std::endl;
    }
};

class DummyBirthService : public IBirthService {
public:
    explicit DummyBirthService(dil::container * container) {}
    ~DummyBirthService() { 
        std::cout << "delete DummyBirthService" << std::endl;
    }
    std::string country() override { return "Bobtown"; }
};

class MyNameService : public INameService {
public:
    explicit MyNameService(dil::container * container) {}
    std::string name() override { return "William Taylor"; }
    ~MyNameService() {
        std::cout << "delete MyNameService" << std::endl;
    }
};

class MyAgeService : public IAgeService {
public:
    explicit MyAgeService(dil::container * container) {}
    int age() override { return 21; }
    ~MyAgeService() {
        std::cout << "delete MyAgeService" << std::endl;
    }
};

class MyBirthService : public IBirthService {
public:
    explicit MyBirthService(dil::container * container) {}
    std::string country() override { return "London"; }
    ~MyBirthService() {
        std::cout << "delete MyBirthService" << std::endl;
    }
};
