/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Get.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:43:22 by mel-kora          #+#    #+#             */
/*   Updated: 2023/06/16 19:48:05 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Methods.hpp"

Get::Get(std::string target): Method(target)
{}

void	Get::implement_method(Response &res, request &req, Server_info server, Location location)
{
	if (target_not_good(res, req, server))
		return ;
	std::cout << "TARGET =" + target +" \n";
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
				if (current == 1)
					res.get_file_response(req, server, target + *i);
				else if (current)
					res.get_redirection_response(req, location, target + *i, 301);
				i++;
			}
		}
		else
		{
			std::vector<std::string> elements;
			res.status_code = 200;
			// get_auto_index_page(res, elements);
		}
	}
	else
		res.get_file_response(req, server, target);
}
