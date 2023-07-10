/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Post.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:44:03 by mel-kora          #+#    #+#             */
/*   Updated: 2023/07/10 15:03:15 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Post::Post(std::string target): Method(target)
{}

void	Post::implement_method(Response &res, request &req, Server_info server, Location location)
{
	if (target_not_good(res, server, location))
		return ;
	if  (location.uploads.size())
	{
		if (check_path(*(location.uploads.begin())) != 2)
		{
			res.status_code = 403;
			res.get_error_response(server, location);
			return ;
		}
		std::string		out_file_path = join_paths(*(location.uploads.begin()), req.name_file);
		std::ifstream	in_file(req.name_file);
		std::fstream	out_file(out_file_path, std::fstream::out | std::fstream::app);
		if (!out_file.is_open() || !in_file.is_open())
		{
			if (in_file.is_open())	in_file.close();
			if (out_file.is_open())	out_file.close();
			res.status_code = 500;
			res.get_error_response(server, location);
			return ;
		}
		if (in_file.eof())
		{
			in_file.close();
			out_file.close();
			res.status_code = 204;
			return ;
		}
		in_file.close();
		out_file.close();
		res.file_path = out_file_path;
		res.exec_path = req.name_file;
		res.status_code = 201;
		return ;
	}
	if (check % 2 == 2)
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
	}
	else if (check == 1 && res.has_cgi(target, location, server))
			return ;
	res.status_code = 403;
	res.get_error_response(server, location);
}
