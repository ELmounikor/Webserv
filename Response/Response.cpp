/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:13:15 by mel-kora          #+#    #+#             */
/*   Updated: 2023/06/13 17:16:43 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Response::Response(): status_code(-1), port(-1), host(""), body(""), to_fetch(""), location_name(""), response_content("")
{
}

int	check_request_uri(std::string request_uri)
{
	std::string	allowed_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 ._~:/?#[]@!$&'()*+,;=%";
	size_t i = 0, j;
	
	while (i < request_uri.size())
	{
		j = allowed_chars.find(request_uri[i]);
		if (j == allowed_chars.size())
			return (0);
		i++;
	}
	return(1);
}

void	Response::response_fetch(request &req, Configuration conf)
{
	if (req.status_code == -1 && req.method == "" && req.path == "" && req.version == "" && req.header.size() == 0)
		return ;
	status_code = req.status_code;
	Server_info server = get_server(req, conf);
	Location location = get_location(req, server);
	if (status_code == -1)
	{
		if (req.header.find("Host") == req.header.end() || !check_request_uri(req.path))
			status_code = 400;
		else if (req.header.find("Transfer-Encoding") != req.header.end() && req.header["Transfer-Encoding"] != "chunked")
			status_code = 501;
		else if (req.header.find("Content-Length") != req.header.end() && strtol(req.header["Content-Length"].c_str(), NULL, 10) > server.body_size)
			status_code = 413;
		else if (req.path.size() > 2048)
			status_code = 414;
		else if (location.autoindex == -1)
			status_code = 404;
		else if (location.returns.size() > 0)
		{
			get_redirection_response(req, server, location);
			return ;
		}
		else if (std::find(location.methods.begin(), location.methods.end(), req.method) == location.methods.end())
			status_code = 405;
	}
	else if (req.method == "POST" && req.header.find("Transfer-Encoding") != req.header.end() && req.header.find("Content-Length") == req.header.end())
		status_code = 411;
	print_response_attr(server, location);
	exit(2);
	if (status_code / 100 != 2 && status_code / 100 != 3)
		get_error_response(req, server);
	else
		get_response(req, server, location);
}

void	Response::get_response(request &req, Server_info server, Location location)
{
	if (req.method == "GET")
	{
		Get res;
		res.implement_method(req, *this, server, location);
	}
	else if (req.method == "DELETE")
	{
		Delete res;
		res.implement_method(req, *this, server, location);
	}
	else if (req.method == "POST")
	{
		Post res;
		res.implement_method(req, *this, server, location);
	}
}

void	Response::get_error_response(request &req, Server_info server)
{
	std::map<int, std::string>::iterator errp = server.error_pages.find(status_code);
	if (server.port != -1 && errp != server.error_pages.end())
	{
		std::ifstream error_page((*errp).second);
		if (error_page.is_open())
		{
			std::getline(error_page, body, '\0');
			response_content = get_status_line(req) + CRLF + body;
			return ;
		}
		// else if (status_code != 403)
		// {
		// 	status_code = 403;
		// 	get_error_response(req, server);
		// 	return ;
		// }
	}
	body = "<!DOCTYPE html>\
	<style>@import url('https://fonts.googleapis.com/css?family=Press Start 2P');	html, body {	width: 100%;	height: 100%;	margin: 0;	} 	* {	font-family: 'Press Start 2P', cursive;	box-sizing: border-box;	}	#app {	padding: 1rem;	background: black;	display: flex;	height: 100%;	justify-content: center;	align-items: center;	color: #5bd6ff;	text-shadow: 0px 0px 10px;	font-size: 6rem;	flex-direction: column;	}	#app .txt {	font-size: 1.8rem;	}	@keyframes blink {	0% {opacity: 0;}	49% {opacity: 0;}	50% {opacity: 1;}	100% {opacity: 1;}	}	.blink {	animation-name: blink;	animation-duration: 1s;	animation-iteration-count: infinite;	}</style>\
	<html>\
		<head>\
			<meta http-equiv=content-type content=text/html; charset=UTF-8>\
			<title>" + std::to_string(status_code) + "</title>\
		</head>\
		<body>\
			<div id=app>\
				<div>" + std::to_string(status_code) + "</div>\
				<div class=txt>" + get_status_message() + "<span class=blink>_</span></div>\
			</div>\
		</body>\
	</html>";
	response_content = get_status_line(req) + CRLF + body;
}

void	Response::get_redirection_response(request &req, Server_info server, Location location)
{
	status_code = (*location.returns.begin()).first;
	std::string file = (*location.returns.begin()).second;
	std::ifstream redirect_page(location.root + file);
	if (location_name[location_name.size() - 1] != '/' && file[0] != '/')
		file = "/" + file;
	if (redirect_page.is_open())
	{
		std::getline(redirect_page, body, '\0');
		std::string location_header = "Location: " + location_name + file;
		response_content = get_status_line(req) + "\n" + location_header + CRLF + body;
	}
	else
	{
		status_code = 403;
		get_error_response(req, server);
	}
}
