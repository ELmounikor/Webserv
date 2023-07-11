/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:18:19 by mel-kora          #+#    #+#             */
/*   Updated: 2023/07/11 10:37:38 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib.hpp"
#include "../Client/Client.hpp"

std::string	Client::get_QueryString()
{
	size_t	interogation_pos = req.path.find("?");
	if (interogation_pos + 1 < req.path.size())
	{
		std::string	QueryString = req.path.substr(interogation_pos + 1, req.path.size());
		return (QueryString);
	}
	return ("");
}

void	Client::get_cgi_env(std::vector<std::string> &env_var, char **cgi_env)
{
	env_var.push_back("SCRIPT_FILENAME=" + res.file_path);
	env_var.push_back("PATH_INFO=" + res.file_path);
	env_var.push_back("REQUEST_URI=" + req.path);
	env_var.push_back("REQUEST_METHOD=" + req.method);
	env_var.push_back("CONTENT_TYPE=" + req.header["Content-Type"]);
	env_var.push_back("CONTENT_LENGTH=" + req.header["Content-Length"]);
	env_var.push_back("HTTP_ACCEPT=" + req.header["Accept"]);
	env_var.push_back("HTTP_ACCEPT_ENCODING=" + req.header["Accept-Encoding"]);
	env_var.push_back("HTTP_ACCEPT_LANGUAGE=" + req.header["Accept-Language"]);
	env_var.push_back("HTTP_CONNECTION=" + req.header["Connection"]);
	env_var.push_back("HTTP_COOKIE=" + req.header["Cookie"]);
	env_var.push_back("HTTP_USER_AGENT=" + req.header["User-Agent"]);
	env_var.push_back("GATEWAY_INTERFACE=CGI/1.1");
	env_var.push_back("REDIRECT_STATUS=200");
	env_var.push_back("QUERY_STRING=" + get_QueryString());
	env_var.push_back("SERVER_PROTOCOL=" + req.version);
	env_var.push_back("SERVER_PORT=" + std::to_string(res.port));
	env_var.push_back("SERVER_NAME=" + res.host);
	std::string server_sofware =  strtok((char *)req.header["User-Agent"].c_str(), " ");
	env_var.push_back("SERVER_SOFTWARE=" + server_sofware);
	if (is_ip_address(res.host))
		env_var.push_back("REMOTE_ADDR=" + res.host);
	else
		env_var.push_back("REMOTE_HOST=" + res.host);
	
	std::vector<std::string>::iterator i = env_var.begin();
	int j = 0;
	while (i != env_var.end())
		cgi_env[j++] = (char *)(*(i++)).c_str();
	cgi_env[j] = NULL;
}

void	cgi_dup(int in, int out)
{
	if (in < 0)
	{
		perror("Client CGI infile open error");
		exit(1);
	}
	if (in && dup2(in, 0) < 0)
	{
		perror("Client CGI dup0 fail");
		close(out);
		if(in)
			close(in);
		exit(1);
	}
	if (dup2(out, 1) < 0)
	{
		perror("Client CGI dup1 fail");
		close(out);
		if(in)
			close(in);
		exit(1);
	}
	if (dup2(out, 2) < 0)
	{
		perror("Client CGI dup2 fail");
		close(out);
		if(in)
			close(in);
		exit(1);
	}
	close(out);
	if(in)
		close(in);
}

void	Client::execute(char **args, char **cgi_env)
{
	int in = 0;
	int out = open(out_file.c_str(), O_RDWR, 0777);
	int err = dup(2);
	if (out < 0)
	{
		perror("Client CGI outfile open error");
		exit(1);
	}
	if (check_path(req.name_file))
		in = open(req.name_file.c_str(), O_RDONLY, 0777);
	cgi_dup(in, out);
	if (execve(args[0], args, cgi_env) == -1)
	{
		dup2(err, 2);
		perror("Client CGI execution fail");
		exit(1);
	}
}

void	Client::parse_cgi_outfile(void)
{
	std::ifstream	cgi_outfile(out_file);
	std::string		content;
	
	if (std::getline(cgi_outfile, content) && content.size() > 0)
	{
		while(content.size() > 0)
		{
			if (content == "\r")
				break ;
			size_t sep_pos = content.find(":");
			if (sep_pos < content.size())
			{
				std::string field = content.substr(0, sep_pos);
				std::string	value = strtok((char *)content.substr(sep_pos + 1, content.size()).c_str(), " ");
				if (field == "Status")
					res.status_code = strtol(value.c_str(), NULL, 10);
				else
					res.headers[field] = value.substr(0, value.size() - 1);
			}
			else
			{
				res.headers.clear();
				return ;
			}
			std::getline(cgi_outfile, content);
		}
	}
	if (content == "\r")
	{
		std::getline(cgi_outfile, content, '\0');
		res.byte_sent = strtol(get_file_size(res.file_path).c_str(), NULL, 10) - content.size();
	}
}

void	Client::execute_cgi(Configuration conf)
{
	char						*args[3] = {(char*)res.exec_path.c_str(), (char*)res.file_path.c_str(), NULL};
	char 						*cgi_env[30];
	std::vector<std::string>	env_var;
	if (pid == -1)
	{
		get_cgi_env(env_var, cgi_env);
		// std::cout << "CGI Environment Variables\n";
		// int j = 0;
		// while (cgi_env[j])
		// 	std::cout << "\t->" <<cgi_env[j++] << "\n";
		pid = fork();
		if (pid < 0)
		{
			perror("Client CGI fork error");
			fail_in_execution(conf);
			return ;
		}
		out_file = get_file_name("");
		if (pid == 0)
			execute(args, cgi_env);
	}
	int result = waitpid(pid, 0, WNOHANG);\
	if (result == -1)
		fail_in_execution(conf);
	else if (result > 0)
	{
		res.status_code = 200;
		res.file_path = out_file;
		parse_cgi_outfile();
		if (res.headers.find("Content-Type") == res.headers.end())
			res.headers["Content-Type"] = "html/txt";
		res.headers["Content-Length"] = std::to_string(strtol(get_file_size(res.file_path).c_str(), NULL, 10) - res.byte_sent);
		res.is_cgi = 0;
	}
}