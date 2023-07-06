/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_checker.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:27:50 by mel-kora          #+#    #+#             */
/*   Updated: 2023/07/05 21:50:57 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Configuration.hpp"

void	Server_info::server_checker()
{
	if (host == "")
		host = "0.0.0.0";
	if (port == -1)
		port = 80;
	if (body_size == -1)
		body_size = 1000000;
	if (locations.size() > 0)
	{
		std::map<std::string, Location>::iterator j = locations.begin();
		
		while (j != locations.end())
		{
			if ((*j).second.autoindex == -1)
				(*j).second.autoindex = 0;
			if ((*j).second.root == "")
			{
				if (root == "")
					ft_exit("Missing root detected 🤖");
				(*j).second.root = root;
			}
			if ((*j).second.methods.size() == 0)
				(*j).second.methods = methods;
			j++;
		}
	}
	else
		ft_exit("Missing location block detected 🤖");
}

void	Configuration::print_config()
{
	std::vector<Server_info>::iterator i = servers.begin();
	int	server_id = 1;

	while (i != servers.end())
	{
		std::cout << "***************** Server " << server_id << " info: *****************\n";
		std::cout << "* listening on " << (*i).host << ':' << (*i).port << "\n";
		std::cout << "* server names:\n";
		print_vector((*i).server_names);
		std::cout << "* error pages:\n";
		print_map((*i).error_pages);
		std::cout << "* client max body size: " << (*i).body_size << "\n";
		if ((*i).locations.size())
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
	print_vector(location.methods);
	output << " - Indexes: \n";
	print_vector(location.indexes);
	output << " - Uploads: \n";
	print_vector(location.uploads);
	output << " - Returns: \n";
	print_map(location.returns);
	output << " - CGI: \n";
	print_map(location.cgi);
	return (output);
}

int	is_number(std::string input)
{
	size_t	i = 0;
	
	if (input.size() == 0)
		return (0);
	while (i < input.size() && isdigit(input[i]))
		i++;
	if (i == input.size())
		return (1);
	return (0);
}
