/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 17:22:51 by sennaama          #+#    #+#             */
/*   Updated: 2023/04/11 18:35:06 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include <arpa/inet.h>
server::server():clients()
{
	if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        ft_exit("socket");
	addrlen = sizeof(address);
	address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
	memset(address.sin_zero, '\0', sizeof address.sin_zero);
}

server::server(const server& obj)
{
	*this = obj;
}

server& server::operator=(const server& obj)
{
	if (this != &obj)
	{
		clients = obj.clients;
		addrlen = obj.addrlen;
		server_socket = obj.server_socket;
		address.sin_family = obj.address.sin_family;
    	address.sin_addr.s_addr = obj.address.sin_addr.s_addr;
    	address.sin_port = obj.address.sin_addr.s_addr;
		memcpy(&address.sin_zero, &obj.address.sin_zero, sizeof(obj.address.sin_zero));
	}
}

server::~server(){}

void server::process(const char *response)
{
	int     opt = true;
	int		valrecv;
	fd_set  readfds; 
	int		max_sd;
	int		sd;
    int     activity;
	
	if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 )  
        ft_exit("setsockopt");  
    if (bind(server_socket, (struct sockaddr *)&address, sizeof(address)) < 0)
        ft_exit("bind");
    if (listen(server_socket, 3) < 0)
        ft_exit("listen");
    std::cout<<"\n+++++++ Waiting for connections ++++++++\n\n";
    while(1)
    {
		FD_ZERO(&readfds);
		FD_SET(server_socket, &readfds);
		max_sd = server_socket;

        for (std::vector<Client *>::iterator it= clients.begin(); it != clients.end(); ++it)
        {
            Client* client = *it;
            sd = client->getClientSocket();
            if (sd > 0)
                FD_SET(sd, &readfds);
            if (sd > max_sd)
                max_sd = sd;
        }
		int activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);
        if ((activity < 0))
            ft_exit("select");
		if (FD_ISSET(server_socket, &readfds))
        {
            if ((server_socket = accept(server_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
                ft_exit("accept");
            std::cout<<"New connection: %s:%d\n"<< inet_ntoa(address.sin_addr)<< ntohs(address.sin_port)<<std::endl;
            char buffer[30000] = {0};
            if (recv(sd, buffer, sizeof(buffer), 0) > 0) {
                std::cout << "Request:\n" << buffer << "\n";
                Client* client = new Client("", buffer, sd);
                    clients.push_back(client);
                } else {
                    close(sd);
                }
        }
        valrecv = recv(client_socket , buffer, sizeof(buffer), 0);
        std::cout << "Request: " << buffer << "\n";
        send(client_socket, response, strlen(response), 0);
        close(client_socket);
    }
}