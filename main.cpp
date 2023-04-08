/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:13:21 by mel-kora          #+#    #+#             */
/*   Updated: 2023/04/08 16:58:50 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	Configuration conf(av[1]);
	//db arak lkhdma ><
	return 0;
}