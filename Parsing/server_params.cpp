/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_params.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 10:26:41 by mel-kora          #+#    #+#             */
/*   Updated: 2023/05/13 17:00:30 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Configuration.hpp"

void	get_root(Server &serv, std::string argument)
{
	if (serv.root != "")
		ft_exit("Duplicate root in a single server detected 🤖");
	serv.root = get_valid_path(argument);
}

void	get_port(Server &serv, std::string argument)
{
	size_t	start = 0;
	long	port;
	
	if (serv.port != -1)
		ft_exit("Duplicate port in a single server detected 🤖");
	while (start < argument.size() && argument[start] != ':')
		start++;
	if (start != argument.size())
		get_host(serv, argument.substr(0, start++));
	else
		start = 0;
	argument = argument.substr(start, argument.size());
	port = strtol(argument.c_str(), NULL, 10);
	if (!is_number(argument) || port > 65535)
		ft_exit("Invalid port detected 🤖");
	serv.port = port;
}

void	get_host(Server &serv, std::string argument)
{
	size_t	start = 0, end = 0;
	long	byte, number_of_bytes = 0;
	
	if (serv.host != "")
		ft_exit("Duplicate host in a single server detected 🤖");
	while (start < argument.size())
	{
		while (end < argument.size() && isdigit(argument[end]))
			end++;
		std::string token = argument.substr(start, end - start);
		byte = strtol(token.c_str(), NULL, 10);
		number_of_bytes++;
		if (!is_number(token) || byte > 255 || (argument[end] != '.' && number_of_bytes < 4) || number_of_bytes > 4)
			ft_exit("Invalid host address detected 🤖");
		start = ++end;
	}
	serv.host = argument;
}

void	get_body_size(Server &serv, std::string argument)
{
	long	body_size_max;
	
	if (serv.body_size != -1)
		ft_exit("Duplicate client body size limit detected 🤖");
	body_size_max = strtol(argument.c_str(), NULL, 10);
	if (!is_number(argument))
		ft_exit("Invalid client body size limit detected 🤖");
	serv.body_size = body_size_max;
}

void	get_server_name(Server &serv, std::string argument)
{
	size_t	start = 0, end = 0;

	while (start < argument.size())
	{
		while (end < argument.size() && !isspace(argument[end]))
			end++;
		std::string token = argument.substr(start, end - start);
		serv.server_names.push_back(token);
		while (end < argument.size() && isspace(argument[end]))
			end++;
		start = end;
	}
}

void	get_methods(Server &serv, std::string argument)
{
	std::string allowed_methods[] = {"GET", "POST", "DELETE"};
	size_t	start = 0, end = 0;

	while (start < argument.size())
	{
		while (end < argument.size() && !isspace(argument[end]))
			end++;
		int i = 0;
		std::string token = argument.substr(start, end - start);
		while (i < 3 && token != allowed_methods[i])
			i++;
		if (i < 3)
		{
			std::vector<std::string>::iterator j = serv.methods.begin();
			while (j != serv.methods.end() && token != *j)
				j++;
			if (j == serv.methods.end())
				serv.methods.push_back(token);
		}
		else
			ft_exit("Invalid method detected 🤖");
		while (end < argument.size() && isspace(argument[end]))
			end++;
		start = end;
	}
}

void	get_index(Server &serv, std::string argument)
{
	size_t	start = 0, end = 0;

	while (start < argument.size())
	{
		while (end < argument.size() && !isspace(argument[end]))
			end++;
		std::string token = argument.substr(start, end - start);
		serv.indexes.push_back(token);
		while (end < argument.size() && isspace(argument[end]))
			end++;
		start = end;
	}
}

void	get_error_page(Server &serv, std::string argument)
{
	size_t				start = 0, end = 0;
	std::vector<long>	errpage_codes;
	std::string			path;

	while (start < argument.size())
	{
		while (end < argument.size() && !isspace(argument[end]))
			end++;
		std::string token = argument.substr(start, end - start);
		if (is_number(token))
		{
			long code = strtol(token.c_str(), NULL, 10);
			if (code < 300 || code > 599)
				ft_exit("Error page code out of range (300-599)"); 
			errpage_codes.push_back(code);
		}
		else
			break;
		while (end < argument.size() && isspace(argument[end]))
			end++;
		start = end;
	}
	if (errpage_codes.size() == 0)
		ft_exit("Invalid error page code detected 🤖");
	path = get_valid_path(argument.substr(start, argument.size() - start));
	std::vector<long>::iterator i = errpage_codes.begin();
	while (i != errpage_codes.end())
	{
		if (serv.error_pages.find(*i) != serv.error_pages.end())
			ft_exit("Duplicate error page code detected 🤖");
		serv.error_pages[*i] = path;
		i++;
	}
}
