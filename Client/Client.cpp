/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:59:15 by sennaama          #+#    #+#             */
/*   Updated: 2023/06/25 14:43:34 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
//Client::Client():response(""),request(""),client_socket(0),recv(-1),send(-1){}
Client::Client(int client_socket): req(), res(),socket_client(client_socket),recv(-1),send(-1),state(-1){}

// Client::Client(const Client& obj)
// {
//     response = obj.response;
//     request = obj.request;
//     client_socket = obj.client_socket;
// }

// Client& Client::operator=(const Client& obj)
// {
//     if (this != &obj)
//     {
//         response = obj.response;
//         request = obj.request;
//         client_socket = obj.client_socket;
//     }
//     return (*this);
// }
Client::~Client(){}

// std::string	Client::getResponse()
// {
//     return response;
// }

// void	Client::setPesponse(std::string response)
// {
//     this->response = response;
// }

// std::string	Client::getRequest()
// {
//     return request;
// }

// void    Client::setRequest(std::string request)
// {
//     this->request = request;
// }

// int Client::getClientSocket()
// {
//     return client_socket;
// }

// void    Client::setCLientSocket(int client_socket)
// {
//     this->client_socket = client_socket;
// }

// int Client::getRecv()
// {
//     return (recv);
// }

// void    Client::setRecv(int recv)
// {
//     this->recv = recv;
// }

// int Client::getSend()
// {
//     return (send);
// }

// void	Client::setSend(int send)
// {
//     this->send = send;
// }