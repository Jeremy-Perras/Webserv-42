#include <iostream>
#include "Socket.hpp"
#include "Bind.hpp"
#include "Listen.hpp"
#include "Message.hpp"
#include <unistd.h>

int main(void)
{

    try
    {
        Listening listen;
        Msg Message;

        Binding bind(AF_INET, SOCK_STREAM, 0, 8080, 0);

        bind.connect_network(bind.getFd());
        listen.listenin(bind.getFd(), 5);
        listen.accept(bind.getFd());
    }
    catch(std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return (0);
}
