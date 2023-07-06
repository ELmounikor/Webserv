/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:18:19 by mel-kora          #+#    #+#             */
/*   Updated: 2023/07/06 16:32:09 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib.hpp"
#include "../Client/Client.hpp"

void	Client::execute_cgi(Configuration conf)
{
	std::string file_path = res.file_path;
	std::string executable_path = res.exec_path;
	// to_be_continued
    if (res.is_finished == 1)
		fail_in_execution(conf);
    else
	    res.is_finished = 2;
}