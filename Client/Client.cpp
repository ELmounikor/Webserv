/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:59:15 by sennaama          #+#    #+#             */
/*   Updated: 2023/07/11 11:33:42 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
Client::Client(int client_socket): req(), res(),socket_client(client_socket),state(-1), pid(-1), out_file(""){}

Client::~Client()
{
	if (pid != -1 && res.is_finished != 2)
	{
		kill(pid, SIGINT);
		std::cout << "\033[0;96mINFINITE LOOP DETECTED\033[0m\n";
	}
}
