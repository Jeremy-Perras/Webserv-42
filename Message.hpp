#ifndef MESSAGE_H
# define MESSAGE_H
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <sstream>
#include <fstream>
#include <string>

class Msg
{
    public:
        Msg(void);
        Msg& operator=(Msg const &rhs);
        Msg(Msg const &src);
        ~Msg(void);
        void Send(int sock, char *buf);
        void Recv(int sock);
        char *getBuf(void);
        class RecvException : public std::exception
        {
            public:
                virtual const char* what() const throw();
        };
        class RecvClientException : public std::exception
        {
            public:
                virtual const char* what() const throw();
        };
    private:
        //int _bytes_sent;
        int _bytes_recv;
        char buf[4096];
};

#endif
