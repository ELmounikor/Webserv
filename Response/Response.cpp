/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:13:15 by mel-kora          #+#    #+#             */
/*   Updated: 2023/07/01 15:26:33 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Response::Response(): is_finished(-1), status_code(-1), is_cgi(-1), port(-1), host(""), body(""), to_fetch(""), file_path(""), exec_path(""), location_name("")
{}

void	Response::reset_response()
{
	is_finished = -1;
	status_code = -1;
	is_cgi = -1;
	port = -1;
	host = "";
	body = "";
	to_fetch = "";
	file_path = "";
	exec_path = "";
	location_name = "";
	body_file.close();
	body_file.clear();
	headers.clear();
}

int	check_request_uri(std::string request_uri)
{
	std::string	allowed_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~:/?#[]@!$&'()*+,;=%";
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
	is_finished = 0;
	is_cgi = 0;
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
			get_redirection_response(join_paths(location_name, (*location.returns.begin()).second), (*location.returns.begin()).first);
		else if (std::find(location.methods.begin(), location.methods.end(), req.method) == location.methods.end())
			status_code = 405;
	}
	if (status_code != -1)
		get_error_response(server, location);
	else
		get_response(req, server, location);
	// print_response_attr(server, location);
}

void	Response::get_response(request &req, Server_info server, Location location)
{
	file_path = join_paths(location.root, to_fetch);
	if (req.method == "GET")
	{
		Get res(file_path);
		res.implement_method(*this, req, server, location);
	}
	else if (req.method == "DELETE")
	{
		Delete res(file_path);
		res.implement_method(*this, req, server, location);
	}
	else if (req.method == "POST")
	{
		Post res(file_path);
		res.implement_method(*this, req, server, location);
	}
}

void	Response::get_error_response(Server_info server, Location location)
{
	std::map<int, std::string>::iterator errp = server.error_pages.find(status_code);
	if (server.port != -1 && errp != server.error_pages.end())
	{
		std::ifstream error_page((*errp).second);
		if (error_page.is_open())
		{
			file_path = (*errp).second;
			get_file_response(server, location, (*errp).second);
			return ;
		}
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
	headers["Content-Type"] = "text/html";
	headers["Content-Length"] = std::to_string(body.size());
	file_path = "Default";
}

void	Response::get_redirection_response(std::string next_location, int redirect_code)
{
	status_code = redirect_code;
	headers["Location"] = next_location;
	file_path = "redirect to " + next_location;
}

void Response::get_auto_index_page_response(std::string dir_path)
{
	DIR* dir = opendir(dir_path.c_str());
	struct dirent* element;
	status_code = 200;
	body = "<!DOCTYPE html>\
	<style>@import url('https://fonts.googleapis.com/css?family=Press Start 2P');	html, body {	width: 100%;	height: 100%;	margin: 0;	} 	* {	font-family: 'Press Start 2P', cursive;	box-sizing: border-box;	}	#app {	padding: 1rem;	background: black;	display: flex;	height: 100%;	justify-content: center;	align-items: center;	color: #5bd6ff;	text-shadow: 0px 0px 10px;	font-size: 6rem;	flex-direction: column;	}	#app .txt {	font-size: 1.8rem;	}	@keyframes blink {	0% {opacity: 0;}	49% {opacity: 0;}	50% {opacity: 1;}	100% {opacity: 1;}	}	.blink {	animation-name: blink;	animation-duration: 1s;	animation-iteration-count: infinite;	}</style>\
	<html>\
		<head>\
			<meta http-equiv=content-type content=text/html; charset=UTF-8>\
			<title>" + location_name + to_fetch + "'s autoindex page" + "</title>\
		</head>\
		<body>\
		<h1>Index of "+ dir_path + "</h1><hr><div>";
	while ((element = readdir(dir)) != NULL)
	{
		body = body + "<a href=" + element->d_name + ((check_path(dir_path + element->d_name) % 2) ? "" : "/") +">" + \
		element->d_name + ((check_path(dir_path + element->d_name) % 2) ? "" : "/")  + "</a><br>";
	}	
	body = body + "</div><hr></body></html>";
	closedir(dir);
	headers["Content-Type"] = "text/html";
	headers["Content-Length"] = std::to_string(body.size());
	file_path = "Default";
}

void Response::get_file_response(Server_info server, Location location, std::string path)
{
	body_file.open(path);
	if (body_file.is_open())
	{
		file_path = path;
		if (location.autoindex != -1 && has_cgi(path, location, server))
			return ;
		headers["Content_Type"] = get_extension_type(get_extension(path));
		headers["Content-Length"] = get_file_size(path);
	}
	else
	{
		status_code = 403;
		get_error_response(server, location);
	}
}

int Response::has_cgi(std::string path, Location location, Server_info server)
{
	std::string extension = get_extension(path);
	std::map<std::string, std::string>::iterator i = location.cgi.begin();
	while (i != location.cgi.end())
	{
		if ((*i).first == extension)
		{
			file_path = path;
			exec_path = (*i).second;
			if (access(exec_path.c_str(), F_OK))
			{
				status_code = 404;
				get_error_response(server, location);
			}
			else if (access(exec_path.c_str(), X_OK))
			{
				status_code = 403;
				get_error_response(server, location);
			}
			else
			{
				status_code = 200;
				is_cgi = 1;
			}
			return (1);
		}
		i++;
	}
	return (0);
}
