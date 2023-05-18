/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 17:22:51 by sennaama          #+#    #+#             */
/*   Updated: 2023/05/18 21:56:10 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include <arpa/inet.h>

server::server():clients()
{
	// if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    //     ft_exit("socket");
	// addrlen = sizeof(address);
	// address.sin_family = AF_INET;
    // address.sin_addr.s_addr = INADDR_ANY;
    // address.sin_port = htons(8080);
	// memset(address.sin_zero, '\0', sizeof address.sin_zero);
}

server::~server(){}

void    server::addEvent(int kq, int fd, int fileter)
{
    struct kevent events[1];
    EV_SET(&events[0], fd, fileter, EV_ADD, 0, 0, NULL);
    if (kevent(kq, events, 1, NULL, 0, NULL) < 0)
    {
        perror("addEvent");
        exit(1);
    }
}

void    server::DisableEvent(int kq, int fd, int fileter)
{
    struct kevent events[1];
    EV_SET(events, fd, fileter, EV_DISABLE, 0, 0, NULL);
    if (kevent(kq, events, 1, NULL, 0, NULL) < 0)
    {
        perror("DisableEvent");
        exit(1);
    }
}

void    server::DeleteEvent(int kq, int fd, int fileter)
{
    struct kevent events[1];
    EV_SET(events, fd, fileter, EV_DELETE, 0, 0, NULL);
    if (kevent(kq, events, 1, NULL, 0, NULL) < 0)
    {
        perror("DeleteEvent");
        exit(1);
    }
}

void    server::EnableEvent(int kq, int fd, int fileter)
{
    struct kevent events[1];
    EV_SET(events, fd, fileter, EV_ENABLE, 0, 0, NULL);
    if (kevent(kq, events, 1, NULL, 0, NULL) < 0)
    {
        perror("EnableEvent");
        exit(1);
    }
}

void    server::listener_port(int port)
{
    int opt = true;

    if (((socket_server = socket(AF_INET, SOCK_STREAM, 0)) < 0))
    {
        perror("ERROR opening socket");
        exit(1);
    }
    if (setsockopt(socket_server, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        perror("setsockopt");
        exit(1);
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);
    memset(serv_addr.sin_zero, 0, sizeof (serv_addr.sin_zero));
    if (bind(socket_server, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("bind");
        exit(1);
    }
    if (listen(socket_server, SOMAXCONN) < 0)
    {
        perror("listen");
        exit(1);
    }
    listeners.push_back(socket_server);
}

void    server::multiplixing(const char *response)
{
    int client_len, socket_client, kq, new_events;
    struct kevent event[MAX_EVENTS];
    client_len = sizeof(serv_addr);
    kq = kqueue();
    //addEvent(kq, socket_server, EVFILT_READ);
    size_t j = 0;
    while (j < listeners.size())
    {
        //std::cout << "port:" << listeners[j] << std::endl;
		//listener_port((i)->port);
        addEvent(kq, listeners[j], EVFILT_READ);
	    j++;
    }
    while(true)
    {
        new_events = kevent(kq, NULL, 0, event, MAX_EVENTS, NULL);
        if (new_events == -1)
        {
            perror("kevent");
            exit(1);
        }
        std::cout<<"dsf"<<std::endl;
        for (int i = 0; i < new_events; i++)
        {
            std::cout<<"new event: "<<new_events<<std::endl;
            int event_fd = event[i].ident;
            if (event[i].filter == EVFILT_READ)
            {
                if (std::find(listeners.begin(), listeners.end(), event_fd) != listeners.end())
                {
                    std::cout<<"New connection coming in...\n";    

                    socket_client = accept(event_fd, (struct sockaddr *)&serv_addr, (socklen_t *)&client_len);
                    if (socket_client == -1)
                    {
                        perror("Accept socket error");
                    }
                    addEvent(kq, socket_client, EVFILT_READ);
                }
                else
                {
                    char buf[1024];
                    size_t bytes_read = recv(event_fd, buf, sizeof(buf), 0);
                    if (bytes_read <= 0)
                    {
                        if (bytes_read < 0)
                            std::cout<<"client read error\n";
                        else if (bytes_read == 0)
                        {
                            DeleteEvent(kq, socket_client, EVFILT_READ);
                            close(event_fd);
                        }
                    }
                    else
                    {
                        std::cout<<buf<<std::endl;
                        addEvent(kq, socket_client, EVFILT_WRITE);
                        DisableEvent(kq, socket_client, EVFILT_READ);
                    }
                }
            }
            else if (event[i].filter == EVFILT_WRITE)
            {
                std::cout << "Received data from client with ID: " << event_fd << std::endl;
                if (send(event_fd, response, strlen(response), 0) == -1)
                {
                    std::cout<<"client send error\n";
                    close(event_fd);
                }
                DisableEvent(kq, socket_client, EVFILT_WRITE);
                close(event_fd);
            }
        }
    }
}

void    server::process(char *file)
{
    const char *response ("HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: \
        12\n\nHello world!");
    Configuration	conf(file);
	std::vector<Server>::iterator i = conf.servers.begin();
    while (i != conf.servers.end())
    {
        std::cout << "port:" << (i)->port << std::endl;
		listener_port((i)->port);
	    i++;
    }
    std::cout<<"sdf"<<std::endl;
    multiplixing(response);
}
