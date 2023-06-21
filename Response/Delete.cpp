/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Delete.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounikor <mounikor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:44:14 by mel-kora          #+#    #+#             */
/*   Updated: 2023/06/21 18:23:29 by mounikor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Delete::Delete(std::string target): Method(target)
{}

void	Delete::implement_method(Response &res, request &req, Server_info server, Location location)
{
	if (target_not_good(res, server))
		return ;
	if (check % 2 == 0)
	{
		if (req.path[req.path.size() - 1] != '/')
		{
			res.status_code = 409;
			res.get_error_response(server);
		}
		std::vector<std::string>::iterator i = location.indexes.begin();
		while (i != location.indexes.end())
		{
			int current = check_path(target + *i);
			if (current == 1 && res.has_cgi(target + *i, location, server))
				return ;
			i++;
			if (i == location.indexes.end())
			{
				res.status_code = 403;
				res.get_error_response(server);
				return ;
			}
			delete_folder(res, target);
			if (res.status_code != -1)
				res.get_error_response(server);
		}
	}
	else if (!res.has_cgi(target, location, server))
	{
		delete_file(res);	
		if (res.status_code != -1)
			res.get_error_response(server);
	}
}

void	Delete::delete_file(Response &res, std::string path)
{
	if (res.status_code != -1)
		return ;
	if (std::remove(path))
	{
		if (check_path(path) < 0)
			res.status_code = 403;
		else
			res.status_code = 500;
	}
}

void	Delete::delete_folder(Response &res, std::string path)
{
	if (res.status_code != -1)
		return ;
    DIR* dir = opendir(dir_path.c_str());
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
	if (std::remove(path))
	{
		if (check_path(path) < 0)
			res.status_code = 403;
		else
			res.status_code = 500;
	}
}
