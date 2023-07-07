/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:59:12 by sennaama          #+#    #+#             */
/*   Updated: 2023/07/07 19:08:08 by mel-kora         ###   ########.fr       */
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
		int			state;

		Client(int client_socket);
		~Client();
		int			send_response(Configuration conf);
		void		fail_in_execution(Configuration conf);
		void		post_file_chunk(Configuration conf);
		void		execute_cgi(Configuration conf);
		void		send_response_header(void);
		void		print_interaction(void);
		void		send_file_chunk(void);
		void		get_cgi_env(std::vector<std::string> cgi_env_var, char *cgi_env[14]);
		std::string	get_QueryString(void);
};

#endif