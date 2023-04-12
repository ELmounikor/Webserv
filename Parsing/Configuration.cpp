/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Configuration.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:16:16 by mel-kora          #+#    #+#             */
/*   Updated: 2023/04/12 16:05:14 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Configuration.hpp"

Location::Location(): autoindex(-1), root("")
{}

Server::Server(): root(""), host(""), port(-1), body_size(-1)
{}

Configuration::Configuration(std::string file_name)
{
	std::string	content;
	std::ifstream conf_file(file_name);
	if (!conf_file.is_open())
		ft_exit("Cannot open configuration file 👽");
	std::getline(conf_file, content, '\0');
	parse_content(content);
    conf_file.close();
}

std::string	trim_spaces(std::string input)
{
	size_t i = 0, j = input.size() - 1;

	while (i < input.length() && isspace(input[i]))
		i++;
	while (j >= 0 && isspace(input[j]))
		j--;
	return (input.substr(i, j - i + 1));
}

std::string get_block(std::string content, size_t &start, size_t &end)
{
	int	open_brackets = 0;
	
	while (start < content.length() && isspace(content[start]))
		start++;
	if (start == content.length() || content[start] != '{')
		ft_exit("Bad input detected 🤖");
	end = start++;
	open_brackets++;
	while (++end < content.length() && open_brackets)
	{
		if (content[end] == '{')
			open_brackets++;
		else if (content[end] == '}')
			open_brackets--;
	}
	if (open_brackets)
		ft_exit("Unclosed block detected 🤖");
	return (content.substr(start, end - start));
}

void	Configuration::parse_content(std::string content)
{
	size_t	start = 0, end = 0;

	while (end < content.length())
	{
		start = content.find("server") + 7;
		if (trim_spaces(content.substr(end, start - end - 6)) != "")
			ft_exit("Something's fishy detected 🤖");
		parse_server_block(get_block(content, start, end));
		start = end;
	}
}

void	Configuration::parse_server_block(std::string block)
{
	Server	server;
	size_t	start = 0, end = 0;

	while (start < block.length())
	{
		end = block.find("\n");
		if (parse_server_line(server, block.substr(start, end - start)) == "location")
		{
			end = start;
			start = block.substr(start, block.find("\n") - start + 1).find("{") + 1;
			std::string location_match = get_valid_path(trim_spaces(block.substr(end, start - end)));
			parse_location_block(server, location_match, get_block(block, start, end));
		}
		start = ++end;
	}
	this->servers.push_back(server_checker(server));
}

std::string	Configuration::parse_server_line(Server &serv, std::string line)
{
	std::string	server_parameters[] = {"root", "listen", "host", "body_size", "server_name", "methods", "index", "error_page", "location"};
	std::string	parameter, argument;
	size_t		start = 0, end = 0;

	while (start < line.length() && isspace(line[start]))
		start++;
	if (start == line.length())
		return ("");
	end = start;
	while (end < line.length() && !isspace(line[end]))
		end++;
	parameter = line.substr(start, end - start + 1);
	argument = trim_spaces(line.substr(end, line.size() - end));
	if (argument[argument.size() - 1] == ';')
		argument = argument.substr(0, argument.size() - 1);
	int i = 0;
	while (i < 9 && parameter != server_parameters[i])
		i++;
	switch (i)
	{
		case 0:
			get_root(serv, argument);
			break;
		case 1:
			get_port(serv, argument);
			break;
		case 2:
			get_host(serv, argument);
			break;
		case 3:
			get_body_size(serv, argument);
			break;
		case 4:
			get_server_name(serv, argument);
			break;
		case 5:
			get_methods(serv, argument);
			break;
		case 6:
			get_index(serv, argument);
			break;
		case 7:
			get_error_page(serv, argument);
			break;
		case 8:
			break;
		default:
			ft_exit("Bad server parameter detected 🤖");
	}
	return (parameter);
}

void	Configuration::parse_location_block(Server	&serv, std::string location_match, std::string block)
{
	Location	location;
	size_t		start = 0, end = 0;

	while (start < block.length())
	{
		end = block.find("\n");
		parse_location_line(location, block.substr(start, end - start));
		start = ++end;
	}
	serv.locations[location_match] = location;
}

void	Configuration::parse_location_line(Location &location, std::string line)
{
	std::string	location_parameters[] = {"autoindex", "root", "methods", "index", "upload", "return", "cgi"};
	std::string	parameter, argument;
	size_t		start = 0, end = 0;

	while (start < line.length() && isspace(line[start]))
		start++;
	if (start == line.length())
		return ;
	end = start;
	while (end < line.length() && !isspace(line[end]))
		end++;
	parameter = line.substr(start, end - start + 1);
	argument = trim_spaces(line.substr(end, line.size() - end));
	if (argument == "")
		ft_exit("No argument provided for " + parameter);
	if (argument[argument.size() - 1] == ';')
		argument = argument.substr(0, argument.size() - 1);
	int i = 0;
	while (i < 7 && parameter != location_parameters[i])
		i++;
	switch (i)
	{
		case 0:
			get_location_autoindex(location, argument);
			break;
		case 1:
			get_location_root(location, argument);
			break;
		case 2:
			get_location_methods(location, argument);
			break;
		case 3:
			get_location_index(location, argument);
			break;
		case 4:
			get_location_upload(location, argument);
			break;
		case 5:
			get_location_return(location, argument);
			break;
		case 6:
			get_location_cgi(location, argument);
			break;
		default:
			ft_exit("Bad location parameter detected 🤖");
	}
}

std::string get_valid_path(std::string path)
{
	size_t	start = 0, end = path.size();
	if (end == 0)
		ft_exit("Missing Path detected 🤖");
	while (start < end && !isspace(path[start]))
		start++;
	if (start < end)
		ft_exit("Invalid space character in path detected 🤖");
	return (path);
}