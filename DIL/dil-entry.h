#pragma once

#include "dil-generic-constraints.h"
#include "dil-header.h"

namespace dil {
    class container;
    class lifetime;

    class DIL_EXPORTS entry
    {
        container * container;

        std::unique_ptr<lifetime> lifetime;
        std::function<void(void *)> deleteHandler;
        std::function<void *()> createHandler;
        std::type_index * interfaceInfo;
        std::type_index * mappingInfo;
        std::string interfaceName;
        std::string mappingName;
    
        long long entryID;
    public:
        explicit entry(dil::container * container, std::unique_ptr<dil::lifetime> lifetime);
        virtual ~entry();

        template<typename Class> 
        entry * setDeleteHandler();

        template<typename Class> 
        entry * setCreateHandler();

        template<typename Interface, typename Mapping>
        entry * setTypeInformation();

        std::function<void(void *)> getDeleteHandler() const;
        std::function<void *()> getCreateHandler() const;
        std::string getInterfaceName() const;
        std::string getMappingName() const;

        size_t getInterfaceHashCode() const;
        size_t getMappingHashCode() const;
        long long getID() const;

        void * getInstance();
    };

    template<typename Interface, typename Mapping>
    entry * entry::setTypeInformation() {
        dil::Implements<Interface, Mapping>();
        if (interfaceInfo == nullptr && mappingInfo == nullptr) {
            interfaceInfo = new std::type_index(typeid(Interface));
            interfaceName = interfaceInfo->name();

            mappingInfo = new std::type_index(typeid(Mapping));
            mappingName = mappingInfo->name();
        }

        return this;
    }
    
    template<typename Class>
    entry * entry::setDeleteHandler() {
        this->deleteHandler = [&](void * pointer) {
            IsClass<Class>();
            if (pointer != nullptr) {
                delete static_cast<Class *>(pointer);
                pointer = nullptr;
            }
        };

        return this;
    }

    template<typename Class>
    entry * entry::setCreateHandler() {
        this->createHandler = [&]() {
            IsClass<Class>();
            return static_cast<void *>(new Class(this->container));
        };

        return this;
    }
}
