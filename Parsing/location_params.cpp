/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location_params.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 10:25:59 by mel-kora          #+#    #+#             */
/*   Updated: 2023/07/09 20:51:03 by mel-kora         ###   ########.fr       */
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
	long		redirection_code;
	std::string	path;

	if (location.returns.size() > 0)
		ft_exit ("Duplicate redirection in a single location detected 🤖");
	while (end < argument.size() && !isspace(argument[end]))
		end++;
	std::string token = argument.substr(start, end - start);
	redirection_code = strtol(token.c_str(), NULL, 10);
	if (!is_number(token) || (redirection_code != 301 && redirection_code != 302 && redirection_code != 307 && redirection_code != 308))
		ft_exit("Invalid HTTP redirection code in location detected 🤖");
	while (end < argument.size() && isspace(argument[end]))
		end++;
	location.returns[redirection_code] = get_valid_path(argument.substr(end, argument.size() - end));
}

void	get_location_cgi(Location &location, std::string argument)
{
	std::string		allowed_cgi[] = {".pl", ".py", ".php"};
	std::string		extension;
	size_t			end = 0;

	while (end < argument.size() && !isspace(argument[end]))
		end++;
	extension = argument.substr(0, end);
	if (extension.size() == 0 || extension[0] != '.')
		ft_exit ("Invalid extention detected 🤖");
	while (end < argument.size() && isspace(argument[end]))
		end++;
	int i = 0;
	while (extension == allowed_cgi[i])
		i++;
	if (i == 3)
		ft_exit ("Unimplemented extention detected 🤖");
	if (location.cgi.find(extension) != location.cgi.end())
		ft_exit ("More than one " + extension.substr(1, extension.size()) + " CGI of in a single location detected 🤖");
	location.cgi[extension] = get_valid_path(argument.substr(end, argument.size()));
}
