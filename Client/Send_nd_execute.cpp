/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Send_nd_execute.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:33:41 by mel-kora          #+#    #+#             */
/*   Updated: 2023/07/05 22:56:59 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Response/Response.hpp"
#include "../Client/Client.hpp"

void	Client::print_interaction()
{
	std::cout << "\033[0;93m[ Request From Socket "<<socket_client<<" ]  Host=<"\
	<<req.header["Host"].c_str()<<">  Method=<"<<req.method.c_str()<<">  URI=<"\
	<<req.path.c_str()<<">\033[0m\n";
	std::cout << "\033[0;96m[ Response To Socket "<<socket_client<<" ]   Status=<"\
	<<res.status_code<<">  Path=<"<<res.file_path.c_str()<<">\033[0m\n";
}

int	Client::send_response()
{
	std::string res_header = res.get_header(req);
	if (res.is_cgi)
		execute_cgi();
	else if (!res.is_finished)
	{
		print_interaction();
		if (send(socket_client, res_header.c_str(), res_header.size(), 0) < 0)
			perror("client send header error");
		res.is_finished = 1;
		if (res.status_code / 100 == 3 || res.status_code == 204 || res.status_code == 201)
		res.is_finished = 2;
	} 
	else if (res.body != "")
	{
		if (send(socket_client, res.body.c_str(), res.body.size(), 0) < 0)
			perror("client send body error");
		res.is_finished = 2;
	}
	else
		send_file_chunk();
	if (res.is_finished == 2)
		return (1);
	return (0);
}

void	Client::send_file_chunk()
{
	if (res.byte_sent != (ssize_t) strtol(res.headers["Content-Length"].c_str(), NULL, 10))
	{
		char buf[65536];
		res.body_file.open(res.file_path);
		res.body_file.seekg(res.byte_sent);
		res.body_file.read(buf, sizeof(buf));
		ssize_t read = res.body_file.gcount();
		if (read > 0)
		{
			std::string data(buf, read);
			ssize_t sent = send(socket_client, data.c_str(), data.size(), 0);
			if (sent < 0)
			{
				perror("client send file error");
				res.is_finished = 2;
			}
			else
				res.byte_sent += sent;
		}
		else
		{
			perror("client read file error");
			res.is_finished = 2;
		}
		res.body_file.close();
		res.body_file.clear();
	}
	else
		res.is_finished = 2;
}

void	Client::execute_cgi()
{
	std::string file_path = res.file_path;
	std::string executable_path = res.exec_path;
	// to_be_continued

	res.is_finished = 2;
}
