#include "Bind.hpp"


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

int Binding::connect_network(int sock)
{
    return(bind(sock,(struct sockaddr *) &this->_address, sizeof(this->_address)));
}

Binding::~Binding(void)
{
    return ;
}
