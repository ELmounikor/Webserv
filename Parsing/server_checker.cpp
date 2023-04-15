/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_checker.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:27:50 by mel-kora          #+#    #+#             */
/*   Updated: 2023/04/15 16:15:09 by mel-kora         ###   ########.fr       */
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
	if (server.locations.size() > 0)
	{
		std::map<std::string, Location>::iterator j = server.locations.begin();

		while (j != server.locations.end())
		{
			if ((*j).second.autoindex == -1)
				(*j).second.autoindex = 0;
			if ((*j).second.root == "")
			{
				if (server.root == "")
					ft_exit("Missing root detected 🤖");
				(*j).second.root = server.root;
			}
			if ((*j).second.methods.size() == 0)
			{
				// if (server.methods.size() == 0)
				// 	ft_exit("Missing http methods detected 🤖");
				(*j).second.methods = server.methods;
			}
			j++;
		}
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
		std::cout << "* listening on " << (*i).host << ':' << (*i).port << "\n";
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
		std::cout << "* client max body size: " << (*i).body_size << "\n";
		if ((*i).locations.size() > 0)
		{
			std::map<std::string, Location>::iterator j = (*i).locations.begin();

			while (j != (*i).locations.end())
			{
				std::cout << "* location '" << (*j).first << "' info:\n";
				std::cout << (*j).second;
				j++;
			}
		}
		i++;
		server_id++;
	}
}

std::ostream	&operator<<( std::ostream &output, const Location &location)
{
	output << " - Autoindex: " << location.autoindex << "\n";
	output << " - Root: " << location.root << "\n";
	output << " - HTTP methods: \n";
	if (location.methods.size() == 0)
		std::cout << "-->(none)\n";
	else
		print_vector(location.methods);
	if (location.indexes.size() > 0)
	{
		output << " - Indexes: \n";
		print_vector(location.indexes);
	}
	if (location.uploads.size() > 0)
	{
		output << " - Uploads: \n";
		print_vector(location.uploads);
	}
	if (location.returns.size() > 0)
	{
		output << " - Returns: \n";
		print_map(location.returns);
	}
	if (location.returns.size() > 0)
	{
		output << " - CGI: \n";
		print_map(location.returns);
	}
	return (output);
}
