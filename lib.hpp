/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:13:32 by mel-kora          #+#    #+#             */
/*   Updated: 2023/06/12 17:17:45 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef     LIB_WERBSERV_HPP
# define    LIB_WERBSERV_HPP
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
# include   "Parsing/Configuration.hpp"
# include   "Response/Response.hpp"
# define    MAX_EVENTS 20000
void        ft_exit(std::string msg);
#endif
