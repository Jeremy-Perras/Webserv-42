#ifndef BIND_H
# define BIND_H
# include"Socket.hpp"
# include <sys/types.h>
# include <sys/socket.h>


class Binding : public Socket
{
    public:
        Binding(int domain, int type, int protocol, int port , u_long ip);
        Binding& operator=(Binding const &rhs);
        Binding(Binding const &src);
        ~Binding(void);
        int connect_network(int sock);

    private:
        // struct sockaddr_in _address;



};

#endif
