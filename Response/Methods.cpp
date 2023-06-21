/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Methods.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounikor <mounikor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:04:32 by mel-kora          #+#    #+#             */
/*   Updated: 2023/06/21 17:50:20 by mounikor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Methods.hpp"

Method::Method(std::string target): check(0), target(target)
{}

bool Method::target_not_good(Response &res, Server_info server)
{
	check = check_path(target);
	if (!check)
	{
		res.status_code = 404;
		res.get_error_response(server);
		return (1);
	}
	return (0);
}
