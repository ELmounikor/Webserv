/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 17:25:56 by sennaama          #+#    #+#             */
/*   Updated: 2023/05/20 17:43:55 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP
# include "../lib.hpp"
# include "../Client/Client.hpp"

class server
{
    public:
        std::vector<Client *> clients;
        struct sockaddr_in  serv_addr;
        //int                 addrlen;
        int                 socket_server;
        std::vector<int>    listeners;
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