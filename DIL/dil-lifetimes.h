#pragma once

#include "dil-header.h"
#include "dil-entry.h"

namespace dil {
    class DIL_EXPORTS lifetime
    {
    public:
        virtual void * getInstance(entry *) = 0;
        virtual void deleteInstance(entry *) = 0;
        virtual ~lifetime() {}
    };

    class DIL_EXPORTS local_lifetime : public lifetime
    {
        std::vector<void *> instances;
    public:
        local_lifetime();
        virtual ~local_lifetime();

        void * getInstance(entry *) override;
        void deleteInstance(entry *) override;
    };

    class DIL_EXPORTS global_lifetime : public lifetime
    {
        void * instance;
    public:
        global_lifetime();
        virtual ~global_lifetime();

        void * getInstance(entry *) override;
        void deleteInstance(entry *) override;
    };
}
