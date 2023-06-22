/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Send_nd_execute.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:33:41 by mel-kora          #+#    #+#             */
/*   Updated: 2023/06/22 18:42:06 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"
#include "../Client/Client.hpp"

int	send_response(Client *cli)
{
	std::string res_header = cli->res.get_header(cli->req);
	if (!cli->res.is_finished)
	{
		if (send(cli->socket_client, res_header.c_str(), res_header.size(), 0) < 0)
			perror("client send error");
		cli->res.is_finished = 1;
	}
	if (cli->res.status_code % 100 == 3 || cli->res.status_code == 204)
		cli->res.is_finished++;
	else if (cli->res.is_cgi)
	{
		execute_cgi(cli);
		cli->res.is_finished++;
	}
	else if (cli->res.body != "")
	{
		if (send(cli->socket_client, cli->res.body.c_str(), cli->res.body.size(), 0) < 0)
			perror("client send error");
		cli->res.is_finished++;
	}
	else if (cli->res.body_file.is_open())
	{
		char buf[1024];
		memset(buf, 0, 1024);
		if (cli->res.body_file.read(buf, 1024))
		{
			if (send(cli->socket_client, buf, 1024, 0) < 0)
				perror("client send error");
		}
		else
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
