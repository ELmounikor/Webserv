/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:13:21 by mel-kora          #+#    #+#             */
/*   Updated: 2023/05/25 13:32:36 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Webserv.hpp"
#include "lib.hpp"

void	ft_exit(std::string msg)
{
	std::cerr << "\033[0;91mError: " + msg + "\n\033[0m";
	exit(1);
}

int	main(int ac, char **av)
{
	if (ac != 2)
		ft_exit("Either too little or too much arguments 👽");
	server s;
	s.process(av[1]);
	return 0;
}