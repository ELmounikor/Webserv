/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Send_nd_execute.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:33:41 by mel-kora          #+#    #+#             */
/*   Updated: 2023/07/08 17:56:36 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib.hpp"
#include "../Client/Client.hpp"

void	Client::print_interaction()
{
	std::cout << "\033[0;93m[ Request From Socket "<<socket_client<<" ]  Host=<"\
	<<req.header["Host"].c_str()<<">  Method=<"<<req.method.c_str()<<">  URI=<"\
	<<req.path.c_str()<<">\033[0m\n";
	std::cout << "\033[0;96m[ Response To Socket "<<socket_client<<" ]   Status=<"\
	<<res.status_code<<">  Path=<"<<res.file_path.c_str()<<">\033[0m\n";
}

void	Client::send_response_header(void)
{
	std::string res_header = res.get_header(req);
	print_interaction();
	if (send(socket_client, res_header.c_str(), res_header.size(), 0) < 0)
		perror("client send header error");
}

int	Client::send_response(Configuration conf)
{
	if (res.is_cgi)
		execute_cgi(conf);
	else if (res.status_code == 201)
		post_file_chunk(conf);
	else if (!res.is_finished)
	{
		send_response_header();
		res.is_finished = 1;
		if (res.status_code / 100 == 3 || res.status_code == 201)
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
	{
		if (check_path(req.name_file))
			std::remove(req.name_file.c_str());
		if (check_path(out_file))
			std::remove(out_file.c_str());
		return (1);
	}
	return (0);
}

void	Client::send_file_chunk(void)
{
	if (res.byte_sent != (ssize_t) strtol(res.headers["Content-Length"].c_str(), NULL, 10))
	{
		res.body_file.open(res.file_path);
		if (res.body_file.is_open())
		{
			char buf[65536] = {0};
			res.body_file.seekg(res.byte_sent);
			res.body_file.read(buf, sizeof(buf));
			ssize_t read = res.body_file.gcount();
			if (read >= 0)
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
		{
			perror("client open file error");
			res.is_finished = 2;
		}
	}
	else
		res.is_finished = 2;
}

void	Client::post_file_chunk(Configuration conf)
{
	std::fstream	out_file(res.file_path, std::fstream::out | std::fstream::app);
	std::ifstream	in_file(res.exec_path);
	
	if (!out_file.is_open() || !in_file.is_open())
	{
		if (in_file.is_open())	in_file.close();
		if (out_file.is_open())	out_file.close();
		fail_in_execution(conf);
		return ;
	}
	in_file.seekg(res.byte_sent);
	if (!in_file.eof())
	{
		char buf[65536] = {0};
		in_file.read(buf, 65536);
		ssize_t read = in_file.gcount();
		if (read >= 0)
		{
			std::string data(buf, read);
			out_file << data;
			res.byte_sent += read;
		}
		else
		{
			perror("client read bodyfile error");
			fail_in_execution(conf);
			return ;
		}
	}
	bool last_read = in_file.eof();
	out_file.close();
	in_file.close();
	if (last_read)
	{
		if (res.byte_sent != (ssize_t)strtol((get_file_size(res.exec_path)).c_str(), NULL, 10))
		{
			fail_in_execution(conf);
			return ;
		}
		send_response_header();
		res.is_finished = 2;
	}
}
