/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:13:21 by mel-kora          #+#    #+#             */
/*   Updated: 2023/07/12 10:37:21 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Webserv.hpp"
#include "lib.hpp"

void	ft_exit(std::string msg)
{
	std::cerr << "\033[0;91mError: " + msg + "\n\033[0m";
	exit(1);
}

void	death_catcher(int sig_code)
{
	if (sig_code == SIGINT || sig_code == SIGQUIT)
	{
		kill(0, SIGINT);
		int pid = getpid();
		kill(pid, SIGINT);
	}
}

int	main(int ac, char **av)
{
	std::signal(SIGPIPE, SIG_IGN);
	if (ac != 2)
		ft_exit("Either too little or too much arguments 👽");
	server s;
	s.process(av[1]);
	return (0);
}