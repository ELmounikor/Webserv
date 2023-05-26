/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:13:15 by mel-kora          #+#    #+#             */
/*   Updated: 2023/05/26 18:42:03 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

void print_request(request req)
{
	std::cout << "status_code : " << req.status_code << "\n";
	std::cout << "version : " << req.version << "\n";
	std::cout << "path : " << req.path << "\n";
	std::cout << "method : " << req.method << "\n";
	std::cout << "header : \n";
	print_map(req.header);
}

Response::Response()
{
}

void	Response::check_param(request req, Configuration conf)
{
	print_request(req);
	if (req.status_code == -1 && req.method == "" && req.path == "" && req.version == "" && req.header.size() == 0)
		return ;
	print_config(conf);
}

void	Response::get_response(void){
	
}