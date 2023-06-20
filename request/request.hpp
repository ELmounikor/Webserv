/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:20:01 by sennaama          #+#    #+#             */
/*   Updated: 2023/06/18 21:11:16 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP
# include "../lib.hpp"
class request
{
    public:
        int             status_code;
        std::string     method;
        std::string     path;
	    std::string     version;
        std::ofstream   body_file;
        int             size;
        int				contentLength;
        std::map<std::string, std::string> header;
        int             flag;
        request();
		std::string	trim(std::string str);
		std::string get_extension(std::string content_type);
		void		request_parse(std::string buf, int socket_client);
        void		header_parse(std::string buf);
        void		print_request();
        void		get_method(std::string assign);
		void		post_method(std::string assign, int socket_client);
		void		appendtofile(std::string str, std::string filename);
		int			countcharacter(std::string str, char c);
        ~request();
};
#endif
