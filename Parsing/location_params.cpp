/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location_params.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 10:25:59 by mel-kora          #+#    #+#             */
/*   Updated: 2023/04/15 14:41:56 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Configuration.hpp"

void	get_location_autoindex(Location &location, std::string argument)
{
	if (location.autoindex != -1)
		ft_exit("Duplicate autoindex in a single location detected 🤖");
	if (argument == "on")
		location.autoindex = 1;
	else if (argument == "off")
		location.autoindex = 0;
	else
		ft_exit("Invalid value off autoindex detected 🤖");
}

void	get_location_root(Location &location, std::string argument)
{
	if (location.root != "")
		ft_exit("Duplicate root in a single location detected 🤖");
	location.root = get_valid_path(argument);
}

void	get_location_methods(Location &location, std::string argument)
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
			std::vector<std::string>::iterator j = location.methods.begin();
			while (j != location.methods.end() && token != *j)
				j++;
			if (j == location.methods.end())
				location.methods.push_back(token);
		}
		else
			ft_exit("Invalid method detected 🤖");
		while (end < argument.size() && isspace(argument[end]))
			end++;
		start = end;
	}
}

void	get_location_index(Location &location, std::string argument)
{
	size_t	start = 0, end = 0;

	while (start < argument.size())
	{
		while (end < argument.size() && !isspace(argument[end]))
			end++;
		std::string token = argument.substr(start, end - start);
		location.indexes.push_back(token);
		while (end < argument.size() && isspace(argument[end]))
			end++;
		start = end;
	}
}

void	get_location_upload(Location &location, std::string argument)
{
	location.uploads.push_back(get_valid_path(argument));
}

void	get_location_return(Location &location, std::string argument)
{
	size_t		start = 0, end = 0;
	char		*terminator;
	long		redirection_code;
	std::string	path;

	if (location.returns.size() > 0)
		ft_exit ("Duplicate redirection in a single location detected 🤖");
	while (end < argument.size() && !isspace(argument[end]))
		end++;
	std::string token = argument.substr(start, end - start);
	redirection_code = strtol(token.c_str(), &terminator, 10);
	if (terminator == NULL || !isdigit(token[0]))
		ft_exit("Invalid redirection page code detected 🤖");
	while (end < argument.size() && isspace(argument[end]))
		end++;
	location.returns[redirection_code] = get_valid_path(argument.substr(end, argument.size() - end));
}

void	get_location_cgi(Location &location, std::string argument)
{
	size_t			start = 0, end = 0;
	std::string		extention;

	if (location.cgi.size() > 0)
		ft_exit ("Duplicate CGI in a single location detected 🤖");
	while (end < argument.size() && !isspace(argument[end]))
		end++;
	extention = argument.substr(start, end - start);
	while (end < argument.size() && isspace(argument[end]))
		end++;
	location.cgi[extention] = get_valid_path(argument.substr(end, argument.size() - end));
}
