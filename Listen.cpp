#include "Listen.hpp"

Listening::Listening(void)
{
    FD_ZERO(&this->_master);
    return;
}

Listening & Listening::operator=(Listening const &rhs)
{
    if(this == &rhs)
        return(*this);
    this->_new_fd = rhs._new_fd;
    this->_their_addr = rhs._their_addr;
    return(*this);
}

void Listening::listenin(int sock, int backlog)
{
    (void) backlog;
    if(listen(sock, SOMAXCONN) == -1)
        throw ListenException();
    FD_SET(sock, &this->_master);
    return ;
}

void Listening::accept(int listening)
{
    bool running = true;
    int count=1;
    int fdmax = listening;

	while (running)
	{
        fd_set copy = this->_master;
    	int socketCount = select(fdmax+1, &copy, nullptr, nullptr, nullptr);
    	for (int i = 0; i < fdmax; i++)
    	{
    			int sock = copy.fds_bits[i];
    			if (sock == listening)
    			{
    				int client = ::accept(listening, nullptr, nullptr);
    				FD_SET(client, &this->_master);
                    count++;
    				std::string welcomeMsg = "Welcome to the Awesome Chat Server!\r\n";
    				send(client, welcomeMsg.c_str(), welcomeMsg.size() + 1, 0);
    			}
    			else
    			{
    				char buf[4096];
    				memset(buf, 0, 4096);
    				int bytesIn = recv(sock, buf, 4096, 0);
    				if (bytesIn <= 0)
    				{
    					close(sock);
    					FD_CLR(sock, &this->_master);
    				}
    				else
    				{
    					if (buf[0] == '\\')
    					{
    						std::string cmd = std::string(buf, bytesIn);
    						if (cmd == "\\quit")
    						{
    							running = false;
    							break;
    						}
    						continue;
    					}
    			        for (int i = 0; i < count; i++)
    					{
    						int outSock = this->_master.fds_bits[i];
    						if (outSock != listening && outSock != sock)
    						{
    							std::ostringstream ss;
    							ss << "SOCKET #" << sock << ": " << buf << "\r\n";
    							std::string strOut = ss.str();

    							send(outSock, strOut.c_str(), strOut.size() + 1, 0);
    						}
    					}
    				}
    			}
		    }
        }
   // //  char host[NI_MAXHOST];
   //  char service[NI_MAXSERV];
   //  unsigned int sin_size = sizeof(struct sockaddr);
   //
   //  memset(host, 0, NI_MAXHOST);
   //  memset(service, 0, NI_MAXSERV);
   //  this->_new_fd = ::accept(sock, (struct sockaddr *) &this->_their_addr, &sin_size);
   //  if(this->_new_fd == -1)
   //      throw AcceptException();
   //  if (getnameinfo((sockaddr*)&this->_their_addr, sin_size, host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
   //     std::cout << host << " connected on port " << service << std::endl;
   //  else
   //  {
   //     inet_ntop(AF_INET, &this->_their_addr.sin_addr, host, NI_MAXHOST);
   //     std::cout << host << " connected on port " << ntohs(this->_their_addr.sin_port) << std::endl;
   // }
    return ;
}

int Listening::getNewfd(void)
{
    return(this->_new_fd);
}

Listening::Listening(Listening const &src)
{
    *this = src;
    return ;
}

const char * Listening::ListenException::what(void) const throw()
{
    return("Can't listen");
}

const char * Listening::AcceptException::what(void) const throw()
{
    return("Problem with connecting ");
}

Listening::~Listening(void)
{
    return ;
}
