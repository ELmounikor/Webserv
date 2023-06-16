/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:12:52 by mel-kora          #+#    #+#             */
/*   Updated: 2023/06/16 19:33:14 by mel-kora         ###   ########.fr       */
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
		int			status_code;
		int			port;
		std::string	host;
		std::string body;
		std::string	to_fetch;
		std::string	location_name;
		std::string	response_content;
		Response();
		void		response_fetch(request &req, Configuration conf);
		void		get_host_nd_port(std::string value);
		void		print_response_attr(Server_info server, Location location);
		void		get_error_response(request &req, Server_info server);
		void		get_response(request &req, Server_info server, Location location);
		void		get_redirection_response(request &req, Location location, std::string file, int redirect_code);
		void		get_file_response(request &req, Server_info server, std::string path);
		Location	get_location(request &req, Server_info server);
		Server_info	get_server(request &req, Configuration conf);
		std::string	get_status_line(request &req);
		std::string	get_status_message(void);
};

#endif
