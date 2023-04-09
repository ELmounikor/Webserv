/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 17:22:51 by sennaama          #+#    #+#             */
/*   Updated: 2023/04/09 18:26:36 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void    server(const char *response)
{
    int server_socket, client_socket, valrecv;
	struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        ft_exit("socket");
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    memset(address.sin_zero, '\0', sizeof address.sin_zero);
    if (bind(server_socket, (struct sockaddr *)&address, sizeof(address)) < 0)
        ft_exit("bind");
    if (listen(server_socket, 1) < 0)
        ft_exit("listen");
    while(1)
    {
        std::cout<<"\n+++++++ Waiting for new connection ++++++++\n\n";
        if ((client_socket = accept(server_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
            ft_exit("accept");
        char buffer[30000] = {0};
        valrecv = recv(client_socket , buffer, sizeof(buffer), 0);
        std::cout << "Request: " << buffer << "\n";
        send(client_socket, response, strlen(response), 0);
        close(client_socket);
    }
}