/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:33:41 by mel-kora          #+#    #+#             */
/*   Updated: 2023/06/17 19:15:03 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

void	Response::execute_cgi(request &req, std::string exec_path, std::string file_path)
{
	is_finished = 1;
	(void) req;
	(void) file_path;
	(void) exec_path;
}