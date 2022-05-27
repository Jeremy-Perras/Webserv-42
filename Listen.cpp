#include "Listen.hpp"

Listening::Listening(void)
{
    return;
}

Listening & Listening::operator=(Listening const &rhs)
{
    if(this == &rhs)
        return(*this);
    this->_listen = rhs._listen;
    this->_new_fd = rhs._new_fd;
    //this->_their_addr = rhs._their_addr; mettre les parametres
    return(*this);
}

void Listening::listenin(int sock, int backlog)
{
    this->_listen = listen(sock, backlog);
    return ;
}

void Listening::accept(int sock)
{
    unsigned int sin_size = sizeof(struct sockaddr);
    this->_new_fd = ::accept(sock, (struct sockaddr *) &this->_their_addr, &sin_size);
    return ;
}

Listening::Listening(Listening const &src)
{
    *this = src;
    return ;
}


Listening::~Listening(void)
{
    return ;
}
