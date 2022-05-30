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

    std::string ip = "127.0.0.1";
    Binding bind(AF_INET, SOCK_STREAM, 0, 8080, (char *) ip.c_str());
    std::ostringstream oss;

    bind.connect_network(bind.getFd());
    listen.listenin(bind.getFd(), 5);
    listen.accept(bind.getFd());
    close(bind.getFd());
    Message.Send(listen.getNewfd());
    while(1)
    {
        usleep(50);
        Message.Recv(listen.getNewfd());
        //write(bind.getFd(), "hello", strlen("hello"));
        //write(listen.getNewfd(), "hello", strlen("hello"));

    }
    close(listen.getNewfd());

    return (0);
}



    //
    //
	// sendToClient(clientSocket, output.c_str(), size);
