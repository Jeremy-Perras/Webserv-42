#include "Socket.hpp"

Socket::Socket(void)
{
    return;
}

Socket::Socket(int domain, int type, int protocol, int port, char *ip) : _server_fd(socket(domain, type, 0))
{
    (void) ip;
    this->_address.sin_family = AF_INET;
    this->_address.sin_addr.s_addr =  INADDR_ANY;
    this->_address.sin_port = htons(port);
    // inet_pton(AF_INET, "0.0.0.0", &this->_address.sin_addr);
    bzero(&(this->_address.sin_zero), 8);
    return ;
}

int Socket::getFd(void)
{
    return(this->_server_fd);
}

struct sockaddr_in Socket::getAdress(void)
{
    return(this->_address);
}

Socket & Socket::operator=(Socket const &rhs)
{
    if(this == &rhs)
        return(*this);
    return(*this);
}

Socket::Socket(Socket const &src)
{
    *this = src;
    return ;
}

Socket::~Socket(void)
{
    return;
}
