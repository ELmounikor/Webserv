/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Post.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounikor <mounikor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:44:03 by mel-kora          #+#    #+#             */
/*   Updated: 2023/06/27 23:03:04 by mounikor         ###   ########.fr       */
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
		while (!in_file.eof())
		{
			char buf[1024];
			memset(buf, 0, 1024);
			in_file.read(buf, 1024);
			out_file << buf;
		}
		res.status_code = 201;
	}
	(void) res;
	(void) req;
	(void) server;
}
