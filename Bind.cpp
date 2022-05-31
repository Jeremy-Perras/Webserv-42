#include "Bind.hpp"

Binding::Binding(void)
{
    return ;
}
Binding::Binding(int domain, int type, int protocol, int port , char *ip) : Socket(domain, type, protocol, port , ip)
{
    return;
}

Binding & Binding::operator=(Binding const &rhs)
{
    if(this == &rhs)
        return(*this);
    return(*this);
}

Binding::Binding(Binding const &src)
{
    *this = src;
    return ;
}

void Binding::connect_network(int sock)
{
    if(bind(sock, (struct sockaddr *) &this->_address, sizeof(this->_address)) == -1)
        throw BindException();
    return ;
}

const char * Binding::BindException::what() const throw()
{
    return("Can't bind to IP/port");
}

Binding::~Binding(void)
{
    return ;
}
