/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Methods.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:04:32 by mel-kora          #+#    #+#             */
/*   Updated: 2023/06/13 20:31:50 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Methods.hpp"

Method::Method(std::string target): target(target)
{}

Get::Get(std::string target): Method(target)
{}

Delete::Delete(std::string target): Method(target)
{}

Post::Post(std::string target): Method(target)
{}

void	Get::implement_method(request &req, Response &res, Server_info server, Location location){
	(void) res;
	(void) req;
	(void) server;
	(void) location;
}

void	Post::implement_method(request &req, Response &res, Server_info server, Location location){
	(void) res;
	(void) req;
	(void) server;
	(void) location;
}

void	Delete::implement_method(request &req, Response &res, Server_info server, Location location){
	(void) res;
	(void) req;
	(void) server;
	(void) location;    
}
