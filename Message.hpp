#ifndef MESSAGE_H
# define MESSAGE_H
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
#include <iostream>

class Msg
{
    public:
        Msg(void);
        Msg& operator=(Msg const &rhs);
        Msg(Msg const &src);
        ~Msg(void);
        void Send(int sock);
        void Recv(int sock);
    private:
};

#endif
