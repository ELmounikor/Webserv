/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Delete.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:44:14 by mel-kora          #+#    #+#             */
/*   Updated: 2023/06/20 22:32:06 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Delete::Delete(std::string target): Method(target)
{}

void	Delete::implement_method(Response &res, request &req, Server_info server, Location location)
{
	(void ) location;
	if (target_not_good(res, server))
		return ;
	if (check % 2 == 0)
	{
		if (req.path[req.path.size() - 1] != '/')
		{
			res.status_code = 409;
			res.get_error_response(server);
		}
		//directory with auto_index
	}
	else
	{
		//file
	}
}
