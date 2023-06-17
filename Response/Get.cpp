/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Get.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:43:22 by mel-kora          #+#    #+#             */
/*   Updated: 2023/06/17 16:06:52 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Methods.hpp"

Get::Get(std::string target): Method(target)
{}

void	Get::implement_method(Response &res, request &req, Server_info server, Location location)
{
	if (target_not_good(res, req, server))
		return ;
	if (check % 2 == 0)
	{
		if (req.path[req.path.size() - 1] != '/')
			res.get_redirection_response(req, location, res.to_fetch + "/", 301);
		else if ((location.autoindex == 1 && check < 0) || (location.autoindex == 0 && location.indexes.size() == 0) )
		{
			res.status_code = 403;
			res.get_error_response(req, server);
		}
		else if (location.autoindex == 0)
		{
			std::vector<std::string>::iterator i = location.indexes.begin();
			while (i != location.indexes.end())
			{
				int current = check_path(target + *i);
				if (current)
				{
					if (current == 1)
						res.get_file_response(req, server, location, target + *i);
					else if (current)
						res.get_redirection_response(req, location, target + *i, 301);
					return ;
				}
				i++;
			}
			res.status_code = 404;
			res.get_error_response(req, server);
		}
		else
			res.get_auto_index_page_response(req, target);
	}
	else
		res.get_file_response(req, server, location, target);
}
