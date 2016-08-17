
#include "dil-exceptions.h"

dil::interface_exception::interface_exception(const std::type_info& info, size_t hash)
{
    this->typeDetails = new std::type_index(info);
    this->hashCode = hash;

    generateMessage();
}

void dil::interface_exception::generateMessage()
{
    std::stringstream ss;
    ss << "Error no interface has been registered with this container. ";
    ss << "Check '";
    ss << typeDetails->name();
    ss << "' is registered with this container and has a type mapping. ";
    ss << "Hash code generated was -> ";
    ss << hashCode;
    msg = ss.str();
}

const char * dil::interface_exception::what() const throw()
{
    return msg.c_str();
}
