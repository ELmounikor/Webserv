/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 20:11:15 by sennaama          #+#    #+#             */
/*   Updated: 2023/06/18 19:41:38 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "request.hpp"

request::request():status_code(-1), method(""),path(""),version(""), size(0), contentLength(0),flag(-1) {}

std::string	request::trim(std::string str) {

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


int	request::countcharacter(std::string str, char c)
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

std::string	request::get_extension(std::string content_type) {
	std::map<std::string, std::string> extension;
    extension["audio/aac"] = ".aac";
    extension["application/x-abiword"] = ".abw";
    extension["application/x-freearc"] = ".arc";
    extension["image/avif"] = ".avif";
    extension["video/x-msvideo"] = ".avi";
    extension["application/vnd.amazon.ebook"] = ".azw";
    extension["application/octet-stream"] = ".bin";
    extension["image/bmp"] = ".bmp";
    extension["application/x-bzip"] = ".bz";
    extension["application/x-bzip2"] = ".bz2";
    extension["application/x-cdf"] = ".cda";
    extension["application/x-csh"] = ".csh";
    extension["text/css"] = ".css";
    extension["text/csv"] = ".csv";
    extension["application/msword"] = ".doc";
    extension["application/vnd.openxmlformats-officedocument.wordprocessingml.document"] = ".docx";
    extension["application/vnd.ms-fontobject"] = ".eot";
    extension["application/epub+zip"] = ".epub";
    extension["application/gzip"] = ".gz";
    extension["image/gif"] = ".gif";
    extension["text/html"] = ".html";
    extension["image/vnd.microsoft.icon"] = ".ico";
    extension["text/calendar"] = ".ics";
    extension["application/java-archive"] = ".jar";
    extension["image/jpeg"] = ".jpeg";
    extension["text/javascript"] = ".js";
    extension["application/json"] = ".json";
    extension["application/ld+json"] = ".jsonld";
    extension["audio/midi"] = ".mid";
    extension["audio/x-midi"] = ".midi";
    extension["text/javascript"] = ".mjs";
    extension["audio/mpeg"] = ".mp3";
    extension["video/mp4"] = ".mp4";
    extension["video/mpeg"] = ".mpeg";
    extension["application/vnd.apple.installer+xml"] = ".mpkg";
    extension["application/vnd.oasis.opendocument.presentation"] = ".odp";
    extension["application/vnd.oasis.opendocument.spreadsheet"] = ".ods";
    extension["application/vnd.oasis.opendocument.text"] = ".odt";
    extension["audio/ogg"] = ".oga";
    extension["video/ogg"] = ".ogv";
    extension["application/ogg"] = ".ogx";
    extension["audio/opus"] = ".opus";
    extension["font/otf"] = ".otf";
    extension["image/png"] = ".png";
    extension["application/pdf"] = ".pdf";
    extension["application/x-httpd-php"] = ".php";
    extension["application/vnd.ms-powerpoint"] = ".ppt";
    extension["application/vnd.openxmlformats-officedocument.presentationml.presentation"] = ".pptx";
    extension["application/vnd.rar"] = ".rar";
    extension["application/rtf"] = ".rtf";
    extension["application/x-sh"] = ".sh";
    extension["image/svg+xml"] = ".svg";
    extension["application/x-tar"] = ".tar";
    extension["image/tiff"] = ".tiff";
    extension["video/mp2t"] = ".ts";
    extension["font/ttf"] = ".ttf";
    extension["text/plain"] = ".txt";
    extension["application/vnd.visio"] = ".vsd";
    extension["audio/wav"] = ".wav";
    extension["audio/webm"] = ".weba";
    extension["video/webm"] = ".webm";
    extension["image/webp"] = ".webp";
    extension["font/woff"] = ".woff";
    extension["font/woff2"] = ".woff2";
    extension["application/xhtml+xml"] = ".xhtml";
    extension["application/vnd.ms-excel"] = ".xls";
    extension["application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"] = ".xlsx";
    extension["application/xml"] = ".xml";
    extension["application/vnd.mozilla.xul+xml"] = ".xul";
    extension["application/zip"] = ".zip";
    extension["video/3gpp"] = ".3gp";
    extension["video/3gpp2"] = ".3g2";
    extension["application/x-7z-compressed"] = ".7z";
    std::map<std::string, std::string>::iterator it = extension.find(content_type);
    if (it != extension.end()) {
        return it->second;
    }
    return extension["application/octet-stream"];
}

void    request::header_parse(std::string buf)
{
    std::istringstream	s(buf);
    std::string			line, key, value;
	
    if (getline(s, line) && method == "")
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
                return ;
            }
        }
        else 
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
}

void	request::get_method(std::string assign)
{
	if (!assign.empty() || header.find("Content-Type") != header.end() \
		|| header.find("Content-Length") != header.end()\
		|| header.find("Transfer-Encoding") != header.end())
		status_code = 400;
}

void	request::appendtofile(std::string str, std::string filename) 
{
    std::ofstream outputfile(filename, std::ios::app);
    if (!outputfile) {
        std::cerr << "Error opening the file." << std::endl;
        return;
    }

    outputfile << str;
    outputfile.close();
}

int hextointeger(const std::string& hexString) {
    std::istringstream iss(hexString);
    int result;
    iss >> std::hex >> result;
    return result;
}

bool isValidContentLength(std::string contentLength) {
    std::stringstream ss(contentLength);
    size_t length;
    ss >> length;
    if (ss.fail() || !ss.eof()) 
        return false;
    size_t maxContentLength = std::numeric_limits<size_t>::max();
    size_t minContentLength = 0;
    return length >= minContentLength && length <= maxContentLength;
}

void	request::post_method(std::string assign, int socket_client)
{
	std::stringstream st;
	std::string name_file;
    
	if (assign.empty() || header.find("Content-Type") == header.end() \
		|| (header.find("Content-Length") == header.end()\
		&& header.find("Transfer-Encoding") == header.end()) || \
		(header.find("Content-Length") != header.end()\
		&& header.find("Transfer-Encoding") != header.end()))
	{
		status_code = 400;
		return ;
	}
	st << socket_client;
    st >> name_file;
    name_file = "body_file_" + name_file + get_extension(header["Content-Type"]);
    if (header.find("Content-Length") != header.end())
	{
        if (!isValidContentLength(header["Content-Length"]))
        {
            status_code = 400;
            return ;
        }
        size += assign.length();
	    if (size < atoi(header["Content-Length"].c_str()))
		    flag = 1;
	    else
		    flag = -1;
    }
    // else
    // {
    //     if (header["Transfer-Encoding"] != "chunked")
    //     {
    //         status_code = 400;
    //         return ;
    //     }
    //     std::string hexvalue;
    //     if (size == 0)
    //     {
    //         std::cout<<"------"<<assign<<"------"<<std::endl;
    //         size_t pos = assign.find("\r\n");
    //         if (pos != std::string::npos)
    //         {      
    //             size_t pos_start = 0;
    //             if (pos == 0)
    //             {
    //                 std::cout<<"----------"<<std::endl;
    //                 pos_start = 2;  
    //                 pos = assign.find("\r\n", 2);
    //             }   
    //             hexvalue = assign.substr(pos_start,pos);
    //             assign.erase(0, pos + strlen("\r\n"));
    //             size = hextointeger(hexvalue);
    //             if (size > 0)
    //                 flag = 1;
    //             else 
    //                 flag = -1;
    //             std::cout<<"size = "<<size<<" lenght ="<< assign.length()<<std::endl;
    //         }
    //         //size -= assign.length();
    //     //     hv = size;
    //     }
    //     else 
    //     {
    //         size_t len = assign.length();
    //         len -=size;
    //         if (len <= 0)
    //             size -= assign.length();
    //         else 
    //         {
    //             size_t pos1 = assign.find("\r\n", len);
    //             if (pos1 != std::string::npos)
    //             {
    //                 size_t pos2 = assign.find("\r\n", pos1 + 2);
    //                 if (pos2 != std::string::npos)
    //                 {
    //                     hexvalue = assign.substr(pos1 + 2,pos2 - (pos1 + 2));
    //                     // std::cout<<hexvalue<<std::endl;
    //                     assign.erase(pos1, pos2 + strlen("\r\n"));
    //                     size = hextointeger(hexvalue);
    //                     //std::cout<<"--->"<<size<<std::endl;
    //                     if (size > 0)
    //                         flag = 1;
    //                     else
    //                         flag = -1;
    //                     //size -= assign.length();
    //                 }
    //                 else
    //                 {
    //                     assign.erase(pos1, pos1 + strlen("\r\n"));
    //                     //size -= assign.length();
    //                 }
    //             }
    //         }
            
    //         //size -= assign.length();
    //         // size_t i;
    //         // for (i = 0; size > 0 && i < assign.length(); i++)
    //         // {
               
    //         //     size--;
    //         // std::cout<<"+++++++++size = "<<size << " "<< i <<" lenght ="<< assign.length()<<std::endl;
    //         // }
    //         // if (size == 0 && i < assign.length())
    //         // {
               
    //         //     if (assign[i] == '\r' && assign[i+1] == '\n')
    //         //     {
    //         //         std::cout<<"++++++++"<<std::endl;
    //         //         i = i + 2;
    //         //     }
    //         //     if (i != assign.length())
    //         //     {
    //         //         size_t pos = assign.find("\r\n", i);
    //         //         hexvalue = assign.substr(i,pos);
    //         //         assign.erase( i - 2, pos + strlen("\r\n"));
    //         //         size = hextointeger(hexvalue);
    //         //         if (size > 0)
    //         //             flag = 1;
    //         //         else 
    //         //             flag = -1;
    //         //     }
    //         // }
            
            
    //     }
        
    // }
	appendtofile(assign, name_file); 
	//std::cout<<"body ==> "<<assign << "size : " << size <<std::endl;
}

void    request::request_parse(std::string assign, int socket_client)
{
	// stdj::cout<<"---------------"<<std::endl;
    //std::cout<<buf<<"\n\n";
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
	
    size_t pos_header_end = assign.find("\r\n\r\n");
    if (pos_header_end != std::string::npos && flag == -1)
    {
        header_parse(assign);
		if (status_code == 400)
			return ;
		assign.erase(0, pos_header_end + strlen("\r\n\r\n"));
    }
    else if (pos_header_end == std::string::npos && flag == -1)
    {
        status_code = 400;
        return ;
    }
	if (method == "GET")
    	get_method(assign);
	else if (method == "POST")
		post_method(assign, socket_client);
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