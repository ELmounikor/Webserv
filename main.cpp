/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:13:21 by mel-kora          #+#    #+#             */
/*   Updated: 2023/06/20 22:36:51 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Webserv.hpp"
#include "lib.hpp"

void	ft_exit(std::string msg)
{
	std::cerr << "\033[0;91mError: " + msg + "\n\033[0m";
	exit(1);
}

// void get_fake_res_from_fake_req(char **av)
// {
// 	Configuration	conf(av[1]);
// 	request			req;
// 	Response		res;
	
// 	// print_config(conf);
// 	std::cout << "\n*************SENDING REQUEST *****************\n\n";
// 	// req.request_parse(av[2], 0);
// 	req.method = "GET";
// 	req.path = "/dir/li/3ajbek/ZZZ";
// 	req.version = "HTTP/1.1";
// 	req.header["Host"] = "localhost:7623";
// 	req.status_code = -1;
// 	req.print_request();
// 	std::cout << "\n*************GETTING RESPONSE ****************\n\n";
// 	res.response_fetch(req, conf);
// 	std::cout << res.response_content;
// }

int	main(int ac, char **av)
{
	//try
	//{
		// get_fake_res_from_fake_req(av);
		// exit(0);
		if (ac != 2)
			ft_exit("Either too little or too much arguments 👽");
		server s;
		s.process(av[1]);
	//}
	// catch(const std::exception& e)
	// {
	// 	std::cerr << e.what() << std::endl;
	// }
	return (0);
}