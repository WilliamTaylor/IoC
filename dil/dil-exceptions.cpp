
#include "dil-exceptions.h"

dil::interface_exception::interface_exception(const std::type_info& info, size_t hash) :
    typeindex(new std::type_index(info)),
    hashcode(hash)
{
    createExceptionMessage();
}

void dil::interface_exception::createExceptionMessage()
{
    std::stringstream ss;
    ss << "Error no interface has been registered with this container. ";
    ss << "Check '" << typeindex->name();
    ss << "' is registered with this container and has a type mapping. ";
    ss << "Hash code generated was -> " << hashcode;

    message = ss.str();
}

const std::type_index& dil::interface_exception::interfaceType() const
{
    return *typeindex;
}

const std::string& dil::interface_exception::exceptionMessage() const
{
    return message;
}

const size_t dil::interface_exception::hash() const
{
    return hashcode;   
}

const char * dil::interface_exception::what() const throw()
{
    return message.c_str();
}
