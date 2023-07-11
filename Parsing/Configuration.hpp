/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Configuration.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:16:09 by mel-kora          #+#    #+#             */
/*   Updated: 2023/07/11 10:51:35 by mel-kora         ###   ########.fr       */
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
		Location();
		Location &operator=(const Location& rhs);
};

class Server_info
{
	public:
		int								port;
		long long						body_size;
		std::string						root;
		std::string						host;
		std::vector<std::string>		methods;
		std::vector<std::string>		indexes;
		std::vector<std::string>		server_names;
		std::map<int, std::string>		error_pages;
		std::map<std::string, Location>	locations;
		Server_info();
		Server_info &operator=(const Server_info& rhs);
		void		server_checker();
};

class Configuration
{
	public:
		std::vector<Server_info>	servers;
		std::set<int>				server_ports;
		Configuration();
		Configuration(std::string conf_file_name);
		void		print_config();
		void		parse_content(std::string content);
		void		parse_server_block(std::string block);
		void		parse_location_block(Server_info &serv, std::string location_match, std::string block);
		void		parse_location_line(Location &location, std::string line);
		std::string	parse_server_line(Server_info &serv, std::string line);
};

std::ostream	&operator<<( std::ostream &output, const Location &location);
std::string		get_valid_path(std::string path);
std::string		trim_spaces(std::string input);
int				is_ip_address(std::string host);
int				is_number(std::string input);
template <class T> void print_vector(T container)
{
	typename T::iterator i = container.begin();

	while (i != container.end())
	{
		std::cout << "\t-->" << *i << "\n";
		i++;
	}
	if (container.size() == 0)
		std::cout << "\t-->(NULL)\n";
}

template <class T> void print_map(T container)
{
	typename T::iterator i = container.begin();

	while (i != container.end())
	{
		std::cout << "\t-->" << (*i).first << " : " << (*i).second << "\n";
		i++;
	}
	if (container.size() == 0)
		std::cout << "\t-->(NULL)\n";
}

/*server params extractors*/
void	get_root(Server_info &serv, std::string argument);
void	get_port(Server_info &serv, std::string argument);
void	get_host(Server_info &serv, std::string argument);
void	get_body_size(Server_info &serv, std::string argument);
void	get_server_name(Server_info &serv, std::string argument);
void	get_methods(Server_info &serv, std::string argument);
void	get_index(Server_info &serv, std::string argument);
void	get_error_page(Server_info &serv, std::string argument);

/*location params extractors*/
void	get_location_autoindex(Location &location, std::string argument);
void	get_location_root(Location &location, std::string argument);
void	get_location_methods(Location &location, std::string argument);
void	get_location_index(Location &location, std::string argument);
void	get_location_upload(Location &location, std::string argument);
void	get_location_return(Location &location, std::string argument);
void	get_location_cgi(Location &location, std::string argument);
#endif