/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:13:32 by mel-kora          #+#    #+#             */
/*   Updated: 2023/04/11 18:43:28 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef     WEBSERV_HPP
# define    WEBSERV_HPP
# include <iostream>
# include <fstream>
# include <cstring>
# include <cstdlib>
# include <cstdio>
# include <sys/socket.h>
# include <netinet/in.h>
# include <vector>
# include <map>
# include "Parsing/Configuration.hpp"
# include "unistd.h"
# include <vector>
# include <iterator>
# define PORT 8080
void	ft_exit(std::string msg);
#endif
