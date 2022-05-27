#ifndef SOCKET_H
# define SOCKET_H
# include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


class Socket
{
    public:
        Socket(void);
        Socket(int domain, int type, int protocol, int port, u_long ip);
        Socket & operator=(Socket const &rhs);
        Socket(Socket const &src);
        ~Socket(void);
        int getFd(void);
        struct sockaddr_in getAdress(void);
    protected:
        struct sockaddr_in _address;
    private:
        int _server_fd;
};


#endif
