/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Configuration.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:16:09 by mel-kora          #+#    #+#             */
/*   Updated: 2023/04/11 16:08:27 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGURATION_HPP
# define CONFIGURATION_HPP
# include "../lib.hpp"

class Location
{
	public:
		int									autoindex;
		std::string							root;
		std::vector<std::string>			indexes;
		std::vector<std::string>			uploads;
		std::vector<std::string>			methods;
		std::map<int, std::string>			returns;
		std::map<std::string, std::string>	cgi;
};

class Server
{
	public:
		std::string						root;
		std::string						host;
		unsigned int					port;
		unsigned long long				body_size;
		std::vector<std::string>		server_names;
		std::vector<std::string>		methods;
		std::vector<std::string>		indexes;
		std::map<int, std::string>		error_pages;
		std::map<std::string, Location>	locations;
};

class Configuration
{
	public:
		std::vector<Server>	servers;
		Configuration(std::string conf_file_name);
		void		parse_content(std::string content);
		void		parse_server_block(std::string block);
		void		parse_location_block(Server &serv, std::string location_match, std::string block);
		std::string	parse_server_line(Server &serv, std::string line);
		void		parse_location_line(Location &location, std::string line);
};

std::string get_valid_path(std::string path);
/*server params extractors*/
void    get_root(Server &serv, std::string argument);
void    get_port(Server &serv, std::string argument);
void    get_host(Server &serv, std::string argument);
void    get_body_size(Server &serv, std::string argument);
void    get_server_name(Server &serv, std::string argument);
void    get_methods(Server &serv, std::string argument);
void    get_index(Server &serv, std::string argument);
void    get_error_page(Server &serv, std::string argument);

/*location params extractors*/
void    get_location_autoindex(Location &location, std::string argument);
void    get_location_root(Location &location, std::string argument);
void    get_location_methods(Location &location, std::string argument);
void    get_location_index(Location &location, std::string argument);
void    get_location_upload(Location &location, std::string argument);
void    get_location_return(Location &location, std::string argument);
void    get_location_cgi(Location &location, std::string argument);
#endif