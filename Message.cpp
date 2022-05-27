#include "Message.hpp"

Msg::Msg(void)
{
    return;
}

Msg & Msg::operator=(Msg const &rhs)
{
    if(this == &rhs)
        return(*this);
    return (*this);
}

Msg::Msg(Msg const &src)
{
    *this = src;
    return ;
}

void Msg::Recv(int sock)
{
    int bytes_recv;
    char buf[250];
     bytes_recv = recv(sock, buf, 250, 0);

}

void Msg::Send(int sock)
{
    char msg[250] = "Beej était là!";
    int len, bytes_sent;
    len = strlen(msg);
    bytes_sent = send(sock, msg, len, 0);
}



Msg::~Msg(void)
{
    return ;
}
