/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 11:40:01 by sennaama          #+#    #+#             */
/*   Updated: 2023/07/11 20:25:01 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

server::server():clients(),maxFd(0)
{
    FD_ZERO(&readSet);
    FD_ZERO(&writeSet);
}
server::~server(){}

void    server::listener_port(int port)
{

	memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
	
	int opt = true;
	int get_add_errno = 0;

	std::stringstream sd;
	sd << port;

	std::string s;
	sd >> s;
	
	if ((get_add_errno = getaddrinfo(NULL, s.c_str(), &hints, &servinfo)) != 0){
        perror("get add info");
		exit(1);
    }

	if ((socket_server = socket(servinfo->ai_family,servinfo->ai_socktype,servinfo->ai_protocol)) < 0){
        perror("Server_Socket");
        exit(1);
    }
	if (setsockopt(socket_server, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
	{
		perror("setsockopt");
		exit(1);
	}
	if (setsockopt(socket_server, SOL_SOCKET, SO_NOSIGPIPE, &opt, sizeof(opt)) < 0)
	{
		perror("setsockopt2");
		exit(1);
	}
	if (fcntl(socket_server, F_SETFL ,O_NONBLOCK) < 0)
        perror("FCNTL Error");
	if (bind(socket_server, (struct sockaddr*)servinfo->ai_addr,servinfo->ai_addrlen) < 0)
	{
		perror("bind");
		exit(1);
	}
	if (listen(socket_server, SOMAXCONN) < 0)
	{
		perror("listen");
		exit(1);
	}
    FD_SET(socket_server, &readSet);
	listeners.push_back(socket_server);
	if (socket_server > maxFd)
    	maxFd = socket_server;
	freeaddrinfo(servinfo);
}

void	server::AddClient(int socket)
{
	Client *new_client = new Client(socket);
	if (fcntl(new_client->socket_client, F_SETFL ,O_NONBLOCK) < 0)
        perror("FCNTL Error");
	FD_SET(socket, &readSet);
	clients.push_back(new_client);
    if (socket > maxFd)
    {
        maxFd = socket;
    }
}

void	server::DeleteClient(int i)
{	
	if (clients[i]->req.header["Host"] != "" || clients[i]->req.method != ""  || clients[i]->req.path != "")
	std::cout << "\033[0;99m[Client Socket "<<clients[i]->socket_client<<" closed ]  Host=<"\
	<<clients[i]->req.header["Host"].c_str()<<">  Method=<"<<clients[i]->req.method.c_str()<<">  URI=<"\
	<<clients[i]->req.path.c_str()<<">\033[0m\n"<< std::endl;
	close(clients[i]->socket_client);
	delete clients[i];
	clients.erase(clients.begin() + i);
}

void	server::request_part(Client* cli, std::string assign)
{
	cli->req.request_parse(assign, cli->socket_client);
	if (cli->req.flag == -1)
	{
		//cli->req.print_request();
		cli->res.response_fetch(cli->req, conf);
		FD_CLR(cli->socket_client, &readSet);
		FD_SET(cli->socket_client, &writeSet);
	}
}

void	server::multiplixing()
{
    fd_set readSet_copy;
    fd_set writeSet_copy;
    int socket_client;
    while(true)
    {
		readSet_copy =  readSet;
        writeSet_copy = writeSet;
        activity = select(maxFd + 1, &readSet_copy, &writeSet_copy, NULL, NULL);
        if (activity < 0) {
            perror("Select error");
        }
		for (std::vector<int>::iterator it = listeners.begin(); it != listeners.end(); it++)
		{
			socket_server =  *it;
			if (FD_ISSET(socket_server, &readSet_copy)) 
			{
				socket_client = accept(socket_server, NULL, NULL);
				if (socket_client == -1)
				{
					perror("Accept socket error");
				}
				else 
					AddClient(socket_client);
			}
	    }
        for (size_t i = 0; i < clients.size(); i++) 
		{
            if (FD_ISSET(clients[i]->socket_client, &readSet_copy)) {
                char buf[6000 + 1];
				int bytes_read = recv(clients[i]->socket_client, buf, 6000, 0);
                if (bytes_read <= 0)
				{
					FD_CLR(clients[i]->socket_client, &readSet);
					DeleteClient(i);
				}
                else
                {
                    buf[bytes_read] = 0;
					std::string assign(buf, buf + bytes_read);
					request_part(clients[i], assign);
                }
            }
            else if (FD_ISSET(clients[i]->socket_client, &writeSet_copy))
			{
                int res = clients[i]->send_response(conf);
				if (res)
				{
					FD_CLR(clients[i]->socket_client, &writeSet);
					DeleteClient(i);
				}
            }
        }
    }
}


void    server::process(char *file)
{
	this->conf = Configuration(file);
	// print_vector(conf.server_ports);
	std::set<int>::iterator i = conf.server_ports.begin();
	// conf.print_config();
	while (i != conf.server_ports.end())
	{
		listener_port(*i);
		i++;
	}
	multiplixing();
}
