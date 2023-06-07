/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Methods.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:04:19 by mel-kora          #+#    #+#             */
/*   Updated: 2023/06/07 13:31:37 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		METHODS_HPP
# define	METHODS_HPP
# include	"../lib.hpp"
class	request;
class	Configuration;
class	Server_info;
class	Location;
class	Response;

class Method
{
	public:
		virtual ~Method() = 0;
		virtual void implement_method(Response &res) = 0;
};

class Get: public Method
{
	public:
		void implement_method(Response &res);
};

class Post: public Method
{
	public:
		void implement_method(Response &res);
};

class Delete: public Method
{
	public:
		void implement_method(Response &res);
};

#endif