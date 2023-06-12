/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Methods.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:04:19 by mel-kora          #+#    #+#             */
/*   Updated: 2023/06/12 23:00:44 by mel-kora         ###   ########.fr       */
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
		virtual void implement_method(request &req, Response &res, Server_info server, Location location) = 0;
};

class Get: public Method
{
	public:
		void implement_method(request &req, Response &res, Server_info server, Location location);
};

class Post: public Method
{
	public:
		void implement_method(request &req, Response &res, Server_info server, Location location);
};

class Delete: public Method
{
	public:
		void implement_method(request &req, Response &res, Server_info server, Location location);
};

#endif