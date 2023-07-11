/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Header.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 22:14:54 by mel-kora          #+#    #+#             */
/*   Updated: 2023/07/11 09:43:25 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

std::string	Response::get_header(request &req)
{
	std::string	status_line = req.version + SP + std::to_string(status_code) + SP + get_status_message() + CRLF;
	if (req.header.find("Cookies") != req.header.end())
		headers["Set-cookie"] = req.header["Cookies"];
	headers["Date"] = get_date();
	std::map<std::string, std::string>::iterator i = headers.begin();
	while (i != headers.end())
	{
		status_line = status_line + (*i).first + ": " + (*i).second + CRLF;
		i++;
	}
	return (status_line + CRLF);
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
