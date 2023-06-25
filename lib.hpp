/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:13:32 by mel-kora          #+#    #+#             */
/*   Updated: 2023/06/25 13:03:01 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef     LIB_WERBSERV_HPP
# define    LIB_WERBSERV_HPP
# include   <map>
# include   <vector>
# include   <ctime>
# include   <cstdio>
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
# include <netdb.h>
# include   "request/request.hpp"
# include   "Parsing/Configuration.hpp"
# include   "Response/Response.hpp"
# define    MAX_EVENTS 20000
void        ft_exit(std::string msg);
#endif
