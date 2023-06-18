/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Methods.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:04:19 by mel-kora          #+#    #+#             */
/*   Updated: 2023/06/17 23:28:39 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		METHODS_HPP
# define	METHODS_HPP
# include	"../lib.hpp"

class	Configuration;
class	Server_info;
class	Location;
class	Response;
class	request;
class Method
{
	public:
		int			check;
		std::string	target;
		Method(std::string target);
		bool			target_not_good(Response &res, request &req, Server_info server);
		virtual void	implement_method (Response &res, request &req, Server_info server, Location location) = 0;
};

class Get: public Method
{
	public:
		Get(std::string target);
		void implement_method(Response &res, request &req, Server_info server, Location location);
};

class Post: public Method
{
	public:
		Post(std::string target);
		void implement_method (Response &res, request &req, Server_info server, Location location);
};

class Delete: public Method
{
	public:
		Delete(std::string target);
		void implement_method (Response &res, request &req, Server_info server, Location location);
};

int			check_path(std::string path);
std::string	get_date(void);
std::string	get_next_option(std::string path);
std::string	get_extention(std::string file_name);
#endif