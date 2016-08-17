#pragma once

#include "dil.h"

class Interface { 
public:
    virtual ~Interface() {}
    virtual void method() = 0;
};

class Mapping : public Interface {
public:
    static bool deleted;
public:
    explicit Mapping(dil::container*) { }
    ~Mapping() { deleted = true; }
    void method() override {}
};
