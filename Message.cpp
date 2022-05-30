#include "Message.hpp"

Msg::Msg(void)
{
    return;
}

Msg & Msg::operator=(Msg const &rhs)
{
    if(this == &rhs)
        return(*this);
    return (*this);
}

Msg::Msg(Msg const &src)
{
    *this = src;
    return ;
}

void Msg::Recv(int sock)
{
    int bytes_recv;
    char buf[500];
    int i;

    bytes_recv = recv(sock, buf, 500, 0);
    read(sock, buf, 1);
    // char buffer[30000] = {0};
    // read(sock, buffer, 30000);
    printf("%s\n",buf );
}

void Msg::Send(int sock)
{
    std::ostringstream oss;
    oss << "HTTP/1.1 " << "errorCode"<< " OK\r\n";
	oss << "Cache-Control: no-cache, private\r\n";
	oss << "Content-Type: text/html\r\n";
	oss << "Content-Length: " << "content.size()" << "\r\n";
	oss << "\r\n";
    oss << "<h1> Hello </h1>";
    oss << "<h2> Hello2 </h2>";
    std::string output = oss.str();
	int size = output.size() + 1;
    char msg[250] = "Beej etait la! ";
    int len, bytes_sent;
    len = strlen(msg);
    bytes_sent = send(sock, output.c_str(), size, 0);
}

Msg::~Msg(void)
{
    return ;
}
