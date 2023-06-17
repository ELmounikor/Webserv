/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Post.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:44:03 by mel-kora          #+#    #+#             */
/*   Updated: 2023/06/17 17:42:02 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Post::Post(std::string target): Method(target)
{}

void	Post::implement_method(Response &res, request &req, Server_info server, Location location)
{
	(void) res;
	(void) req;
	(void) server;
	(void) location;
}
