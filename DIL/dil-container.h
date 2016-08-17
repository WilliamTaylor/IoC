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

#include "dil-generic-constraints.h"
#include "dil-lifetimes.h"
#include "dil-exceptions.h"
#include "dil-header.h"
#include "dil-entry.h"

namespace dil {
    enum container_state {
        Locked, Unlocked 
    };

    class DIL_EXPORTS container
    {
        std::map<size_t, std::unique_ptr<entry>> mappings;
        container_state state;
    public:
        container();
        container(container&& container);
        container(const container& container) = delete;

        virtual ~container();
    
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

        template<typename Interface>
        bool supplied(size_t * hashOutput = nullptr) const;

        void unlock();
        void lock();

        size_t size() const;
    private:
        size_t hash(const std::string& v) const;
    };

    template<typename Dependency>
    container * container::query(Dependency ** dependency) {
        dil::IsInterface<Dependency>();
        try {
            auto object = fetch<Dependency>();
            (*dependency) = object;
        } catch (interface_exception e) {
            (*dependency) = nullptr;
        }

        return this;
    }
    
    template<typename Interface>
    entry * container::fetchEntry() {
        IsInterface<Interface>();
        size_t hash = 0;
        return supplied<Interface>(hash) ? mappings[hash].get() : nullptr;
    }

    template<typename Interface, typename Mapping>
    container * container::supply(std::unique_ptr<lifetime> scope) {
        if (state == Unlocked) {
            Implements<Interface, Mapping>();
            auto entry = std::make_unique<dil::entry>(this, move(scope));
            entry->setTypeInformation<Interface, Mapping>();
            entry->setCreateHandler<Mapping>();
            entry->setDeleteHandler<Mapping>();
            mappings[typeid(Interface).hash_code()] = move(entry);
        }

        return this;
    }

    template<typename Interface>
    bool container::supplied(size_t * hashOutput) const {
        IsInterface<Interface>();
        auto hash = typeid(Interface).hash_code();

        if (hashOutput != nullptr) {
            (*hashOutput) = hash;
        }

        return mappings.count(hash) != 0;
    }

    template<typename Interface>
    Interface * container::fetch() {
        IsInterface<Interface>();

        const auto& info = typeid(Interface);
        auto hash = info.hash_code();

        if (mappings.count(hash) > 0)
        {
            return static_cast<Interface *>(mappings[hash]->getInstance());
        }

        throw interface_exception(info, hash);
    }

    template<typename Dependency, typename... Dependencies>
    container * container::query(Dependency ** first, Dependencies... args) {
        dil::IsInterface<Dependency>();
        return query(first)->query(args...);
    }
}
