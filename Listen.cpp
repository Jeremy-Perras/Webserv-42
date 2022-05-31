#include "Listen.hpp"

Listening::Listening(void)
{
    return;
}

Listening & Listening::operator=(Listening const &rhs)
{
    if(this == &rhs)
        return(*this);
    this->_new_fd = rhs._new_fd;
    this->_their_addr = rhs._their_addr;
    return(*this);
}

void Listening::listenin(int sock, int backlog)
{
    if(listen(sock, backlog) == -1)
        throw ListenException();
    return ;
}

void Listening::accept(int sock)
{
    char host[NI_MAXHOST];
    char service[NI_MAXSERV];
    unsigned int sin_size = sizeof(struct sockaddr);

    memset(host, 0, NI_MAXHOST);
    memset(service, 0, NI_MAXSERV);
    this->_new_fd = ::accept(sock, (struct sockaddr *) &this->_their_addr, &sin_size);
    if(this->_new_fd == -1)
        throw AcceptException();
    if (getnameinfo((sockaddr*)&this->_their_addr, sin_size, host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
       std::cout << host << " connected on port " << service << std::endl;
    else
    {
       inet_ntop(AF_INET, &this->_their_addr.sin_addr, host, NI_MAXHOST);
       std::cout << host << " connected on port " << ntohs(this->_their_addr.sin_port) << std::endl;
   }
    return ;
}

int Listening::getNewfd(void)
{
    return(this->_new_fd);
}

Listening::Listening(Listening const &src)
{
    *this = src;
    return ;
}

const char * Listening::ListenException::what(void) const throw()
{
    return("Can't listen");
}

const char * Listening::AcceptException::what(void) const throw()
{
    return("Problem with connecting ");
}

Listening::~Listening(void)
{
    return ;
}
