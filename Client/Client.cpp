/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:59:15 by sennaama          #+#    #+#             */
/*   Updated: 2023/07/13 10:58:34 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
Client::Client(int client_socket): req(), res(),socket_client(client_socket),state(-1), pid(-1), out_file(""){}

Client::~Client()
{
	if (req.header["Host"] != "" || req.method != ""  || req.path != "")
	std::cout << "\033[0;99m[Client Socket "<<socket_client<<" closed ]  Host=<"\
	<<req.header["Host"].c_str()<<">  Method=<"<<req.method.c_str()<<">  URI=<"\
	<<req.path.c_str()<<">\033[0m\n"<< std::endl;
	if (pid > 0 && !waitpid(pid, 0, WNOHANG))
		kill(pid, SIGKILL);
}
