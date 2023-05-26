/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:59:12 by sennaama          #+#    #+#             */
/*   Updated: 2023/05/26 18:15:07 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP
#include "../lib.hpp"

class Client
{
	public:
		request		req;
		Response	res;
		int			socket_client;
		int 		recv;
		int			send;
	
		//Client();
		Client(int client_socket);
		//Client(const Client& obj);
		//Client& operator=(const Client& obj);
		~Client();
		// std::string	getResponse();
		// void	setPesponse(std::string response);
		// std::string	getRequest();
		// void	setRequest(std::string request);
		// int		getClientSocket();
		// void	setCLientSocket(int client_socket);	
		// int 	getRecv();
		// void	setRecv(int recv);	
		// int 	getSend();
		// void	setSend(int send);	
};
#endif