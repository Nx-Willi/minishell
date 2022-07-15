# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/28 08:31:56 by wdebotte          #+#    #+#              #
#    Updated: 2022/07/15 11:50:45 by wdebotte         ###   ########.fr        #
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

################################################################################
# => VARIABLES
################################################################################

NAME		= libft.a

PATHSRCS	= srcs/
PATHHEADERS	= includes/
PATHNULL	= /dev/null

SRCS		= $(addprefix ${PATHSRCS}str/, ft_isalpha.c ft_isdigit.c ft_isalnum.c \
						ft_isprint.c ft_isspace.c ft_toupper.c ft_tolower.c \
						ft_strncmp.c ft_strdup.c ft_strchr.c ft_strrchr.c \
						ft_strnstr.c ft_substr.c ft_strjoin.c ft_strtrim.c \
						ft_split.c ft_strmapi.c ft_strlen.c ft_strlcpy.c \
						ft_strlcat.c ft_striteri.c ft_putchar.c ft_putstr.c \
						iswhitespace.c) \
			$(addprefix ${PATHSRCS}mem/, ft_memcmp.c ft_bzero.c ft_memset.c \
						ft_memcpy.c ft_memmove.c ft_memchr.c ft_calloc.c) \
			$(addprefix ${PATHSRCS}file/, ft_putchar_fd.c ft_putstr_fd.c \
						ft_putendl_fd.c ft_putnbr_fd.c is_ext_correct.c \
						get_next_line.c) \
			$(addprefix ${PATHSRCS}lst/, ft_lstsize.c ft_lstadd_back.c \
						ft_lstadd_front.c ft_lstiter.c ft_lstdelone.c \
						ft_lstclear.c ft_lstlast.c ft_lstnew.c ft_lstmap.c) \
			$(addprefix ${PATHSRCS}int/, ft_atoi_base.c ft_atoi.c ft_atoli.c \
						ft_itoa_base.c ft_itoa.c ft_putnbr.c) \
			$(addprefix ${PATHSRCS}printf/, printf.c putnbrs.c utils.c) \

OBJS		= ${SRCS:.c=.o}

HEADERS		= ${PATHHEADERS}libft.h \
			${PATHHEADERS}printf.h

CC			= clang
CFLAGS		= -Wall -Wextra -Werror
INCS		= -I${PATHHEADERS}

RM			= rm -rf

NORM		= norminette
FLAGC		= -R CheckForbiddenSourceHeader
FLAGH		= -R CheckDefine

################################################################################
# => RULES
################################################################################

.c.o:
				@echo "${BOLD}${YELLOW}Compiling:${END}\t$<"
				@${CC} ${CFLAGS} ${INCS} -c $< -o ${<:.c=.o} >${PATHNULL}

all:		${NAME}

${NAME}:	${OBJS}
				@echo "${BOLD}${GREEN}Building:${END}\t${NAME}"
				@ar -rc ${NAME} ${OBJS} >${PATHNULL}

clean:
				@echo "${BOLD}${RED}Removing:${END}\tAll .o files"
				@${RM} ${OBJS} >${PATHNULL}

fclean:		clean
				@echo "${BOLD}${RED}Removing:${END}\t${NAME}"
				@${RM} ${NAME} >${PATHNULL}

re:			fclean all

norminette:
				@echo "${BOLD}${YELLOW}Norminette:${END}\tAll .c files"
				${NORM} ${FLAGC} ${SRCS}
				@echo "${BOLD}${GREEN}Norminette:${END}\tOK !\n"
				@echo "${BOLD}${YELLOW}Norminette:${END}\tAll .h files"
				${NORM} ${FLAGH} ${HEADERS}
				@echo "${BOLD}${GREEN}Norminette:${END}\tOK !"

.PHONY:		all clean fclean re norminette

################################################################################
