/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Header.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 22:14:54 by mel-kora          #+#    #+#             */
/*   Updated: 2023/06/18 20:34:43 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

std::string	Response::get_status_line(request &req)
{
	std::string	status_line = req.version + SP + std::to_string(status_code) + SP + get_status_message() + CRLF;
	// header["Date"] = get_date();
	if (body.size() > 0)
		header["Content-Length"] = std::to_string(body.size());
	// std::map<std::string, std::string>::iterator i = header.begin();
	// while (i != header.end())
	// {
	// 	status_line = (*i).first + ": " + (*i).second + CRLF;
	// 	i++;
	// }
	return (status_line + "\n" + CRLF);
}

std::string	Response::get_status_message(void)
{
	switch (status_code)
	{
		case 200:
			return ("OK");
		case 201:
			return ("Created");
		case 204:
			return ("No Content");
		case 301:
			return ("Moved Permanently");
		case 302:
			return ("Found");
		case 307:
			return ("Temporary Redirect");
		case 308:
			return ("Permanent Redirect");
		case 400:
			return ("Bad Request");
		case 401:
			return ("Unauthorized");
		case 403:
			return ("Forbidden");
		case 404:
			return ("Not Found");
		case 405:
			return ("Method Not Allowed");
		case 409:
			return ("Conflict");
		case 410:
			return ("Gone");
		case 411:
			return ("Length Required");
		case 413:
			return ("Payload Too Large");
		case 414:
			return ("URI Too Long");
		case 500:
			return ("Internal Server Error");
		case 501:
			return ("Not Implemented");
		case 502:
			return ("Bad Gateway");
		default:
			return ("Unsupported HTTP response status code ⛔️");
	}
}
