/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Send_nd_execute.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:33:41 by mel-kora          #+#    #+#             */
/*   Updated: 2023/07/05 13:08:05 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"
#include "../Client/Client.hpp"

void	print_interaction(Client *cli)
{
	std::cout << "\033[0;93m[ Request From Socket "<<cli->socket_client<<" ]  Host=<"<<cli->req.header["Host"].c_str()<<\
	">  Method=<"<<cli->req.method.c_str()<<">  URI=<"<<cli->req.path.c_str()<<">\033[0m\n";
	std::cout << "\033[0;96m[ Response To Socket "<<cli->socket_client<<" ]   Status=<"<<cli->res.status_code<<\
	">  Path=<"<<cli->res.file_path.c_str()<<">\033[0m\n";
}

int	send_response(Client *cli)
{
	std::string res_header = cli->res.get_header(cli->req);
	if (!cli->res.is_finished)
	{
		print_interaction(cli);
		if (send(cli->socket_client, res_header.c_str(), res_header.size(), 0) < 0)
			perror("client send header error");
		cli->res.is_finished = 1;
		if (cli->res.status_code / 100 == 3 || cli->res.status_code == 204 || cli->res.status_code == 201)
		cli->res.is_finished = 2;
	} 
	else if (cli->res.body != "")
	{
		if (send(cli->socket_client, cli->res.body.c_str(), cli->res.body.size(), 0) < 0)
			perror("client send body error");
		cli->res.is_finished = 2;
	}
	else if (cli->res.is_cgi)
	{
		execute_cgi(cli);
		cli->res.is_finished = 2;
	}
	else
	{
		if (cli->res.byte_sent != (ssize_t) strtol(cli->res.headers["Content-Length"].c_str(), NULL, 10))
		{
			char buf[65536];
			cli->res.body_file.open(cli->res.file_path);
			cli->res.body_file.seekg(cli->res.byte_sent);
			cli->res.body_file.read(buf, sizeof(buf));
			ssize_t read = cli->res.body_file.gcount();
			if (read > 0)
			{
				std::string data(buf, read);
				long sent = send(cli->socket_client, data.c_str(), data.size(), 0);
				if (sent < 0)
				{
					perror("client send file error");
					cli->res.is_finished = 2;
				}
				else
					cli->res.byte_sent += sent;
			}
			else
			{
				perror("client read file error");
				cli->res.is_finished = 2;
			}
		}
		else
			cli->res.is_finished = 2;
		cli->res.body_file.close();
		cli->res.body_file.clear();
	}
	if (cli->res.is_finished == 2)
		return (1);
	return (0);
}

void	execute_cgi(Client *cli)
{
	std::string file_path = cli->res.file_path;
	std::string executable_path = cli->res.exec_path;
	// to_be_continued
}
