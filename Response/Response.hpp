/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:12:52 by mel-kora          #+#    #+#             */
/*   Updated: 2023/06/18 19:28:09 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		RESPONSE_HPP
# define	RESPONSE_HPP
# define	CRLF	"\r\n" 
# define	SP		" " 
# include	"Methods.hpp"

class	request;
class	Configuration;
class	Server_info;
class	Location;
class	Response
{
	public:
		int									is_finished;
		int									status_code;
		int									port;
		std::string							host;
		std::string 						body;
		std::string							to_fetch;
		std::string							location_name;
		std::string							response_content;
		std::map<std::string, std::string>	header;
		Response();
		void		get_host_nd_port(std::string value);
		void		response_fetch(request &req, Configuration conf);
		void		get_error_response(request &req, Server_info server);
		void		print_response_attr(Server_info server, Location location);
		void		get_auto_index_page_response(request &req, std::string dir_path);
		void		get_response(request &req, Server_info server, Location location);
		void		execute_cgi(request &req, std::string exec_path, std::string file_path);
		void		get_redirection_response(request &req, std::string next_location, int redirect_code);
		void		get_file_response(request &req, Server_info server, Location location, std::string path);
		std::string	get_status_message(void);
		std::string	get_status_line(request &req);
		Server_info	get_server(request &req, Configuration conf);
		Location	get_location(request &req, Server_info server);
};

#endif
