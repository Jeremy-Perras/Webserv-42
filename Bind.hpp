#ifndef BIND_H
# define BIND_H
# include"Socket.hpp"
# include <sys/types.h>
# include <sys/socket.h>
# include <iostream>


class Binding : public Socket
{
    public:
        Binding(void);
        Binding(int domain, int type, int protocol, int port , char *ip);
        Binding& operator=(Binding const &rhs);
        Binding(Binding const &src);
        ~Binding(void);
        void connect_network(int sock);
        class BindException : public std::exception
        {
            public:
            virtual const char* what() const throw();
        };
    private:

};

#endif
