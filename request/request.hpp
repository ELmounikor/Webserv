/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:20:01 by sennaama          #+#    #+#             */
/*   Updated: 2023/07/06 06:42:22 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP
# include "../lib.hpp"
class request
{
    public:
        std::map<std::string, std::string> header;
        std::string     data;
        std::string     method;
        std::string     path;
	    std::string     version;
        std::fstream   body_file;
        std::string     name_file;
        int             status_code;
        int             size;
        int             contentLength;
        int             flag;
        request();
		std::string	trim(std::string str);
		std::string get_extension(std::string content_type);
		void		request_parse(std::string buf, int socket_client);
        void		header_parse(std::string buf);
        void		print_request();
        void		get_method(std::string assign);
		void		post_method(std::string assign);
		void		appendtofile(std::string str, std::string filename);
		int			countcharacter(std::string str, char c);
        ~request();
};
#endif
