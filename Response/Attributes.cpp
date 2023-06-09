/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Attributes.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:00:51 by mel-kora          #+#    #+#             */
/*   Updated: 2023/06/09 19:41:47 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

void	Response::get_host_nd_port(std::string value)
{
	size_t	start = 0;

	port = 80;
	start = value.find(":");
	if (start != 0)
	{
		host = value.substr(0, start++);
		value = value.substr(start, value.size());
		port = strtol(value.c_str(), NULL, 10);
	}
	else
		host = value;
	if (host == "localhost")
		host = "127.0.0.1";
}

void	Response::get_server(Configuration conf)
{
	std::vector<Server_info>::iterator serv_i = conf.servers.begin();
	
	if (is_ip_address(host))
	{
		while (serv_i != conf.servers.end())
		{
			if (((*serv_i).host == host || (*serv_i).host == "0.0.0.0") && (*serv_i).port == port)
			{
				server = &(*serv_i);
				break ;
			}
			serv_i++;
		}
	}
	else
	{
		std::vector<std::string>::iterator servname_i;
		
		while (serv_i != conf.servers.end())
		{
			if ((*serv_i).port == port)
			{
				servname_i = (*serv_i).server_names.begin();
				while (servname_i != (*serv_i).server_names.end() && *servname_i != host)
					servname_i++;
				if (*servname_i == host)
				{
					server = &(*serv_i);
					break ;
				}
				serv_i++;
			}
		}
	}
	if (!server)
		server = &(*(conf.servers.begin()));
}

void	Response::get_location(request &req, Configuration conf)
{
	if (req.header.find("host") != req.header.end())
	{
		get_host_nd_port(req.header["host"]);
		get_server(conf);
		std::string request_uri = req.path;
		std::map<std::string, Location>::iterator location_i  = server->locations.find(request_uri);
			if (location_i != server->locations.end())
			{
				location = &((*location_i).second);
				// break ;
			}
			request_uri = request_uri.substr(0, request_uri.size() - 1);
	}
	else
		server = &(*(conf.servers.begin()));
}
