/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 11:40:27 by sennaama          #+#    #+#             */
/*   Updated: 2023/07/12 10:35:22 by sennaama         ###   ########.fr       */
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
		std::vector<Client *>	clients;
		Configuration			conf;
		int                 	socket_server;
		std::vector<int>    	listeners;
        int maxFd, activity, fd;
        fd_set readSet, writeSet;
		server();
		~server();
        void	listener_port(int port);
		void	AddClient(int socket);
        void	multiplixing();
		void	DeleteClient(int i);
		void	request_part(Client* cli, std::string assign);
		void	process(char *file);
};
#endif