/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:13:32 by mel-kora          #+#    #+#             */
/*   Updated: 2023/05/28 17:03:26 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef     WEBSERV_HPP
# define    WEBSERV_HPP
# include   <map>
# include   <vector>
# include   <cstdio>
# include   <cstring>
# include   <cstdlib>
# include   <fstream>
# include   <sstream>
# include   <iostream>
# include   <iterator>
# include   <unistd.h>
# include   <sys/event.h>
# include   <sys/socket.h>
# include   <netinet/in.h>
# include   "request/request.hpp"
# include   "Response/Response.hpp"
# include   "Parsing/Configuration.hpp"
# define    MAX_EVENTS 20000
void        ft_exit(std::string msg);
#endif
