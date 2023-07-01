/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Send_nd_execute.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:33:41 by mel-kora          #+#    #+#             */
/*   Updated: 2023/07/01 15:35:24 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"
#include "../Client/Client.hpp"

void	print_interaction(Client *cli)
{
	printf("\033[0;93m[ Request From Socket %d]  Host=<%s>  Method=<%s>  URI=<%s>\033[0m\n", \
	cli->socket_client, cli->req.header["Host"].c_str(), cli->req.method.c_str(), cli->req.path.c_str());
	printf("\033[0;96m[ Response To Socket %d]   Status=<%d>  Path=<%s>\033[0m\n", \
	cli->socket_client, cli->res.status_code, cli->res.file_path.c_str());
}

int	send_response(Client *cli)
{
	std::string res_header = cli->res.get_header(cli->req);
	if (!cli->res.is_finished)
	{
		print_interaction(cli);
		if (send(cli->socket_client, res_header.c_str(), res_header.size(), 0) < 0)
		{
			cli->res.is_finished = 2;
			perror("client send error");
		}
		cli->res.is_finished = 1;
	}
	else if (cli->res.status_code / 100 == 3 || cli->res.status_code == 204 || cli->res.status_code == 201)
		cli->res.is_finished++;
	else if (cli->res.body != "")
	{
		if (send(cli->socket_client, cli->res.body.c_str(), cli->res.body.size(), 0) < 0)
		{
			cli->res.is_finished = 2;
			perror("client send error");
		}
		cli->res.is_finished++;
	}
	else if (cli->res.body_file.is_open())
	{
		if (!cli->res.body_file.eof())
		{
			char buf[1024];
			memset(buf, 0, 1024);
			cli->res.body_file.read(buf, 1024);
			size_t	byte_read = cli->res.body_file.gcount();
			if (send(cli->socket_client, buf, byte_read, 0) < 0)
			{
				cli->res.is_finished = 2;
				perror("client send error");
			}
		}
		else
			cli->res.is_finished++;		
	}
	else if (cli->res.is_cgi)
	{
		execute_cgi(cli);
		cli->res.is_finished++;
	}
	if (cli->res.is_finished == 2)
	{
		cli->res.reset_response();
		return (1);
	}
	return (0);
}

void	execute_cgi(Client *cli)
{
	std::string file_path = cli->res.file_path;
	std::string executable_path = cli->res.exec_path;
	// to_be_continued
}
