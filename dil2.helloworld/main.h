#pragma once

#include <iostream>
#include "dil.h"

#pragma comment(lib, "dil.lib")

struct INameService 
{
    virtual ~INameService() {}
    virtual std::string name() = 0;
};

struct IAgeService 
{
    virtual ~IAgeService() {}
    virtual int age() = 0;
};

struct IBirthService 
{
    virtual ~IBirthService() {}
    virtual std::string country() = 0;
};

struct IPrinter 
{
    virtual ~IPrinter() {}
    virtual void print() = 0;
};

struct DummyNameService : INameService 
{
    explicit DummyNameService(dil::container *) {}
    std::string name() override { return "Bob"; }
};

struct DummyAgeService : IAgeService 
{
    explicit DummyAgeService(dil::container *) {}
    int age() override { return 25; }
};

struct DummyBirthService : IBirthService 
{
    explicit DummyBirthService(dil::container *) {}
    std::string country() override { return "Bobtown"; }
};

struct MyNameService : INameService 
{
    explicit MyNameService(dil::container *) {}
    std::string name() override { return "William Taylor"; }
};

struct MyAgeService : IAgeService 
{
    explicit MyAgeService(dil::container *) {}
    int age() override { return 21; }
};

struct MyBirthService : IBirthService 
{
    explicit MyBirthService(dil::container *) {}
    std::string country() override { return "London"; }
};
