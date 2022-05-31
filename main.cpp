#include <iostream>
#include "Socket.hpp"
#include "Bind.hpp"
#include "Listen.hpp"
#include "Message.hpp"
#include <unistd.h>

int main(void)
{
    fd_set copy;
    (void) copy;
    try
    {
        Listening listen;
        Msg Message;

        std::string ip = "127.0.0.1";
        Binding bind(AF_INET, SOCK_STREAM, 0, 8080, (char *) ip.c_str());
        std::ostringstream oss;

        bind.connect_network(bind.getFd());
        listen.listenin(bind.getFd(), 5);
        listen.accept(bind.getFd());
        // close(bind.getFd());
        // while(true)
        // {
        //     Message.Recv(listen.getNewfd());
        //     Message.Send(listen.getNewfd(), Message.getBuf());
        // }
        // close(listen.getNewfd());
    }
    catch(std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return (0);
}
