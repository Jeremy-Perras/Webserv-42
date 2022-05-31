#include "Socket.hpp"

Socket::Socket(void)
{
    return;
}

Socket::Socket(int domain, int type, int protocol, int port, char *ip) : _server_fd(socket(domain, type, 0))
{
    (void) ip;
    this->_address.sin_family = AF_INET;
    this->_address.sin_addr.s_addr =  INADDR_ANY;  // inet_pton(AF_INET, "0.0.0.0", &this->_address.sin_addr);
    this->_address.sin_port = htons(port);
    bzero(&(this->_address.sin_zero), 8);
    if(this->_server_fd == -1)
        throw SocketException();
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
    this->_address = rhs._address;
    this->_server_fd = rhs._server_fd;
    return(*this);
}

Socket::Socket(Socket const &src)
{
    *this = src;
    return ;
}

const char* Socket::SocketException::what() const throw()
{
    return("Can't create socket");
}

Socket::~Socket(void)
{
    return;
}
