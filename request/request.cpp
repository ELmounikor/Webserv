/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 20:11:15 by sennaama          #+#    #+#             */
/*   Updated: 2023/05/31 18:55:04 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "request.hpp"

request::request():status_code(-1), method(""),path(""),version(""){}

std::string trim(std::string str) {

    size_t pos = str.find_first_not_of(" \t\r\n");
    if (pos != std::string::npos) {
        str.erase(0, pos);
    }

    pos = str.find_last_not_of(" \t\r\n");
    if (pos != std::string::npos) {
        str.erase(pos + 1);
    }

    return str;
}


int countcharacter(std::string str, char c)
{
    int count = 0;
    size_t pos = 0;
    while ((pos = str.find(c, pos)) != std::string::npos)
    {
        count++;
        pos++;
    }
    return count;
}

void request::request_parse(std::string buf)
{
    std::string line;
    std::string key, value;
    std::string name_file = "body_file";

   // std::cout<<"---------------"<<std::endl;
    //std::cout<<buf;
    // buf = "GET / HTTP/1.1\n"
    //     "Host: localhost:8080\r\n"
    //     "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.14; rv:109.0) Gecko/20100101 Firefox/113.0\r\n"
    //     "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8\r\n"
    //     "Accept-Language: en-US,en;q=0.5\r\n"
    //     "Accept-Encoding: gzip, deflate, br\r\n"
    //     "Connection: keep-alive\r\n"
    //     "Upgrade-Insecure-Requests: 1\r\n"
    //     "Sec-Fetch-Dest: document\r\n"
    //     "Sec-Fetch-Mode: navigate\r\n"
    //     "Sec-Fetch-Site: none\r\n"
    //     "Sec-Fetch-User: ?1\r\n"
    //     "\r\n";
    std::istringstream s(buf);
    if (getline(s, line))
    {
        std::istringstream sq(line);
        if (countcharacter(line, ' ') == 2 && (std::getline(sq, method, ' ') && std::getline(sq, path, ' ')))
        {
            sq >> version;
            if ((method.empty() || path.empty() || version.empty()) ||\
               (method != "GET" && method != "POST" && method != "DELETE") || \
                (version != "HTTP/1.1"))
            {
                status_code = 400;
                std::cout << "Version: " << version << "\nMethod: " << method << "\nPath: " << path << std::endl;
                return ;
            }
        }
        else 
        {
            status_code = 400;
            return ;
        }
    }
    if (method == "POST")
    {
        if ((buf.find("Content-Length") == std::string::npos && buf.find("Transfer-Encoding") == std::string::npos)
            || (buf.find("Content-Length") != std::string::npos && buf.find("Transfer-Encoding") != std::string::npos))
        {
            status_code = 400;
            return ;
        }
    }
        
    while (std::getline(s, line) && !line.empty() && line != "\r")
    {
        size_t pos = line.find(':');
        if (pos != std::string::npos) 
        {
            key = line.substr(0, pos);
            for (size_t i = 0; i < key.length(); i++) 
            {
                if (std::isspace(key[i])) 
                {
                    status_code = 400;
                    return ;
                }
            }
            value = line.substr(pos + 2);
            
            if (value.find_first_not_of(" ") > 1 || value[value.length() - 1] != '\r')
            {
                status_code = 400;
                return ;
            }
            header[key] = trim(value);
            
        }
        else 
        {
            status_code = 400;
            return ;
        }
    }
    if (line != "\r")
    {
        status_code = 400;
        return ;
    }
    else
    {
        if (method == "GET")
        {
            status_code = 400;
            return;
        }
        // else if (method == "POST")
        // {
        //     //std::cout<<"bodyyyy"<<std::endl;
        //     body_file.open(name_file);
        //     if (!body_file.is_open()) 
        //         return ;
        //     s >> line;
        //     body_file << line;
        //     body_file.close();
        // }
    }
    //print_request();    
}

request::~request(){}  

void request::print_request()
{
    if (status_code == 400)
    {
        std::cout<<"\nBAD REQUEST\n"<<std::endl;
        return;
    }
    std::cout << "Method: " << method << std::endl;
    std::cout << "Path: " << path << std::endl;
    std::cout << "Version: " << version << std::endl;
    std::map<std::string, std::string>::iterator iter;
    for (iter = header.begin(); iter != header.end(); ++iter) {
       std::cout << iter->first <<" : " << iter->second << std::endl;
    }
}                                                                                                 