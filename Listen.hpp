#ifndef LISTEN_H

# define LISTEN_H
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
#include <iostream>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/select.h>
 #include <sys/time.h>
 #include <sys/types.h>
 #include <unistd.h>
 #include <string>
 #include <sstream>

class Listening
{

    public:
        Listening(void);
        Listening& operator=(Listening const &rhs);
        Listening(Listening const &src);
        ~Listening(void);
        void listenin(int sock, int backlog);
        void accept(int sock);
        int getNewfd(void);
        class ListenException : public std::exception
        {
            public:
                virtual const char *what() const throw();
        };
        class AcceptException : public std::exception
        {
            public:
                virtual const char *what() const throw();
        };
    private:
        int _new_fd;
        struct sockaddr_in _their_addr;
        fd_set _master;
};







#endif
