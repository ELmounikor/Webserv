/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Configuration.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:16:16 by mel-kora          #+#    #+#             */
/*   Updated: 2023/04/09 18:25:07 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Configuration.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

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
	if (content[start] != '{')
		ft_exit("Bad input 👿");
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
		ft_exit("Unclosed block 🤖");
	return (content.substr(start, end - start));
}

void	Configuration::parse_content(std::string content)
{
	size_t	start = 0, end = 0;

	while (end < content.length())
	{
		start = content.find("server") + 7;
		if (trim_spaces(content.substr(end, start - end - 6)) != "")
			ft_exit("Something is fishy 🐡");
		parse_server_block(get_block(content, start, end));
		start = end;
	}
}

void	Configuration::parse_server_block(std::string block)
{
	Server	server;
	size_t	start = 0, end = 0;

	
}

void	Configuration::parse_location_block(Server	&serv, std::string location_match, std::string block)
{
	Location	location;
	size_t		start = 0, end = 0;

	
}


/*
** --------------------------------- METHODS ----------------------------------
*/


/* ************************************************************************** */