/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:12:52 by mel-kora          #+#    #+#             */
/*   Updated: 2023/05/26 17:12:36 by mel-kora         ###   ########.fr       */
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
		Response(request req, Configuration conf);
		void	get_response(void);
};

#endif
