/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:18:19 by mel-kora          #+#    #+#             */
/*   Updated: 2023/07/07 19:09:09 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib.hpp"
#include "../Client/Client.hpp"

std::string	Client::get_QueryString()
{
	ssize_t		interogation_pos = req.path.find('?');
	if (interogation_pos + 1 >= (ssize_t)req.path.size())
		return ("");
	std::string	QueryString = req.path.substr(interogation_pos + 1, req.path.size());
	//may need decoding but let see that later
	return (QueryString);
}

void	Client::get_cgi_env(std::vector<std::string> cgi_env_var, char *cgi_env[14])
{
	std::string QueryString = get_QueryString();
	cgi_env_var.push_back("SCRIPT_FILENAME=" + res.exec_path);
	cgi_env_var.push_back("PATH_INFO=" + res.file_path);
	cgi_env_var.push_back("SERVER_PROTOCOL=" + req.version);
	cgi_env_var.push_back("SERVER_PORT=" + std::to_string(res.port));
	cgi_env_var.push_back("REQUEST_METHOD=" + req.method);
	cgi_env_var.push_back("CONTENT_TYPE=" + req.header["Content-Type"]);
	cgi_env_var.push_back("CONTENT_LENGTH=" + req.header["Content-Length"]);
	cgi_env_var.push_back("HTTP_COOKIE=" + req.header["Cookie"]);
	cgi_env_var.push_back("QUERY_STRING=" + QueryString);
	cgi_env_var.push_back("GATEWAY_INTERFACE=CGI/1.1");
	cgi_env_var.push_back("REDIRECT_STATUS=200");
	if (is_ip_address(res.host))
		cgi_env_var.push_back("REMOTE_ADDR=" + res.host);
	else
	{
		cgi_env_var.push_back("REMOTE_HOST=" + res.host);
		cgi_env_var.push_back("SERVER_NAME=" + res.host);
	}
	std::vector<std::string>::iterator i = cgi_env_var.begin();
	int j = 0;
	while (i != cgi_env_var.end())
		cgi_env[j++] = (char *)(*(i++)).c_str();
	cgi_env[j] = NULL;
}

void	Client::execute_cgi(Configuration conf)
{
	char						*args[3] = {(char*)res.exec_path.c_str(), (char*)res.file_path.c_str(), NULL};
	char 						*cgi_env[14];
	std::vector<std::string>	cgi_env_var;
	
	get_cgi_env(cgi_env_var, cgi_env);
	(void) args;
	(void) cgi_env;
	// to_be_continued
    if (res.is_finished == 1)
		fail_in_execution(conf);
    else
	    res.is_finished = 2;
}