/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:12:52 by mel-kora          #+#    #+#             */
/*   Updated: 2023/05/31 18:27:16 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Response_HPP
# define Response_HPP
# include "../lib.hpp"

class request;
class Configuration;
class Response
{
	public:
		int			status_code;
		std::string	http_version;
		std::string	reason_phrase;
		std::string	host;
		std::string	path;
		Response();
		void	check_param(const request &req, Configuration conf);
		void	get_response(void);
};

#endif
