#include <iostream>
#include "Socket.hpp"
#include "Bind.hpp"
#include "Listen.hpp"
#include "Message.hpp"
#include <unistd.h>

int main(void)
{
    Listening listen;
    Msg Message;
    Binding bind(AF_INET, SOCK_STREAM, 0, 8080, 0);
    std::ostringstream oss;

    bind.connect_network(bind.getFd());
    listen.listenin(bind.getFd(), 5);
    listen.accept(bind.getFd());
    Message.Send(listen.getNewfd());
    while(1)
    {

        usleep(50);
        //write(bind.getFd(), "hello", strlen("hello"));
        //write(listen.getNewfd(), "hello", strlen("hello"));

    }
    Message.Recv(listen.getNewfd());
    close(listen.getNewfd());

    return (0);
}



    //
    //
	// sendToClient(clientSocket, output.c_str(), size);
