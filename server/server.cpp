/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 17:22:51 by sennaama          #+#    #+#             */
/*   Updated: 2023/07/04 20:16:08 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include <arpa/inet.h>
#include <cerrno>

server::server():clients(){
	kq = kqueue();
	events = (struct kevent *)malloc(sizeof(struct kevent));
}

server::~server(){}

void    server::addEvent(int kq, int& fd, int fileter)
{
	EV_SET(&events[0], fd, fileter, EV_ADD, 0, 0, NULL);
	
	if (kevent(kq, &events[0], 1, NULL, 0, NULL) < 0)
	{
		perror("addEvent");
	}
}

void    server::DisableEvent(int kq, int& fd, int fileter)
{
	EV_SET(&events[0], fd, fileter, EV_DISABLE, 0, 0, NULL);
	if (kevent(kq, events, 1, NULL, 0, NULL) < 0)
	{
		perror("DisableEvent");
	}
}

void    server::DeleteEvent(int kq, int& fd, int fileter)
{
	EV_SET(&events[0], fd, fileter, EV_DELETE, 0, 0, NULL);
	if (kevent(kq, &events[0], 1, NULL, 0, NULL) < 0)
	{
		perror("DeleteEvent");
	}
}

void    server::EnableEvent(int kq, int& fd, int fileter)
{
	EV_SET(&events[0], fd, fileter, EV_ENABLE, 0, 0, NULL);
	if (kevent(kq, &events[0], 1, NULL, 0, NULL) < 0)
	{
		perror("EnableEvent");
	}
}

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
        std::cerr << (get_add_errno) << std::endl;
    }

	if ((socket_server = socket(servinfo->ai_family,servinfo->ai_socktype,servinfo->ai_protocol)) < 0){
        perror("Server_Socket");
        exit(EXIT_FAILURE);
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
	addEvent(kq, socket_server, EVFILT_READ);
	listeners.push_back(socket_server);
}

int     server::ft_exist(int new_events, int client)
{
	for (int e = 0; e < new_events; e++)
	{
		int event_ident = r_events[e].ident;
		if (client == event_ident)
		{
			if (r_events[e].filter ==  EVFILT_READ)
				return (1);
			else if (r_events[e].filter ==  EVFILT_WRITE)
				return (0);
		}
	}
	return (-1);
}

void    server::multiplixing()
{
	int socket_client, new_events;
	struct timespec timeout;
    timeout.tv_sec = 0;
    timeout.tv_nsec = 0;
	while(true)
	{
		new_events = kevent(kq, NULL, 0, r_events, MAX_EVENTS, NULL);
		if (new_events == -1)
		{
			perror("kevent");
			exit(1);
		}
		for (int i = 0; i < new_events; i++)
		{

			int event_fd = r_events[i].ident;
			std::cout<<"new event: "<< event_fd<< "\n";
			if (r_events[i].filter == EVFILT_READ)
			{
				if (std::find(listeners.begin(), listeners.end(), event_fd) != listeners.end())
				{
					std::cout<<"New connection coming in...\n";
					socket_client = accept(*(std::find(listeners.begin(), listeners.end(), event_fd)), NULL , NULL);
					if (socket_client == -1)
					{
						perror("Accept socket error");
					}
					Client *new_client = new Client(socket_client);
					if (fcntl(new_client->socket_client, F_SETFL ,O_NONBLOCK) < 0)
                        perror("FCNTL Error");
					addEvent(kq, new_client->socket_client, EVFILT_READ);
					new_client->state =0;
					clients.push_back(new_client);
				}
				else
				{
					for (std::vector<Client *>::iterator j = clients.begin(); j != clients.end();)
                    {
                        if (ft_exist(new_events, (*j)->socket_client) == 1 && ((*j)->state == 0))
                        {
                            char buf[6000 + 1];
                            int bytes_read = recv((*j)->socket_client, buf, 6000, 0);
                            if (bytes_read <= 0)
							{
								perror("Client recv error");
								DeleteEvent(kq, (*j)->socket_client, EVFILT_READ);
                                close((*j)->socket_client);
                                delete *j;
                                clients.erase(j);
							}
                            else
                            {
								buf[bytes_read] = 0;
								std::string assign(buf, buf + bytes_read);
                                (*j)->req.request_parse(assign, (*j)->socket_client);
								//(*j)->req.print_request();
								
                                if ((*j)->req.flag == -1)
                                {
									//std::cout << "client request complete " << (*j)->socket_client << std::endl;
									// (*j)->req.print_request();
                                    (*j)->res.response_fetch((*j)->req, conf);
									
			                        DisableEvent(kq, (*j)->socket_client, EVFILT_READ);
                                    addEvent(kq, (*j)->socket_client, EVFILT_WRITE);
									(*j)->state = 1;
									//	r_events[i].filter = EVFILT_WRITE;
									// exit(0);
                                }
                                j++;
                            }
                        }
                        else
                            j++;
                    }
				}
			}
			else if (r_events[i].filter == EVFILT_WRITE)
			{
				
				for (std::vector<Client *>::iterator j = clients.begin(); j < clients.end();)
				{
					if (ft_exist( new_events, (*j)->socket_client) == 0 && ((*j)->state == 1)) 
					{	
						int i  = send_response(*j);
						if (i)
						{
						std::cout << i;
							std::vector<Client *>::iterator tmp = j++;
							DeleteEvent(kq, (*tmp)->socket_client, EVFILT_WRITE);
							DeleteEvent(kq, (*tmp)->socket_client, EVFILT_READ);
							close((*tmp)->socket_client);
							delete *tmp;
							clients.erase(tmp);
	std::cout << "connection dropped " << clients.size() << std::endl;
						}
						else
							j++;
						// const char *response ("HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: \
						// 12\n\nHello world!");
						// if (send((*j)->socket_client, response, strlen(response), 0) == -1)
                        //     std::cout<<"client send errorfff\n";
						
                        // DeleteEvent(kq, (*j)->socket_client, EVFILT_WRITE);
						// DeleteEvent(kq, (*j)->socket_client, EVFILT_READ);
                        // close((*j)->socket_client);
                        // delete *j;
                        // clients.erase(j);
					}
					else
						j++;
				}
			}
		}
	}
}

void    server::process(char *file)
{
	
	this->conf = Configuration(file);
	std::vector<Server_info>::iterator i = conf.servers.begin();
	while (i != conf.servers.end())
	{
		listener_port((i)->port);
		i++;
	}
	multiplixing();
}
