/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:20:01 by sennaama          #+#    #+#             */
/*   Updated: 2023/05/26 16:08:41 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP
# include "../lib.hpp"
class request
{
    public:
        int			status_code;
        std::string	method;
        std::string	path;
	    std::string	version;
        std::map<std::string, std::string> header;
        request();
        void request_parse(std::string buf);
        void print_request();
        ~request();
};
#endif
