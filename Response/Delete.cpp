/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Delete.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:44:14 by mel-kora          #+#    #+#             */
/*   Updated: 2023/06/17 17:42:13 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Delete::Delete(std::string target): Method(target)
{}

void	Delete::implement_method(Response &res, request &req, Server_info server, Location location)
{
	if (target_not_good(res, req, server))
		return ;
	(void) location;
}
