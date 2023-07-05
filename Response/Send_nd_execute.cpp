/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Send_nd_execute.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:33:41 by mel-kora          #+#    #+#             */
/*   Updated: 2023/07/05 08:27:30 by sennaama         ###   ########.fr       */
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
		// std::cout << "\033[0;95m"<< res_header << " \033[0m\n";
		if (send(cli->socket_client, res_header.c_str(), res_header.size(), 0) < 0)
			perror("client send error");
		cli->res.is_finished = 1;
		if (cli->res.status_code / 100 == 3 || cli->res.status_code == 204 || cli->res.status_code == 201)
		cli->res.is_finished = 2;
	} 
	else if (cli->res.body != "")
	{
		if (send(cli->socket_client, cli->res.body.c_str(), cli->res.body.size(), 0) < 0)
			perror("client send error");
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
			if (cli->res.body_file.is_open())
				cli->res.body_file.close();
			cli->res.body_file.open(cli->res.file_path);
			cli->res.body_file.seekg(cli->res.byte_sent);
			cli->res.body_file.read(buf, sizeof(buf));
			std::streamsize read = cli->res.body_file.gcount();
			// std::cout << "You read " << read << " bytes\n";
			if (read > 0)
			{
				std::string data(buf, read);
				// std::cout << "****************\n";
				// std::cout << "sok:" << cli->socket_client << "\n";
				// std::cout << "state:" << cli->state << "\n";
				// std::cout << "****************\n";
				long sent = send(cli->socket_client, data.c_str(), data.size(), 0);
				//std::cout <<data.size() << "->" << sent << "\n";
				
				if (sent < 0)
				{
					cli->res.is_finished = 2;
					perror("send:");
				}
				else
				{
						cli->res.byte_sent += sent;
				}
				// while (sent < 0)
				// {
				// 	usleep(10);
				// 	sent = send(cli->socket_client, data.c_str(), data.size(), 0);
				// }
				// if (sent > 0)
					//std::cout << "YOU SENT " << cli->res.byte_sent << " bytes out of " << strtol(cli->res.headers["Content-Length"].c_str(), NULL, 10) << "\n";
				// {
				// }
			}
			else
			{
				std::cout << "LOSERch\n";
				cli->res.is_finished = 2;
			}
			cli->res.body_file.close();
		}
		else
		{
			std::cout << "WINNER\n";
			cli->res.is_finished = 2;
		}
	}
	// else if (cli->res.body_file.is_open())
	// {
	// 	if (!cli->res.body_file.eof())
	// 	{
	// 		char buf[65536];
	// 		memset(buf, 0, 65536);
	// 		cli->res.body_file.read(buf, 65536);
	// 		size_t	byte_read = cli->res.body_file.gcount();
	// 		ssize_t byte_sent = send(cli->socket_client, buf, byte_read, 0);
	// 		if ( byte_sent< 0)
	// 		{
	// 			cli->res.is_finished = 2;
	// 			perror("client send error");
	// 		}
	// 		cli->res.byte_sent += byte_sent;
	// 		std::cout << "We sent " << cli->res.byte_sent << " bytes out of " + cli->res.headers["Content-Length"] + "\n";
	// 	}
	// 	else
	// 		cli->res.is_finished = 2;		
	// }
	if (cli->res.is_finished == 2)
	{
		// print_interaction(cli);
		// cli->res.reset_response();
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
