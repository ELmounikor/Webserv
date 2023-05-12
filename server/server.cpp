/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 17:22:51 by sennaama          #+#    #+#             */
/*   Updated: 2023/04/15 23:36:29 by sennaama         ###   ########.fr       */
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
    return (*this);
}

server::~server(){}

// void server::process(const char *response)
// {
// 	int     opt = true;
// 	int		valrecv;
// 	fd_set  readfds; 
// 	int		max_sd;
// 	int		sd;
	
// 	if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 )  
//         ft_exit("setsockopt");  
//     if (bind(server_socket, (struct sockaddr *)&address, sizeof(address)) < 0)
//         ft_exit("bind");
//     if (listen(server_socket, 3) < 0)
//         ft_exit("listen");
//     std::cout<<"\n+++++++ Waiting for connections ++++++++\n\n";
//     while(1)
//     {
// 		FD_ZERO(&readfds);
// 		FD_SET(server_socket, &readfds);
// 		max_sd = server_socket;

//         for (std::vector<Client *>::iterator it= clients.begin(); it != clients.end(); ++it)
//         {
//             Client* client = *it;
//             sd = client->getClientSocket();
//             if (sd > 0)
//                 FD_SET(sd, &readfds);
//             if (sd > max_sd)
//                 max_sd = sd;
//         }
// 		int activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);
//         if ((activity < 0))
//             ft_exit("select");
// 		if (FD_ISSET(server_socket, &readfds))
//         {
//             if ((sd = accept(server_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
//                 ft_exit("server:accept");
//             std::cout<<"New connection: "<< inet_ntoa(address.sin_addr)<<" "<<ntohs(address.sin_port)<<std::endl;
//             char buffer[30000] = {0};
//             if (recv(sd, buffer, sizeof(buffer), 0) > 0) {
//                 std::cout << "Request:\n" << buffer << "\n";
//                 Client* client = new Client("", buffer, sd);
//                     clients.push_back(client);
//                 } else {
//                     close(sd);
//                 }
//         }
//         for (std::vector<Client *>::iterator it= clients.begin(); it != clients.end(); ++it)
//         {
//             Client* client = *it;
//             sd = client->getClientSocket();
//             if (FD_ISSET(sd, &readfds)) {
//                 char buffer[30000] = {0};
//                 valrecv = recv(sd, buffer, sizeof(buffer), 0);
//                 if (valrecv <= 0) {
//                     std::cout<<"Connection closed: "<< inet_ntoa(address.sin_addr)<< ntohs(address.sin_port)<<std::endl;
//                     close(sd);
//                     clients.erase(std::remove(clients.begin(), clients.end(), client), clients.end());
//                     delete client;
//                 } else {
//                     printf("Request: %s", buffer);
//                     client->setRequest(buffer);
//                     send(sd, response, strlen(response), 0);
//                 }
//             }
//         }
//     }
// }

// void server::process(const char *response)
// {
//     fd_set	master;
//     fd_set	read_fds;
//     int		listener;
// 	int		newfd;
// 	char	buf[256];
// 	int     opt = true;
// 	int		fdmax;
	
// 	FD_ZERO(&master);
// 	FD_ZERO(&read_fds);
// 	listener = server_socket;
// 	if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 )  
//         ft_exit("setsockopt");  
//     if (bind(server_socket, (struct sockaddr *)&address, addrlen) < 0)
//         ft_exit("bind");
//     if (listen(server_socket, SOMAXCONN) < 0)
//         ft_exit("listen");
// 	FD_SET(listener, &master);
// 	fdmax = listener;
// 	while (true)
// 	{
// 		read_fds = master;
// 		if (select(fdmax + 1, &read_fds, NULL, NULL, NULL) == -1)
// 			std::cout<<"Error: select"<<std::endl;
// 		for (int i = 0; i <= fdmax + 1; i++)
// 		{
// 			if (FD_ISSET(i, &read_fds))
// 			{
// 				if (i == listener)
// 				{
// 					addrlen = sizeof(address);
//                     newfd = accept(listener, (struct sockaddr *)&address, (socklen_t*)&addrlen);
// 					if (newfd == -1)
// 						std::cout<<"Error:accept"<<std::endl;
// 					else 
// 					{
// 						FD_SET(newfd, &master);
// 						if (newfd > fdmax)
// 							fdmax = newfd;
// 						std::cout<<"New connection: "<< i << " " << inet_ntoa(address.sin_addr)<<" "<<ntohs(address.sin_port)<<std::endl;
// 					}
// 				}
// 				else
// 				{
// 					if (recv(i, buf, sizeof(buf), 0) < 0)
// 					{
// 						std::cout<<"Error:recv" << i <<std::endl;
// 						close(i);
// 						FD_CLR(i, &master);
// 					}
// 					else
// 					{
// 						for (int j = 0; j <= fdmax; j++)
// 						{
// 							if (FD_ISSET(j, &master))
// 							{
// 								if (j != listener && j != i)
// 									if (send(j, response, strlen(response), 0) < 0)
// 										std::cout<<"Error: send"<< i <<std::endl;
// 							}
// 						}	
// 					}
// 				}
// 			}
// 		}
// 	}
    
// }

void server::process(const char *response)
{
    fd_set read_fds;
    int newfd;
    char buf[10000];
    int opt = true;
    int fdmax = 0;

    FD_ZERO(&read_fds);
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        perror("setsockopt");
        exit(1);
    }
    if (bind(server_socket, (struct sockaddr *)&address, addrlen) < 0)
    {
        perror("bind");
        exit(1);
    }
    if (listen(server_socket, SOMAXCONN) < 0)
    {
        perror("listen");
        exit(1);
    }
    FD_SET(server_socket, &read_fds);
    fdmax = server_socket;
    while (true)
    {
        fd_set read_fds_copy = read_fds;
        int num = select(fdmax + 1, &read_fds_copy, NULL, NULL, NULL);
        for (int i = 0; i <= fdmax; i++)
        {
            if (FD_ISSET(i, &read_fds_copy))
            {
                if (i == server_socket)
                {
                    newfd = accept(server_socket, (struct sockaddr *)&address, (socklen_t *)&addrlen);
                    std::cout << newfd << std::endl;
                    FD_SET(newfd, &read_fds);
                    if (newfd < 0)
                    {
                        std::cout << "Error:accept" << std::endl;
                    }
                    else if (newfd >= fdmax)
                    {
                        fdmax = newfd;
                        std::cout << "Connection made" << std::endl;
                    }
                    std::cout << "New connection: " << i << " " << inet_ntoa(address.sin_addr) << " " << ntohs(address.sin_port) << std::endl;
                }
                else
                {
                    int l = recv(i, buf, 10000, 0);
                    if (l <= 0)
                    {
                        close(i);
                        FD_CLR(i, &read_fds);
                    }
                    else
                    {
                        std::cout << "Client with ID: " << i << " is disconnected." << std::endl;
                        std::cout << buf << std::endl;
                        send(i, response, sizeof(response), 0);
                    }
                }
            }
        }
    }
}