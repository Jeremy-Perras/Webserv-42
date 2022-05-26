#ifndef SOCKET_H
# define SOCKET_H
# include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>

class Socket
{
    public:
        Socket(int domain, int type, int protocol, int port, u_long ip);
        Socket & operator=(Socket const &rhs);
        Socket(Socket const &src);
        ~Socket(void);





    private:
        Socket(void);
        struct sockaddr_in _address;
        int _server_fd;
};


#endif
