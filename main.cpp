/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:13:21 by mel-kora          #+#    #+#             */
/*   Updated: 2023/03/30 14:23:23 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.hpp"

int main(int ac, char **av)
{
	if (ac == 2)
	{
		(void) av;
	}
	else
		std::cout << "\033[0;91mError: Either too little or too much arguments 👽\n\033[0m";
}