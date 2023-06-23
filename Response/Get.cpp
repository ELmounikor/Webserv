/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Get.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:43:22 by mel-kora          #+#    #+#             */
/*   Updated: 2023/06/23 17:25:39 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Get::Get(std::string target): Method(target)
{}

void	Get::implement_method(Response &res, request &req, Server_info server, Location location)
{
	// std::cout << "TARGET = '" + target + "'\n";
	if (target_not_good(res, server, location))
		return ;
	if (check % 2 == 0)
	{
		if (req.path.size() > 0 && req.path[req.path.size() - 1] != '/')
			res.get_redirection_response(req.path + "/", 301);
		std::vector<std::string>::iterator i = location.indexes.begin();
		while (i != location.indexes.end())
		{
			std::string new_target = join_paths(target, *i);
			int current = check_path(new_target);
			if (current)
			{
				// std::cout << "new_target = '" + new_target + "'\n";
				if (current == 1)
				{
					res.status_code = 200;
					res.get_file_response(server, location, new_target);
				}
				else
					res.get_redirection_response(join_paths(res.location_name, *i), 301);
				return ;
			}
			i++;
		}
		if (location.autoindex == 1 && check > 0)
		{
			res.status_code = 200;
			res.get_auto_index_page_response(target);
		}
		else
		{
			res.status_code = 403;
			res.get_error_response(server, location);	
		}
	}
	else
	{
		res.status_code = 200;
		res.get_file_response(server, location, target);
	}
}
