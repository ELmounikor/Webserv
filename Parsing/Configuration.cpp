/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Configuration.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:16:16 by mel-kora          #+#    #+#             */
/*   Updated: 2023/04/08 16:57:55 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Configuration.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Configuration::Configuration(std::string file_name)
{
	std::string	content;
	std::ifstream conf_file(file_name);
	if (!conf_file.is_open())
		ft_exit("Cannot open configuration file 👽");
	std::getline(conf_file, content, '\0');
    conf_file.close();
	//db arak lkhdma ><
}

/*
** --------------------------------- METHODS ----------------------------------
*/


/* ************************************************************************** */