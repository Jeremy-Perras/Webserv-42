#include "Bind.hpp"

int Bind::connect_network(int sock, struct sockadrr_in address)
{
    return(bind(sock,(struct sockaddr *) &address), sizeof)
}
