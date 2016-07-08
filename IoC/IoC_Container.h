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

#include "IoC_GenericConstraints.h"
#include "IoC_LocalLifetime.h"
#include "IoC_Exceptions.h"
#include "IoC_Lifetime.h"
#include "IoC_Header.h"
#include "IoC_Entry.h"

namespace ioc {
    enum IoC_ContainerState {
        Locked, Unlocked 
    };

    class IOC_EXPORTS IoC_Container
    {
        std::map<size_t, std::unique_ptr<IoC_Entry>> mappings;
        IoC_ContainerState state;
    public:
        IoC_Container();
        IoC_Container(IoC_Container&& container);
        IoC_Container(const IoC_Container& container) = delete;

        virtual ~IoC_Container();
    
        template<typename Dependency, typename... Dependencies>
        IoC_Container * query(Dependency ** first, Dependencies... args);
            
        template<typename Dependency>
        IoC_Container * query(Dependency ** dependency);

        template<typename Interface, typename Mapping>
        IoC_Container * supply(std::unique_ptr<IoC_Lifetime> lifespan = std::make_unique<IoC_LocalLifetime>());

        template<typename Interface>
        IoC_Entry * fetchEntry();

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
    IoC_Container * IoC_Container::query(Dependency ** dependency) {
        IsInterface<Dependency>();
        try {
            auto object = fetch<Dependency>();
            (*dependency) = object;
        } catch (IoC_InterfaceException e) {
            (*dependency) = nullptr;
        }

        return this;
    }
    
    template<typename Interface>
    IoC_Entry * IoC_Container::fetchEntry() {
        IsInterface<Interface>();
        size_t hash = 0;
        return supplied<Interface>(hash) ? mappings[hash].get() : nullptr;
    }

    template<typename Interface, typename Mapping>
    IoC_Container * IoC_Container::supply(std::unique_ptr<IoC_Lifetime> scope) {
        if (state == Unlocked) {
            Implements<Interface, Mapping>();
            auto entry = std::make_unique<IoC_Entry>(this, move(scope));
            entry->setTypeInformation<Interface, Mapping>();
            entry->setCreateHandler<Mapping>();
            entry->setDeleteHandler<Mapping>();
            mappings[typeid(Interface).hash_code()] = move(entry);
        }

        return this;
    }

    template<typename Interface>
    bool IoC_Container::supplied(size_t * hashOutput) const {
        IsInterface<Interface>();
        auto hash = typeid(Interface).hash_code();

        if (hashOutput != nullptr) {
            (*hashOutput) = hash;
        }

        return mappings.count(hash) != 0;
    }

    template<typename Interface>
    Interface * IoC_Container::fetch() {
        IsInterface<Interface>();

        const auto& info = typeid(Interface);
        auto hash = info.hash_code();

        if (mappings.count(hash) > 0)
        {
            return static_cast<Interface *>(mappings[hash]->getInstance());
        }

        throw IoC_InterfaceException(info, hash);
    }

    template<typename Dependency, typename... Dependencies>
    IoC_Container * IoC_Container::query(Dependency ** first, Dependencies... args) {
        IsInterface<Dependency>();
        return query(first)->query(args...);
    }
}
