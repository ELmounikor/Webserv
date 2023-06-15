/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Get.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:43:22 by mel-kora          #+#    #+#             */
/*   Updated: 2023/06/15 14:13:49 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Methods.hpp"

Get::Get(std::string target): Method(target)
{}

void	Get::implement_method(Response &res, request &req, Server_info server, Location location)
{
	if (target_not_good(res, req, server))
		return ;
    (void) location;
}
