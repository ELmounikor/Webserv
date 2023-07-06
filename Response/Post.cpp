/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Post.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:44:03 by mel-kora          #+#    #+#             */
/*   Updated: 2023/07/06 00:04:32 by mel-kora         ###   ########.fr       */
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
		std::string		out_file_path = join_paths(file_location, res.to_fetch + req.get_extension(req.header["Content-Type"]));
		// int	i = chmod(req.name_file.c_str(), S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		// std::cout  << req.name_file << "\n"; 
		// if (i < 0)
		// 	perror("read request body file error");
		std::ifstream	in_file(req.name_file);
		if (in_file.eof())
		{
			res.status_code = 204;
			return ;
		}
		if (check_path(out_file_path) || res.to_fetch == "")
		{
			res.status_code = 409;
			res.get_error_response(server, location);
			return ;
		}
		std::ofstream	out_file(out_file_path);
		if (!out_file.is_open() || !in_file.is_open())
		{
			res.status_code = 500;
			res.get_error_response(server, location);
			return ;
		}
		while (!in_file.eof())
		{
			char buf[65536] = {0};
			in_file.read(buf, 65536);
			std::string data(buf, in_file.gcount());
			out_file << data;
		}
		res.status_code = 201;
		return ;
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
	}
	else if (check == 1 && res.has_cgi(target, location, server))
			return ;
	res.status_code = 403;
	res.get_error_response(server, location);
}
