/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Post.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounikor <mounikor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:44:03 by mel-kora          #+#    #+#             */
/*   Updated: 2023/06/28 11:29:40 by mounikor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Post::Post(std::string target): Method(target)
{}

void	Post::implement_method(Response &res, request &req, Server_info server, Location location)
{
	if  (location.uploads.size())
	{
		std::string		file_location = join_paths(location.root, *(location.uploads.begin()));
		std::ifstream	in_file(req.name_file);
		if (check_path(file_location) != 2)
		{
			res.status_code = 500;
			res.get_error_response(server, location);
			return ;
		}
		std::ofstream	out_file(get_file_name(file_location));
		if (in_file.eof())
		{
			res.status_code = 204;
			return ;
		}
		while (!in_file.eof())
		{
			char buf[1024];
			memset(buf, 0, 1024);
			in_file.read(buf, 1024);
			out_file << buf;
		}
		res.status_code = 201;
	}
	if (target_not_good(res, server, location))
		return ;
	if (check % 2 == 0)
	{
		std::vector<std::string>::iterator i = location.indexes.begin();
		while (i != location.indexes.end())
		{
			std::string new_target = join_paths(target, *i);
			int current = check_path(new_target);
			if (current == 1 && res.has_cgi(new_target, location, server))
				return ;
			i++;
		}
		res.status_code = 403;
		res.get_error_response(server, location);
	}
	else
	{
		if (check == 1 && res.has_cgi(target, location, server))
			return ;
		res.status_code = 403;
		res.get_error_response(server, location);
	}
}
