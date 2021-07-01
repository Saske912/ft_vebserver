//
// Created by Pamula File on 5/8/21.
//

#ifndef SERVER_HPP
#define SERVER_HPP
#include <iostream>
#include <string>
#include <list>
#include <map>
#include "route.hpp"
#include "../wpersimm.h"
#include <fcntl.h>
#include <queue>

class config;
class Header;

class server {
public:
    server();
    server(std::string  const & host, unsigned int port, const std::map<int, std::string>& error_pages,
             std::list<route> const & routs, long int client_body_size = 1);
    ~server();
    server( server const &src );
    server &operator=( server const &src );

    std::string                 get_host() const;
    void                        set_host(std::string  const & host);
    unsigned int                get_port() const;
    void                        set_port(unsigned int port);
    const std::list<std::string>&      get_server_names() const;
    void                        set_server_names(std::list<std::string>  const & server_name);
	void                        add_server_name(std::string  const & server_name);
    const std::map<int, std::string>&     get_error_pages() const;
    void                        set_error_pages(std::map<int, std::string> const & err_pages);
    void						add_error_page(int error_code, const std::string &filename);
    long int                    get_client_body_size() const;
	void                        set_client_body_size(long int size);
    const std::list<route>&            get_routes() const;
    void						add_route(const route &route_);
    std::map<int, std::string>  get_def_error_pages() const;
    std::pair<std::string, std::string> getAllow() const;
    void                        setAllow(const std::pair<std::string, std::string>& allow);
    std::string                 getCgiPath() const;
    void                        setCgiPath(const std::string &cgi_path);
    int                         exception_processing(int except, Header &head);
    void                        concat( Header & head );
    int                         autoindex( Header &head, route route );
    void descriptorForSend( Header &head);
    int                         descriptorForReceive( Header &head);
    const std::list<std::string> &getListOfMethods( ) const;
    void setListOfMethods( const std::list<std::string> &listOfMethods );
    std::list<Header> &getSet( );
    void setSet( const std::list<Header> &set );
    int getHostSock( ) const;
    void setHostRaw( int hostRaw );
    config *getConf( ) const;
    void setConf( config *conf );
    bool head_in_set(Header &head);
    bool operator==(Header const & head) const;
    fd_set                      read;
    sockaddr_in                 addr;
protected:
    void cgi_processing( Header &head, bool flag );
    void handle_cgi_response_headers(int fd, Header &head);
    static bool                 is_file_with_extension( std::string request);
	bool                        is_file( const std::string& request);
    void is_cgi( Header &head );
    std::string                 get_error(int, std::map<int, std::string> ers);
    void                        set_default_pages();
    std::string                 get_allow(std::list<std::string> arr);
    void                        set_list_of_methods();
    std::string                 set_location(route &  route, Header &  head);
private:
    config                              *_conf;
    std::list<Header>                   _set;
    std::string                         _host;
    unsigned int                        _port;
    std::list<std::string>              _server_names;
    std::map<int, std::string>          _error_pages;
    std::map<int, std::string>          _default_error_pages;
    std::list<route>                    _routs;
    long int                            _client_body_size;
    std::list<std::string>              _list_of_methods;
    std::pair<std::string, std::string> _allow;
    std::string                         _cgi_path;
    int                                 _host_socket;
};

std::ostream &operator<<(std::ostream &o, const server &serv);

#endif //SERVER_HPP
