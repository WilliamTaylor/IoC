
#pragma once

#include "dil-generic-constraints.h"
#include "dil-exceptions.h"
#include "dil-lifetimes.h"
#include "dil-header.h"
#include "dil-entry.h"

namespace dil 
{
    enum container_state 
    {
        Unlocked,
        Locked
    };

    class DIL_EXPORTS container
    {
    public:
        container();
        container(const container& container) = delete;
        container(container&& container);
        ~container();
    
        void unlock();
        void lock();

        size_t hash(const std::string& v) const;
        size_t size() const;

        template<typename Interface>
        bool supplied(size_t * hashOutput = nullptr) const;

        template<typename Dependency, typename... Dependencies>
        container * query(Dependency ** first, Dependencies... args);
            
        template<typename Dependency>
        container * query(Dependency ** dependency);

        template<typename Interface, typename Mapping>
        container * supply(std::unique_ptr<lifetime> lifespan = std::make_unique<local_lifetime>());

        template<typename Interface>
        entry * fetchEntry();

        template<typename Interface>
        Interface * fetch();
    private:
        std::map<size_t, std::unique_ptr<entry>> mappings;
        container_state state;
    };

    template<typename Dependency>
    container * container::query(Dependency ** dependency) 
    {
        IsInterface<Dependency>();
       
        try 
        {
            auto object = fetch<Dependency>();
            (*dependency) = object;
        } 
        catch (interface_exception e) 
        {
            (*dependency) = nullptr;
        }

        return this;
    }
    
    template<typename Interface>
    entry * container::fetchEntry() 
    {
        IsInterface<Interface>();
        size_t hash = 0;
        return supplied<Interface>(hash) ? mappings[hash].get() : nullptr;
    }

    template<typename Interface, typename Mapping>
    container * container::supply(std::unique_ptr<lifetime> scope) 
    {
        Implements<Interface, Mapping>();

        if (state == Unlocked) 
        {            
            auto entry = std::make_unique<dil::entry>(this, move(scope));
            entry->createTypeInfo<Interface, Mapping>();
            entry->createNewClosure<Mapping>();
            entry->createDeleteClosure<Mapping>();
           
            mappings[typeid(Interface).hash_code()] = move(entry);
        }

        return this;
    }

    template<typename Interface>
    bool container::supplied(size_t * hashOutput) const {
        IsInterface<Interface>();
       
        const auto hash = typeid(Interface).hash_code();

        if (hashOutput != nullptr) 
        {
            *hashOutput = hash;
        }

        return mappings.count(hash) != 0;
    }

    template<typename Interface>
    Interface * container::fetch() 
    {
        IsInterface<Interface>();

        const auto& info = typeid(Interface);
        const auto hash = info.hash_code();

        if (mappings.count(hash) > 0)
        {
            return mappings[hash]->getObject<Interface>();
        }

        throw interface_exception(info, hash);
    }

    template<typename Dependency, typename... Dependencies>
    container * container::query(Dependency ** first, Dependencies... args) 
    {
        IsInterface<Dependency>();
        return query(first)->query(args...);
    }
}
