/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 17:25:56 by sennaama          #+#    #+#             */
/*   Updated: 2023/05/26 17:00:32 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP
# include "../lib.hpp"
# include "../Client/Client.hpp"

class server
{
	public:
		Configuration			conf;
		std::vector<Client *>	clients;
		struct sockaddr_in		serv_addr;
		//int                 	addrlen;
		int                 	socket_server;
		std::vector<int>    	listeners;
		server();
		~server();
		void    process(char *file);
		void    addEvent(int kq, int fd, int fileter);
		void    DisableEvent(int kq, int fd, int fileter);
		void    DeleteEvent(int kq, int fd, int fileter);
		void    EnableEvent(int kq, int fd, int fileter);
		void    listener_port(int port);
		void    multiplixing(const char *response);
};
#endif