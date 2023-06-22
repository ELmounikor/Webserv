/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:12:52 by mel-kora          #+#    #+#             */
/*   Updated: 2023/06/22 18:30:33 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		RESPONSE_HPP
# define	RESPONSE_HPP
# define	CRLF	"\r\n" 
# define	SP		" " 
# include	"Methods.hpp"

class	Response
{
	public:
		int									is_finished;
		int									status_code;
		int									is_cgi;
		int									port;
		std::string							host;
		std::string							body;
		std::string							to_fetch;
		std::string							file_path;
		std::string							exec_path;
		std::string							location_name;
		std::fstream						body_file;
		std::map<std::string, std::string>	headers;
		Response();
		int			has_cgi(std::string path, Location location, Server_info server);
		void		reset_response(void);
		void		get_host_nd_port(std::string value);
		void		get_error_response(Server_info server);
		void		response_fetch(request &req, Configuration conf);
		void		get_auto_index_page_response(std::string dir_path);
		void		print_response_attr(Server_info server, Location location);
		void		get_response(request &req, Server_info server, Location location);
		void		get_redirection_response(std::string next_location, int redirect_code);
		void		get_file_response(Server_info server, Location location, std::string path);
		std::string	get_status_message(void);
		std::string	get_header(request &req);
		Server_info	get_server(request &req, Configuration conf);
		Location	get_location(request &req, Server_info server);
};

#endif
