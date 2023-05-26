/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:12:52 by mel-kora          #+#    #+#             */
/*   Updated: 2023/05/26 14:51:44 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Response_HPP
# define Response_HPP
# include "../lib.hpp"

class request;
class Response
{
	public:
		int			status_code;
		std::string	location;
		Response(request req);
};
#endif
