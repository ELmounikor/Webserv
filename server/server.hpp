/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 17:25:56 by sennaama          #+#    #+#             */
/*   Updated: 2023/04/11 18:27:16 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP
# include "../lib.hpp"
# include "../Client/Client.hpp"
class server
{
    private:
        std::vector<Client *> clients;
        struct sockaddr_in address;
        int                 addrlen;
        int                 server_socket;
    public:
        server();
        server(const server& obj);
		server& operator=(const server& obj);
		~server();
        void process(const char *response);
};
#endif