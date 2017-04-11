#pragma once

#include "dil-header.h"
#include "dil-entry.h"

namespace dil 
{
    struct lifetime
    {
        virtual raw_pointer acquire(entry * e) = 0;
        virtual void release(entry * e) = 0;
        virtual ~lifetime() = default;
    };

    class DIL_EXPORTS local_lifetime : public lifetime
    {
    public:
        local_lifetime() = default;
        virtual ~local_lifetime() = default;

        raw_pointer acquire(entry *) override;
        void release(entry *) override;
    private:
        std::vector<raw_pointer> allocated_objects;
    };

    class DIL_EXPORTS global_lifetime : public lifetime
    {
    public:
        global_lifetime();
        virtual ~global_lifetime() = default;

        raw_pointer acquire(entry *) override;
        void release(entry *) override;
    private:
        raw_pointer object;
    };
}
