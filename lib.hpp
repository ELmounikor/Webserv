/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:13:32 by mel-kora          #+#    #+#             */
/*   Updated: 2023/07/11 10:34:48 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef     LIB_WERBSERV_HPP
# define    LIB_WERBSERV_HPP
# include   <map>
# include   <set>
# include   <ctime>
# include   <vector>
# include   <cstdio>
# include   <csignal>
# include   <netdb.h>
# include   <cstring>
# include   <cstdlib>
# include   <fstream>
# include   <sstream>
# include   <fcntl.h>
# include   <iostream>
# include   <iterator>
# include   <unistd.h>
# include   <dirent.h>
# include   <sys/stat.h>
# include   <sys/types.h>
# include   <sys/event.h>
# include   <sys/socket.h>
# include   <netinet/in.h>
# include   "request/request.hpp"
# include   "Parsing/Configuration.hpp"
# include   "Response/Response.hpp"
# define    MAX_EVENTS 60000
void        ft_exit(std::string msg);
#endif
