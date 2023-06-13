# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/30 14:02:35 by mel-kora          #+#    #+#              #
#    Updated: 2023/06/13 18:16:52 by mel-kora         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	webserv
INCS		=	lib.hpp\
				server/server.hpp\
				Client/Client.hpp\
				request/request.hpp\
				Response/Methods.hpp\
				Response/Response.hpp\
				Parsing/Configuration.hpp\
				#more files
SRCS		=	main.cpp\
				server/server.cpp\
				Client/Client.cpp\
				request/request.cpp\
				Response/Utils.cpp\
				Response/Status.cpp\
				Response/Methods.cpp\
				Response/Response.cpp\
				Response/Attributes.cpp\
				Parsing/Configuration.cpp\
				Parsing/server_params.cpp\
				Parsing/server_checker.cpp\
				Parsing/location_params.cpp\
				#more files
OBJS		= 	${SRCS:.cpp=.o}
CC			= 	@c++
RM			= 	@rm -rf
CPPFLAGS	= 	-Wall -Werror -Wextra -std=c++98

.cpp.o : $(INCS)
	@$(CC) $(CPPFLAGS) -c $< -o $@
	@echo "\033[1;96m*\033[0m"

all : $(NAME)
	@echo "\033[1;93m	 _ ≧◉ᴥ◉≦ __     __                        \033[0m"
	@echo "\033[1;93m	| |     / /__  / /_  ________  ______   __\033[0m"
	@echo "\033[1;93m	| | /| / / _ \/ __ \/ ___/ _ \/ ___/ | / /\033[0m"
	@echo "\033[1;93m	| |/ |/ /  __/ /_/ (__  )  __/ /   | |/ / \033[0m"
	@echo "\033[1;93m	|__/|__/\___/_.___/____/\___/_/    |___/  \033[0m"
	@echo "\033[1;93m	                              MANDATORY   \033[0m"

$(NAME) : $(INCS) $(OBJS)
	@$(CC) $(CPPFLAGS) $(OBJS) -o $(NAME)
	@echo "\033[1;96m\n	----> files created \033[0m"

clean:
	@$(RM) $(OBJS) 
	@echo "\033[1;94m	----> files deleted \033[0m"

fclean:		clean
	@$(RM) $(NAME)
	@echo "\033[1;94m	ʕ•́ᴥ•̀ʔっ\033[0m"

re:			fclean all

.PHONY: all clean fclean re 