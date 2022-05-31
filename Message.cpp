#include "Message.hpp"

Msg::Msg(void)
{
    memset(buf, 0, 4096);
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
    // int bytes_recv;
    // char buf[500];
    // int i;
    //
    this->_bytes_recv = recv(sock, this->buf, 4096, 0);
    if(this->_bytes_recv == -1)
     throw RecvException();
    if(this->_bytes_recv == 0)
      throw RecvClientException();
    std::cout << std::string(this->buf, 0, this->_bytes_recv) << std::endl;

    // read(sock, buf, 1);
    // printf("%s\n",buf );
}

char * Msg::getBuf(void)
{
    return(this->buf);
}

void Msg::Send(int sock, char *buf)
{
     send(sock, buf, this->_bytes_recv + 1, 0);
    // std::ostringstream oss;
    // oss << "HTTP/1.1 " << "errorCode"<< " OK\r\n";
	// oss << "Cache-Control: no-cache, private\r\n";
	// oss << "Content-Type: text/html\r\n";
	// oss << "Content-Length: " << "content.size()" << "\r\n";
	// oss << "\r\n";
    // oss << "<h1> Hello </h1>";
    // oss << "<h2> Hello2 </h2>";
    // std::string output = oss.str();
	// int size = output.size() + 1;
    // char msg[250] = "Beej etait la! ";
    // int len, bytes_sent;
    // len = strlen(msg);
    // this->bytes_sent = send(sock, output.c_str(), size, 0);
}

const char * Msg::RecvException::what() const throw()
{
    return("Error in recv(). Quitting");
}

const char * Msg::RecvClientException::what() const throw()
{
    return("Client disconnected");
}

Msg::~Msg(void)
{
    return ;
}
