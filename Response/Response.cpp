/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:13:15 by mel-kora          #+#    #+#             */
/*   Updated: 2023/06/07 13:24:13 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Response::Response()
{
}

void	Response::response_fetch(request &req, Configuration conf)
{
	status_code = req.status_code;
	get_location(req);
	if (req.status_code == -1 && req.method == "" && req.path == "" && req.version == "" && req.header.size() == 0)
		return ;
	if (status_code == -1)
	{
		if (req.header.find("host") == req.header.end())
			status_code = 400;
		else if (req.header.find("Transfer-Encoding") != req.header.end() && req.header["Transfer-Encoding"] != "chunked")
			status_code = 501;
		else if (req.path.size() > 2048)
			status_code = 414;
		else if (req.header.find("Content-Length") == req.header.end())
			status_code = 411;
	}
	if (status_code != -1)
		get_error_response();
	else
	{
		get_response(req);
		if (status_code / 100 != 2 || status_code / 100 != 3)
		{
			//send error
		}
		else 
		{
			//send chunk of response	
		}
	}
}

std::string	Response::get_http_message(void){
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
		default:
			return ("Unsupported HTTP response status codes ⛔️");
	}
}

std::string	Response::get_error_response(void){
	return (get_status_line() + CRLF + "<!DOCTYPE html>\
	<style>@import url('https://fonts.googleapis.com/css?family=Press Start 2P');	html, body {	width: 100%;	height: 100%;	margin: 0;	} 	* {	font-family: 'Press Start 2P', cursive;	box-sizing: border-box;	}	#app {	padding: 1rem;	background: black;	display: flex;	height: 100%;	justify-content: center;	align-items: center;	color: #5bd6ff;	text-shadow: 0px 0px 10px;	font-size: 6rem;	flex-direction: column;	}	#app .txt {	font-size: 1.8rem;	}	@keyframes blink {	0% {opacity: 0;}	49% {opacity: 0;}	50% {opacity: 1;}	100% {opacity: 1;}	}	.blink {	animation-name: blink;	animation-duration: 1s;	animation-iteration-count: infinite;	}</style>\
	<html>\
		<head>\
			<meta http-equiv=content-type content=text/html; charset=UTF-8>\
			<title>" + std::to_string(status_code) + "</title>\
			<link href=error.css rel=stylesheet type=text/css>\
		</head>\
		<body>\
			<div id=app>\
				<div>" + std::to_string(status_code) + "</div>\
				<div class=txt>" + get_http_message() + "<span class=blink>_</span></div>\
			</div>\
		</body>\
	</html>");
}

void	Response::get_response(request &req){
	if (req.method == "GET")
	{
		Get res;
		res.implement_method(*this);
	}
	else if (req.method == "POST")
	{
		Post res;
		res.implement_method(*this);
	}
	else if (req.method == "DELETE")
	{
		Delete res;
		res.implement_method(*this);
	}
}

std::string	Response::get_status_line(void){
	return ("HTTP/1.1" + ' ' + std::to_string(status_code) + ' ' + get_http_message());
}

int	check_request_uri(std::string request_uri){
	std::string	allowed_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 ._~:/?#[]@!$&'()*+,;=%";
	unsigned long i = 0, j;
	while (i < request_uri.size())
	{
		j = 0;
		while (j < allowed_chars.size() && request_uri[i] != allowed_chars[j])
			j++;
		if (j != allowed_chars.size())
			return (0);
		i++;
	}
	return(1);
}