/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Attributes.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:00:51 by mel-kora          #+#    #+#             */
/*   Updated: 2023/06/17 23:27:47 by mel-kora         ###   ########.fr       */
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

Server_info	search_by_servername(Response &res, Configuration conf, std::string server_name)
{
	std::vector<Server_info>::iterator serv_i = conf.servers.begin();
	std::vector<std::string>::iterator servname_i;
	Server_info server;
		
	while (serv_i != conf.servers.end())
	{
		if ((*serv_i).port == res.port)
		{
			servname_i = (*serv_i).server_names.begin();
			while (servname_i != (*serv_i).server_names.end() && *servname_i != server_name)
				servname_i++;
			if (servname_i != (*serv_i).server_names.end())
				return (*serv_i);
		}
		serv_i++;
	}
	return (server);
}

Server_info	Response::get_server(request &req, Configuration conf)
{
	std::vector<Server_info>::iterator serv_i = conf.servers.begin();
	Server_info server;
	
	if (req.status_code == -1 && req.header.find("Host") != req.header.end())
	{
		get_host_nd_port(req.header["Host"]);
		if (host == "127.0.0.1")
		{
			server = search_by_servername(*this, conf, "localhost");
			if (server.port != -1)
				return (server);
		}
		if (is_ip_address(host))
		{
			while (serv_i != conf.servers.end())
			{
				if ((*serv_i).host == host && (*serv_i).port == port)
					return (*serv_i);
				serv_i++;
			}
			serv_i = conf.servers.begin();
			while (serv_i != conf.servers.end())
			{
				if ((*serv_i).host == "0.0.0.0" && (*serv_i).port == port)
					return (*serv_i);
				serv_i++;
			}
		}
		else
			server = search_by_servername(*this, conf, host);
	}
	else
		status_code = 400;
	if (server.port == -1)
		return (*(conf.servers.begin()));
	return (server);
}

Location	Response::get_location(request &req, Server_info server)
{
	Location location;
	std::string request_uri = req.path;
	if (request_uri.size() == 0 || request_uri[0] != '/')
		request_uri = "/" + request_uri;
	std::map<std::string, Location>::iterator location_i  = server.locations.find(request_uri);
	if (location_i != server.locations.end())
	{
		location_name = (*location_i).first;
		return ((*location_i).second);
	}
	if (request_uri[request_uri.size() - 1] == '/')
		request_uri = request_uri.substr(0, request_uri.size() - 1);
	while (1)
	{
		std::string request_uri_copy = request_uri + "/";
		std::map<std::string, Location>::iterator location_j  = server.locations.find(request_uri_copy);
		location_i  = server.locations.find(request_uri);
		if (location_j != server.locations.end())
		{
			location_name = (*location_j).first;
			return ((*location_j).second);
		}
		else if (location_i != server.locations.end())
		{
			location_name = (*location_i).first;
			return ((*location_i).second);
		}
		else if (request_uri.size() == 0)
			return (location);
		request_uri = get_next_option(request_uri);
		to_fetch = req.path.substr(request_uri.size() + 1, req.path.size());
	}
	return (location);
}

void	Response::print_response_attr(Server_info server, Location location)
{
	std::cout << "\033[0;96m*** Responding to " << host << ":" << port << " ***\033[0m" << std::endl;
	std::cout << "- status: " << status_code << SP + get_status_message() << std::endl;
	std::cout << "- to_fetch: " << to_fetch << std::endl;
	std::cout << "- location_name: " << location_name + "\n";
	if (server.port != -1)
	{
		std::cout << "- server_info: "<< server.host << ":" << server.port << "\n";
		std::cout << " * client max body size: " << server.body_size << "\n";
		std::cout << " * error pages:\n";
		print_map(server.error_pages);
		// std::cout << " * server names:\n";
		// print_vector(server.server_names);
		// std::cout << " * locations:\n";
		// print_map(server.locations);
	}
	else
		std::cout << "- no server\n";
	if (location.autoindex != -1)
		std::cout << "- location '" << location_name << "' info:\n" << location;
	else
		std::cout << "- no location\n";
	std::cout << "\033[0;96m*** END ***\033[0m" << std::endl;
}
