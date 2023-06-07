/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Attributes.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:00:51 by mel-kora          #+#    #+#             */
/*   Updated: 2023/06/07 13:25:39 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

void	Response::get_host_nd_port(std::string value)
{
	size_t	start = 0;

	port = 80;
	while (start < value.size() && value[start] != ':')
		start++;
	if (start != value.size())
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

void	Response::get_server(request req)
{
	
}

void	Response::get_location(request req)
{
	
}
