/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 20:11:15 by sennaama          #+#    #+#             */
/*   Updated: 2023/05/22 16:28:42 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "request.hpp"

request::request():status_code(-1), method(""),path(""),version(""){}

int countSpaces(std::string str)
{
    int count = 0;
    size_t pos = 0;
    while ((pos = str.find(' ', pos)) != std::string::npos)
    {
        count++;
        pos++;
    }
    return count;
}

void request::request_parse(std::string buf)
{
    std::string request_line;
    std::string key, value;
    //std::cout<<buf;
    //buf = "GET / HTTP/1.1\nHost: localhost:8080 \nUser-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.14; rv:109.0) Gecko/20100101 Firefox/113.0 \nAccept: text/html,application/xhtml+xml, application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8\nAccept-Language: en-US,en;q=0.5\nAccept-Encoding: gzip, deflate, br\nConnection: keep-alive\nUpgrade-Insecure-Requests: 1\nSec-Fetch-Dest: document\nSec-Fetch-Mode: navigate\nSec-Fetch-Site: none\nSec-Fetch-User: ?1\n";
    std::istringstream s(buf);
    if (getline(s, request_line))
    {
        std::istringstream sq(request_line);
        if (countSpaces(request_line) == 2 && (std::getline(sq, method, ' ') && std::getline(sq, path, ' ')))
        {
            sq >> version;
            if ((method.empty() || path.empty() || version.empty()) ||\
               (method != "GET" && method != "POST" && method != "DELETE") || \
                (version != "HTTP/1.1"))
            {
                status_code = 400;
                std::cout<<"\nBAD REQUEST\n"<<std::endl;
                std::cout << "Version: " << version << "\nMethod: " << method << "\nPath: " << path << std::endl;
                return ;
            }
            std::cout << "Method: " << method << std::endl;
            std::cout << "Path: " << path << std::endl;
            std::cout << "Version: " << version << std::endl;
        }
        else 
        {
            status_code = 400;
            std::cout<<"\nBAD REQUEST\n"<<std::endl;
            return ;
        }
    }
}
request::~request(){}