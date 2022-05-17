# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/18 14:12:28 by wdebotte          #+#    #+#              #
#    Updated: 2022/05/17 13:58:50 by wdebotte         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
# => TEXT
################################################################################

END		= \033[0m
BOLD	= \033[1m

RED		= \033[91m
GREEN	= \033[92m
YELLOW	= \033[93m
CYAN	= \033[96m

################################################################################
# => VARIABLES
################################################################################

NAME		= minishell

PATHSRCS	= ./srcs/
PATHHEADERS	= ./includes/
PATHLIBFT	= ./libft/
PATHNULL	= /dev/null

SRCS		= ${PATHSRCS}main.c

OBJS		= ${SRCS:.c=.o}
HEADERS		= ${PATHHEADERS}

CC			= clang
CFLAGS		= -Wall -Wextra -Werror
INCS		= -I${PATHHEADERS} -I${PATHLIBFT}${PATHHEADERS}

RM			= rm -rf
MAKE		= make -C

NORM		= norminette
FLAGC		= -R CheckForbiddenSourceHeader
FLAGH		= -R CheckDefine

LIBFT		= -L${PATHLIBFT} -lft

################################################################################
# => RULES
################################################################################

.c.o:
				@echo "${BOLD}${YELLOW}Compiling:${END}\t$<"
				@${CC} ${CFLAGS} ${INCS} -c $< -o ${<:.c=.o} >${PATHNULL}

all:		${NAME}

${NAME}:	${OBJS}
				@echo "${BOLD}${GREEN}Building:${END}\tlibft.a"
				@${MAKE} ${PATHLIBFT} >${PATHNULL}
				@echo "${BOLD}${GREEN}Building:${END}\t${NAME}"
				@${CC} ${OBJS} ${INCS} ${LIBFT} -lreadline -o ${NAME} >${PATHNULL}

clean:
				@echo "${BOLD}${RED}Removing:${END}\tAll .o files"
				@${RM} ${OBJS} >${PATHNULL}

fclean:		clean
				@${MAKE} ${PATHLIBFT} fclean >${PATHNULL}
				@echo "${BOLD}${RED}Removing:${END}\t${NAME}"
				@${RM} ${NAME} >${PATHNULL}

norminette:
				@echo "${BOLD}${YELLOW}Norminette:${END}\tAll .c files"
				${NORM} ${FLAGC} ${SRCS}
				@echo "${BOLD}${GREEN}Norminette:${END}\tOK !\n"
				@echo "${BOLD}${YELLOW}Norminette:${END}\tAll .h files"
				${NORM} ${FLAGH} ${HEADERS}
				@echo "${BOLD}${GREEN}Norminette:${END}\tOK !"

re:			fclean all

.PHONY:		all clean fclean re norminette

################################################################################
