//
// Created by Pamula File on 6/17/21.
//
#include "header.h"

std::string get_http_line( std::string &buffer, Header &head, server &serv )
{
    std::string line;
    size_t      finder;

    if ((finder = buffer.find("\r\n")) == std::string::npos)
    {
        head.setReminder(head.getReminder() + buffer);
        return std::string();
    }
    line = head.getReminder() + buffer.substr(0, finder);
    head.setReminder(std::string());
    buffer.erase(0, finder + 2);
//    head.setBuffer(buffer);
    return parse_request( line, head, serv );
}
