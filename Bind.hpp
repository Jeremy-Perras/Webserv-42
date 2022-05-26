#ifndef BIND_H
# define BIND_H
# include"Sicket.hpp"

class Bind : public Socket
{
    public:
        Bind(void);
        Bind& operator=(Bind const &rhs);
        Bind(Bind const &src)
        ~Bind(void);
        int connect_network(int sock, struct sockadrr_in address);




    private:



}

#endif
