/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:13:21 by mel-kora          #+#    #+#             */
/*   Updated: 2023/04/12 17:10:27 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Webserv.hpp"

void	ft_exit(std::string msg)
{
	std::cerr << "\033[0;91mError: " + msg + "\n\033[0m";
	exit(1);
}

int	main(int ac, char **av)
{
	//if (ac != 2)
	//	ft_exit("Either too little or too much arguments 👽");
	//Configuration conf(av[1]);
	(void) ac;
	(void) av;
	server b;
	b.process("HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: \
	12\n\nHello world!");
	return 0;
}