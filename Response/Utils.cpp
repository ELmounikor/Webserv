/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:12:02 by mel-kora          #+#    #+#             */
/*   Updated: 2023/06/17 15:42:20 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

int check_path(std::string path)
{
	struct stat	buf;
	if (stat(path.c_str(), &buf) != 0)
		return (0);
	if (S_ISDIR(buf.st_mode))
	{
		DIR* dir = opendir(path.c_str());
		if (!dir)
			return (-2);
		closedir(dir);
		return (2);
	}
	std::ifstream file(path);
	if (file.is_open())
		return (1);
	return (-1);
}

std::string	get_extention(std::string file_name)
{
	size_t dot_pos = file_name.find('.');
	return (file_name.substr(++dot_pos, file_name.size()));
}
