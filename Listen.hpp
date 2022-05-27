#ifndef LISTEN_H

# define LISTEN_H
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
#include <iostream>

class Listening
{

    public:
        Listening(void);
        Listening& operator=(Listening const &rhs);
        Listening(Listening const &src);
        ~Listening(void);
        void listenin(int sock, int backlog);
        void accept(int sock);

    private:
        int _listen;
        int _new_fd;
        struct sockaddr_in _their_addr;

};







#endif
