/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_checker.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:27:50 by mel-kora          #+#    #+#             */
/*   Updated: 2023/04/12 17:14:35 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Configuration.hpp"

Server	server_checker(Server &server)
{
	if (server.host == "")
		server.host = "0.0.0.0";
	if (server.port == -1)
		server.port = 80;
	if (server.body_size == -1)
		server.body_size = 1000000;
	//need to check error pages and locations info
	if (server.locations.size() > 0)
	{
		std::map<std::string, Location>::iterator i = server.locations.begin();

		while (i != server.locations.end())
			i++;
	}
	return (server);
}

void	print_config(Configuration config)
{
	std::vector<Server>::iterator i = config.servers.begin();
	int	server_id = 1;

	while (i != config.servers.end())
	{
		std::cout << "***************** Server " << server_id << " info: *****************\n";
		std::cout << "* listening on :" << (*i).host << ':' << (*i).port << "\n";
		if ((*i).server_names.size() > 0)
		{
			std::cout << "* server names:\n";
			print_vector((*i).server_names);
		}
		if ((*i).error_pages.size() > 0)
		{
			std::cout << "* error pages:\n";
			print_map((*i).error_pages);
		}
		std::cout << "* client max body size :" << (*i).body_size << "\n";
		i++;
		server_id++;
	}
	
}