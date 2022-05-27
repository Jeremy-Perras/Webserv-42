#include <iostream>
#include "Socket.hpp"
#include "Bind.hpp"
#include "Listen.hpp"
#include "Message.hpp"

int main(void)
{
    Listening listen;
    Msg Message;
    Binding bind(AF_INET, SOCK_STREAM, 0, 80, 0);
    bind.connect_network(bind.getFd());
    listen.listenin(bind.getFd(), 5);
    listen.accept(bind.getFd());
    Message.Send(bind.getFd());

    return (0);
}
