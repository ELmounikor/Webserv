/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Attributes.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:00:51 by mel-kora          #+#    #+#             */
/*   Updated: 2023/06/12 15:27:04 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

void	Response::get_host_nd_port(std::string host_value)
{
	size_t	start = 0;

	port = 80;
	start = host_value.find(':');
	if (start < host_value.size())
	{
		host = host_value.substr(0, start++);
		host_value = host_value.substr(start, host_value.size());
		port = strtol(host_value.c_str(), NULL, 10);
	}
	else
		host = host_value;
	if (host == "localhost")
		host = "127.0.0.1";
}

void	search_by_servername(Response &res, Configuration conf, std::string server_name)
{
	std::vector<Server_info>::iterator serv_i = conf.servers.begin();
	std::vector<std::string>::iterator servname_i;
		
	while (serv_i != conf.servers.end())
	{
		if ((*serv_i).port == res.port)
		{
			servname_i = (*serv_i).server_names.begin();
			while (servname_i != (*serv_i).server_names.end() && *servname_i != server_name)
				servname_i++;
			if (*servname_i == server_name)
			{
				res.server = &(*serv_i);
				break ;
			}
			serv_i++;
		}
	}
}

void	Response::get_server(Configuration conf)
{
	std::vector<Server_info>::iterator serv_i = conf.servers.begin();
	
	if (host == "127.0.0.1")
	{
		search_by_servername(*this, conf, "localhost");
		if (server)
			return ;
	}
	if (is_ip_address(host))
	{
		while (serv_i != conf.servers.end())
		{
			if ((*serv_i).host == host && (*serv_i).port == port)
			{
				server = &(*serv_i);
				return ;
			}
			serv_i++;
		}
		if (serv_i == conf.servers.end())
		{
			serv_i = conf.servers.begin();
			while (serv_i != conf.servers.end())
			{
				if ((*serv_i).host == "0.0.0.0" && (*serv_i).port == port)
				{
					server = &(*serv_i);
					return ;
				}
				serv_i++;
			}
		}
	}
	else
		search_by_servername(*this, conf, host);
	if (!server)
		server = &(*(conf.servers.begin()));
}

std::string	get_next_option(std::string request_uri)
{
	size_t last_slash_pos = request_uri.rfind('/');
	if (last_slash_pos < request_uri.size())
		return (request_uri.substr(0, last_slash_pos));
	return (request_uri);
}

void	Response::get_location(request &req, Configuration conf)
{	
	
	if (req.status_code == -1 && req.header.find("Host") != req.header.end())
	{
		get_host_nd_port(req.header["Host"]);
		get_server(conf);
		std::string request_uri = req.path;
		if (request_uri.size() == 0 || request_uri[0] != '/')
			request_uri = "/" + request_uri;
		std::map<std::string, Location>::iterator location_i  = server->locations.find(request_uri);
		if (location_i != server->locations.end())
		{
			location = &((*location_i).second);
			return ;
		}
		if (request_uri[request_uri.size() - 1] == '/')
			request_uri = request_uri.substr(0, request_uri.size() - 1);
		while (request_uri.size() > 0)
		{
			std::string request_uri_copy = request_uri + "/";
			std::map<std::string, Location>::iterator location_j  = server->locations.find(request_uri_copy);
			location_i  = server->locations.find(request_uri);
			if (location_j != server->locations.end())
			{
				location = &((*location_j).second);
				return ;
			}
			else if (location_i != server->locations.end())
			{
				location = &((*location_i).second);
				return ;
			}
			request_uri = get_next_option(request_uri);
		}
	}
	else
	{
		server = &(*(conf.servers.begin()));
		status_code = 400;
	}
}

void	Response::print_response_attr(void)
{
	std::cout << "\033[0;96m*** Responding to " << host << ":" << port << " ***\033[0m" << std::endl;
	std::cout << "- status: " << status_code << SP + get_status_message() << std::endl;
	std::cout << "- url: " << location_name + to_fetch + "\n";
	if (server)
	{
		std::cout << "- server_info: "<< server->host << ":" << server->port << "\n";
		std::cout << " * server names:\n";
		print_vector(server->server_names);
		std::cout << " * error pages:\n";
		print_map(server->error_pages);
		std::cout << " * client max body size: " << server->body_size << "\n";
	}
	else
		std::cout << "- no server\n";
	if (location)
		std::cout << "- location '" << location_name << "' info:\n" << location;
	else
		std::cout << "- no location\n";
	std::cout << "\033[0;96m*** END ***\033[0m" << std::endl;
}
