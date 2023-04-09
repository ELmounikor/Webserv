/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:13:21 by mel-kora          #+#    #+#             */
/*   Updated: 2023/04/09 18:15:46 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.hpp"
#include "server/server.hpp"

void	ft_exit(std::string msg)
{
	std::cerr << "\033[0;91mError: " + msg + "\n\033[0m";
	exit(1);
}

int	main(int ac, char **av)
{
	//if (ac != 2)
	//	ft_exit("Either too little or too much arguments 👽");
	(void) ac;
	(void) av;
	//Configuration conf(av[1]);
	//db arak lkhdma ><
	server("HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: \
	12\n\nHello world!");
	return 0;
}