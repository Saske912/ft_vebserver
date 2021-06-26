//
// Created by Pamula File on 5/6/21.
//
#include "header.h"

sockaddr_in init_host_addr( unsigned int port, const std::string& host )
{
    sockaddr_in         addr;
    in_addr_t           in_addr = inet_addr(host.c_str());

    if (in_addr == INADDR_NONE)
    {
        std::cerr << "inet_addr: malformed addr" << std::endl;
        exit(1);
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = in_addr;
    return (addr);
}

void init_serv( config &config )
{
    int     sock;

    std::list<server>::iterator it = config.getServers().begin();
    while ( it != config.getServers().end())
    {
        it->addr = init_host_addr(it->get_port(), it->get_host());
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == -1)
            error_exit("socket error");
        it->setHostRaw(sock);
        config.opt = 1;
        setsockopt( it->getHostSock( ), SOL_SOCKET, SO_REUSEADDR, &config.opt, sizeof(config.opt));
        if ( config.opt != 1)
            error_exit("SO_REUSEADDR");
        config.opt = BUFSIZE;
        setsockopt( it->getHostSock( ), SOL_SOCKET, SO_RCVBUF, &config.opt, sizeof(config.opt));
        if ( config.opt != BUFSIZE)
            error_exit("SO_RCVBUF");
        if ( bind( it->getHostSock( ), reinterpret_cast<sockaddr *>(&it->addr), sizeof(it->addr)) == -1)
            error_exit("fail to bind IP");
        if ( listen( it->getHostSock( ), QUEUE) == -1)
            error_exit("listening error");
        it++;
    }
}
