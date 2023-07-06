/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Delete.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:44:14 by mel-kora          #+#    #+#             */
/*   Updated: 2023/07/06 18:20:55 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Delete::Delete(std::string target): Method(target)
{}

void	Delete::implement_method(Response &res, request &req, Server_info server, Location location)
{
	if (target_not_good(res, server, location))
		return ;
	if (check % 2 == 0)
	{
		if (req.path.size() > 0 && req.path[req.path.size() - 1] != '/')
		{
			res.status_code = 409;
			res.get_error_response(server, location);
			return ;
		}
		std::vector<std::string>::iterator i = location.indexes.begin();
		while (i != location.indexes.end())
		{
			int current = check_path(join_paths(target, *i));
			if (current == 1 && res.has_cgi(join_paths(target, *i), location, server))
				return ;
			i++;
			if (i == location.indexes.end())
				res.status_code = 403;	
		}
		if (check < 0)
			res.status_code = 403;
		else if (res.status_code == -1)
			delete_folder(res, target);
	}
	else
	{
		if (check < 0)
			res.status_code = 403;
		else if (!res.has_cgi(target, location, server))
			delete_file(res, target);
	}
	if (res.status_code != -1)
		res.get_error_response(server, location);
	else
		res.status_code = 204;
}

void	Delete::delete_file(Response &res, std::string path)
{
	if (std::remove(path.c_str()))
		res.status_code = 500;
}

void	Delete::delete_folder(Response &res, std::string path)
{
	if (res.status_code != -1)
		return ;
    DIR* dir = opendir(path.c_str());
	if (dir)
	{
		struct dirent* element;
		while ((element = readdir(dir)) != NULL)
		{
			int current = check_path(path + element->d_name);
			if (current % 2)
				delete_file(res, path + element->d_name);
			else
				delete_folder(res, path + element->d_name);
		}
		closedir(dir);
	}
	if (std::remove(path.c_str()))
		res.status_code = 500;
	else
		res.status_code = -1;
}
