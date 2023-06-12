/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:12:52 by mel-kora          #+#    #+#             */
/*   Updated: 2023/06/12 15:27:04 by mel-kora         ###   ########.fr       */
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
		std::string	link;
		std::string body;
		std::string	to_fetch;
		std::string	location_name;
		std::string	response_content;
		Location	*location;
		Server_info	*server;
		Response();
		void		response_fetch(request &req, Configuration conf);
		void		get_location(request &req, Configuration conf);
		void		get_host_nd_port(std::string value);
		void		get_server(Configuration conf);
		void		get_response(request &req);
		void		print_response_attr(void);
		void		get_redirection_response(request &req);
		void		get_error_response(request &req);
		std::string	get_status_line(request &req);
		std::string	get_status_message(void);
};

#endif
