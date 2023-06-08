/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:12:52 by mel-kora          #+#    #+#             */
/*   Updated: 2023/06/08 11:49:37 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		Response_HPP
# define	Response_HPP
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
		Location	*location;
		Server_info	*server;
		Response();
		void		response_fetch(request &req, Configuration conf);
		void		get_server(Configuration conf);
		void		get_location(request req, Configuration conf);
		void		get_response(request &req);
		void		get_host_nd_port(std::string value);
		std::string	get_body(void);
		std::string	get_http_message(void);
		std::string	get_error_response(request req);
		std::string	get_status_line(request req);
};

int	check_request_uri(std::string request_uri);
#endif
