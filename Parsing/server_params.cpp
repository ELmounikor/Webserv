/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_params.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 10:26:41 by mel-kora          #+#    #+#             */
/*   Updated: 2023/04/11 18:50:45 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Configuration.hpp"

void	get_root(Server &serv, std::string argument)
{
	if (serv.root != "")
		ft_exit("Duplicate root in a single server");
	serv.root = get_valid_path(argument);
}

void	get_port(Server &serv, std::string argument)
{
	size_t	start = 0, end = 0;
	long	port;
	char	*terminator;
	
	if (serv.port)
		ft_exit("Duplicate port");
	while (start < argument.size() && argument[start] != ':')
		start++;
	if (start != argument.size())
		get_host(serv, argument.substr(0, start));
	else
		start = 0;
	port = strtol(argument.c_str(), &terminator, 10);
	if (terminator || !isdigit(argument[0]) || port > 65535)
		ft_exit("Invalid port");
	serv.port = port;
}

void	get_host(Server &serv, std::string argument)
{
	size_t	start = 0, end = 0;
	long	byte, number_of_bytes = 0;
	char	*terminator;
	
	if (serv.host != "")
		ft_exit("Duplicate host");
	while (start < argument.size())
	{
		while (end < argument.size() && argument[end] != '.')
			end++;
		std::string token = argument.substr(start, end - start);
		byte = strtol(token.c_str(), &terminator, 10);
		number_of_bytes++;
		if (terminator || !isdigit(token[0]) || byte > 255 || number_of_bytes > 4)
			ft_exit("Invalid host address");
		start = end;
	}
	serv.host = argument;
}

void	get_body_size(Server &serv, std::string argument)
{
	long	body_size;
	char	*terminator;
	
	if (body_size)
		ft_exit("Duplicate client body size limit");
	body_size = strtol(argument.c_str(), &terminator, 10);
	if (terminator || !isdigit(argument[0]))
		ft_exit("Invalid client body size limit");
	serv.body_size = body_size;
}

void	get_server_name(Server &serv, std::string argument)
{
	size_t	start = 0, end = 0;

	while (start < argument.size())
	{
		while (end < argument.size() && !isspace(argument[end]))
			end++;
		int i = 0;
		std::string token = argument.substr(start, end - start + 1);
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
		std::string token = argument.substr(start, end - start + 1);
		while (i < allowed_methods->size() && token != allowed_methods[i])
			i++;
		if (i < allowed_methods->size())
		{
			std::vector<std::string>::iterator j = serv.methods.begin();
			while (j != serv.methods.end() && token != *j)
				j++;
			if (j == serv.methods.end())
				serv.methods.push_back(token);
		}
		else
			ft_exit("Invalid method detected");
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
		int i = 0;
		std::string token = argument.substr(start, end - start + 1);
		serv.indexes.push_back(token);
		while (end < argument.size() && isspace(argument[end]))
			end++;
		start = end;
	}
}

void	get_error_page(Server &serv, std::string argument)
{
	size_t		start = 0, end = 0;
	char		*terminator;
	long		errpage_code;
	std::string	path;

	while (end < argument.size() && !isspace(argument[end]))
		end++;
	std::string token = argument.substr(start, end - start + 1);
	errpage_code = strtol(token.c_str(), &terminator, 10);
	if (terminator || !isdigit(token[0]))
		ft_exit("Invalid error page code");
	while (end < argument.size() && isspace(argument[end]))
		end++;
	serv.error_pages[errpage_code] = get_valid_path(argument.substr(end, argument.size() - end));
}
