/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:13:32 by mel-kora          #+#    #+#             */
/*   Updated: 2023/07/02 12:09:16 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef     LIB_WERBSERV_HPP
# define    LIB_WERBSERV_HPP
# include   <map>
# include   <ctime>
# include   <vector>
# include   <cstdio>
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
# define    MAX_EVENTS 20000
void        ft_exit(std::string msg);
#endif
