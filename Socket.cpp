#include "Socket.hpp"

Socket::Socket(void)
{
    return;
}

Socket::Socket(int domain, int type, int protocol, int port , u_long ip) : _server_fd(socket(domain, type, protocol))
{
    this->_address.sin_family = domain;
    this->_address.sin_port = htons(port);
    this->_address.sin_addr.s_addr = htonl(ip);

    // if(this->_server_fd < 0)
    //     throw ExceptionSocket();
    return ;
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
