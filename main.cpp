/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:13:21 by mel-kora          #+#    #+#             */
/*   Updated: 2023/03/30 17:57:52 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.hpp"

void ft_exit(std::string msg)
{
	std::cerr << "\033[0;91mError: " + msg + "\n\033[0m";
	exit(1);
}

int main(int ac, char **av)
{
	std::string		content;
	
	if (ac != 2)
		ft_exit("Either too little or too much arguments 👽");
	std::ifstream conf_file(av[1]);
	if (!conf_file.is_open())
		ft_exit("Cannot open configuration file 👽");
	std::getline(conf_file, content, '\0');
	//db arak lkhdma ><
	return 0;
}