/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:13:21 by mel-kora          #+#    #+#             */
/*   Updated: 2023/06/12 16:01:33 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Webserv.hpp"
#include "lib.hpp"

void	ft_exit(std::string msg)
{
	std::cerr << "\033[0;91mError: " + msg + "\n\033[0m";
	exit(1);
}

std::string get_fake_res_from_fake_req(char **av)
{
	Configuration	conf(av[1]);
	request			req;
	Response		res;
	
	print_config(conf);
	std::cout << "\033[0;91*************SENDING REQUEST*****************\n\033[0m";
	req.request_parse(av[2], 0);
	req.print_request();
	std::cout << "\033[0;91*************GETTING RESPONSE****************\n\033[0m";
	res.response_fetch(req, conf);
	return (res.response_content);
}

int	main(int ac, char **av)
{
	(void) ac;
	std::cout << get_fake_res_from_fake_req(av);
	// if (ac != 2)
	// 	ft_exit("Either too little or too much arguments 👽");
	// server s;
	// s.process(av[1]);
	return 0;
}