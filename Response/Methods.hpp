/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Methods.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:04:19 by mel-kora          #+#    #+#             */
/*   Updated: 2023/06/08 12:12:37 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		METHODS_HPP
# define	METHODS_HPP
# include	"../lib.hpp"
class	Response;

class Method
{
	public:
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