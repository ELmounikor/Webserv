/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Configuration.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:16:16 by mel-kora          #+#    #+#             */
/*   Updated: 2023/05/19 16:39:13 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Configuration.hpp"

Location::Location(): autoindex(-1), root("")
{}

Server_info::Server_info(): port(-1), body_size(-1), root(""), host("")
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

	while (i < input.size() && isspace(input[i]))
		i++;
	while (j >= 0 && isspace(input[j]))
		j--;
	return (input.substr(i, j - i + 1));
}

std::string get_block(std::string content, size_t &start, size_t &end)
{
	int	open_brackets = 0;
	
	while (start < content.size() && isspace(content[start]))
		start++;
	if (start == content.size() || content[start] != '{')
		ft_exit("Bad input detected 🤖");
	end = start++;
	open_brackets++;
	while (++end < content.size() && open_brackets)
	{
		if (content[end] == '{')
			open_brackets++;
		else if (content[end] == '}')
			open_brackets--;
	}
	if (open_brackets)
		ft_exit("Unclosed block detected 🤖");
	return (content.substr(start, end - start - 1));
}

void	Configuration::parse_content(std::string content)
{
	size_t	tmp, end = 0;

	while (trim_spaces(content) != "")
	{
		end = content.find("server") + 7;
		if (trim_spaces(content.substr(0, end - 7)) != "")
			ft_exit("Something's fishy detected 🤖");
		parse_server_block(get_block(content, end, tmp));
		content = content.substr(tmp, content.size());
	}
}

void	Configuration::parse_server_block(std::string block)
{
	Server_info	server;
	size_t	start, end = 0;

	while (trim_spaces(block) != "")
	{
		start = 0;
		end = block.find("\n");
		if (parse_server_line(server, block.substr(0, end)) == "location")
		{
			while (start < block.size() && isspace(block[start]))
				start++;
			while (start < block.size() && !isspace(block[start]))
				start++;
			while (start < block.size() && isspace(block[start]))
				start++;
			end = start;
			while (end < block.size() && !isspace(block[end]))
				end++;
			std::string location_match = get_valid_path(block.substr(start, end - start));
			start = end;
			parse_location_block(server, location_match, get_block(block, start, end));
		}
		block = block.substr(++end, block.size());
	}
	this->servers.push_back(server_checker(server));
}

std::string	Configuration::parse_server_line(Server_info &serv, std::string line)
{
	std::string	server_parameters[] = {"root", "listen", "host", "body_size", "server_name", "methods", "index", "error_page", "location"};
	std::string	parameter, argument;
	size_t		start = 0, end = 0;

	while (start < line.size() && isspace(line[start]))
		start++;
	if (start == line.size())
		return ("");
	if (line[start] == '#')
		return ("comment");
	end = start;
	while (end < line.size() && !isspace(line[end]))
		end++;
	parameter = line.substr(start, end - start);
	if (line[line.size() - 1] == ';')
		line = line.substr(0, line.size() - 1);
	argument = trim_spaces(line.substr(end, line.size()));
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

void	Configuration::parse_location_block(Server_info	&serv, std::string location_match, std::string block)
{
	Location	location;
	size_t		end = 0;

	while (trim_spaces(block) != "")
	{
		end = block.find("\n");
		parse_location_line(location, block.substr(0, end));
		block = block.substr(++end, block.size());
	}
	if (serv.locations.find(location_match) == serv.locations.end())
		serv.locations[location_match] = location;
}

void	Configuration::parse_location_line(Location &location, std::string line)
{
	std::string	location_parameters[] = {"autoindex", "root", "methods", "index", "upload", "return", "cgi"};
	std::string	parameter, argument;
	size_t		start = 0, end = 0;

	while (start < line.size() && isspace(line[start]))
		start++;
	if (start == line.size())
		return ;
	if (line[start] == '#')
		return ;
	end = start;
	while (end < line.size() && !isspace(line[end]))
		end++;
	parameter = line.substr(start, end - start);
	if (line[line.size() - 1] == ';')
		line = line.substr(0, line.size() - 1);
	argument = trim_spaces(line.substr(end, line.size() - end));
	if (argument == "")
		ft_exit("No argument provided for " + parameter);
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
