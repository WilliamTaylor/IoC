#pragma once

#include "dil-generic-constraints.h"
#include "dil-header.h"

namespace dil 
{
    using delete_closure = std::function<void(void *)>;
    using create_closure = std::function<void *()>;
    using timestamp = long long;

    class DIL_EXPORTS entry
    {
        std::unique_ptr<lifetime> lifetimeScope;
        std::type_index* implementationType;
        std::type_index* interfaceType;

        delete_closure deleteClosure;
        create_closure createClosure;
        timestamp timeRegistered;
        container * container;
    public:
        explicit entry(dil::container * container, std::unique_ptr<lifetime> lifetime);
        virtual ~entry();

        const std::type_index& getImplementationType() const;
        const std::type_index& getInterfaceType() const;
        
        delete_closure getDeleteClosure() const;
        create_closure getCreateClosure() const;
       
        timestamp getTimeRegisted() const;

        template<typename Interface>
        Interface * getObject();

        template<typename Class> 
        entry * createDeleteClosure();

        template<typename Class> 
        entry * createNewClosure();

        template<typename Interface, typename Mapping>
        entry * createTypeInfo();
    private:
        void * ptr();
    };

    template<typename Interface, typename Mapping>
    entry * entry::createTypeInfo() 
    {
        Implements<Interface, Mapping>();

        if (!interfaceType && !implementationType) 
        {
            implementationType = new std::type_index(typeid(Mapping));
            interfaceType = new std::type_index(typeid(Interface));
        }

        return this;
    }
    
    template<typename Class>
    entry * entry::createDeleteClosure() 
    {
        IsClass<Class>();

        deleteClosure = [&](void * pointer) -> void
        {
            if (pointer != nullptr) 
            {
                delete static_cast<Class *>(pointer);
                pointer = nullptr;
            }
        };

        return this;
    }

    template<typename Class>
    entry * entry::createNewClosure() 
    {
        IsClass<Class>();

        createClosure = [&]() -> void * 
        { 
            return static_cast<void *>(new Class(this->container)); 
        };

        return this;
    }

    template<typename Interface>
    Interface * entry::getObject()
    {    
        return static_cast<Interface *>(ptr());
    }
}
