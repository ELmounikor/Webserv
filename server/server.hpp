/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 17:25:56 by sennaama          #+#    #+#             */
/*   Updated: 2023/06/25 17:03:27 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP
# include "../lib.hpp"
# include "../Client/Client.hpp"

class server
{
	public:
		struct addrinfo hints , *servinfo;
		Configuration			conf;
		std::vector<Client *>	clients;
		// struct sockaddr_in		serv_addr;
		//int                 	addrlen;
		int                 	socket_server;
		std::vector<int>    	listeners;
		int						kq;
		server();
		~server();
		void    process(char *file);
		void    addEvent(int kq, int& fd, int fileter);
		void    DisableEvent(int kq, int& fd, int fileter);
		void    DeleteEvent(int kq, int& fd, int fileter);
		void    EnableEvent(int kq, int& fd, int fileter);
		struct kevent *events;
		struct kevent r_events[MAX_EVENTS];
		void    listener_port(int port);
		void    multiplixing();
		int     ft_exist(int new_events, int client);
};

#endif