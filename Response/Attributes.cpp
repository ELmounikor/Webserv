/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Attributes.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:00:51 by mel-kora          #+#    #+#             */
/*   Updated: 2023/06/08 16:33:12 by mel-kora         ###   ########.fr       */
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
	(void) conf;
	if (is_ip_address(host))
	{
		//check by host:port
	}
	else
	{
		//check by server_name:port then sever_name
	}
}

void	Response::get_location(request &req, Configuration conf)
{
	if (req.header.find("host") != req.header.end())
	{
		get_host_nd_port(req.header["host"]);
		get_server(conf);
		if (!server)
			server = &(*(conf.servers.begin()));
		
	}
	else
		server = &(*(conf.servers.begin()));
}
