/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Methods.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:04:32 by mel-kora          #+#    #+#             */
/*   Updated: 2023/06/16 19:31:27 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Methods.hpp"

Method::Method(std::string target): check(0), target(target)
{}

bool Method::target_not_good(Response &res, request &req, Server_info server)
{
	check = check_path(target);
	if (!check)
	{
		res.status_code = 404;
		res.get_error_response(req, server);
		return (1);
	}
	return (0);
}

int	Method::execute_cgi(Response &res, request &req, Server_info server, Location location)
{
	(void) res;
	(void) req;
	(void) server;
	(void) location;
	return (0);
}
