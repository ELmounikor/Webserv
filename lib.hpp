/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:13:32 by mel-kora          #+#    #+#             */
/*   Updated: 2023/05/22 11:08:57 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef     WEBSERV_HPP
# define    WEBSERV_HPP
# include <iostream>
# include <fstream>
# include <sstream>
# include <cstring>
# include <cstdlib>
# include <cstdio>
# include <sys/socket.h>
# include <netinet/in.h>
# include <map>
# include <vector>
# include <iterator>
# include "Parsing/Configuration.hpp"
# include <netinet/in.h>
# include <sys/event.h>
# include <unistd.h>
#   include "request/request.hpp"
# define MAX_EVENTS 20000
void	ft_exit(std::string msg);
#endif
