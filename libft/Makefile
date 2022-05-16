# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/28 08:31:56 by wdebotte          #+#    #+#              #
#    Updated: 2022/05/05 23:15:33 by wdebotte         ###   ########.fr        #
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

PATHSRCS	= ./srcs/
PATHHEADERS	= ./includes/
PATHNULL	= /dev/null

SRCS 		= ${PATHSRCS}str/ft_isalpha.c \
			${PATHSRCS}str/ft_isdigit.c\
			${PATHSRCS}str/ft_isalnum.c \
			${PATHSRCS}str/ft_isascii.c \
			${PATHSRCS}str/ft_isprint.c\
			${PATHSRCS}str/ft_isspace.c \
			${PATHSRCS}str/ft_toupper.c \
			${PATHSRCS}str/ft_tolower.c \
			${PATHSRCS}str/ft_strncmp.c \
			${PATHSRCS}str/ft_strdup.c \
			${PATHSRCS}str/ft_strchr.c \
			${PATHSRCS}str/ft_strrchr.c \
			${PATHSRCS}str/ft_strnstr.c \
			${PATHSRCS}str/ft_substr.c \
			${PATHSRCS}str/ft_strjoin.c \
			${PATHSRCS}str/ft_strtrim.c \
			${PATHSRCS}str/ft_split.c \
			${PATHSRCS}str/ft_strmapi.c \
			${PATHSRCS}str/ft_strlen.c \
			${PATHSRCS}str/ft_strlcpy.c \
			${PATHSRCS}str/ft_strlcat.c \
			${PATHSRCS}str/ft_striteri.c \
			${PATHSRCS}str/ft_putchar.c \
			${PATHSRCS}str/ft_putstr.c \
			${PATHSRCS}str/iswhitespace.c \
			\
			${PATHSRCS}mem/ft_memcmp.c \
			${PATHSRCS}mem/ft_bzero.c \
			${PATHSRCS}mem/ft_memset.c \
			${PATHSRCS}mem/ft_memcpy.c \
			${PATHSRCS}mem/ft_memmove.c \
			${PATHSRCS}mem/ft_memchr.c \
			${PATHSRCS}mem/ft_calloc.c \
			\
			${PATHSRCS}file/ft_putchar_fd.c \
			${PATHSRCS}file/ft_putstr_fd.c \
			${PATHSRCS}file/ft_putendl_fd.c \
			${PATHSRCS}file/ft_putnbr_fd.c \
			${PATHSRCS}file/is_ext_correct.c \
			${PATHSRCS}file/get_next_line.c \
			\
			${PATHSRCS}lst/ft_lstsize.c \
			${PATHSRCS}lst/ft_lstadd_back.c \
			${PATHSRCS}lst/ft_lstadd_front.c \
			${PATHSRCS}lst/ft_lstiter.c \
			${PATHSRCS}lst/ft_lstdelone.c \
			${PATHSRCS}lst/ft_lstclear.c \
			${PATHSRCS}lst/ft_lstlast.c \
			${PATHSRCS}lst/ft_lstnew.c \
			${PATHSRCS}lst/ft_lstmap.c \
			\
			${PATHSRCS}int/ft_atoi_base.c \
			${PATHSRCS}int/ft_atoi.c \
			${PATHSRCS}int/ft_atoli.c \
			${PATHSRCS}int/ft_itoa_base.c \
			${PATHSRCS}int/ft_itoa.c \
			${PATHSRCS}int/ft_putnbr.c \
			\
			${PATHSRCS}printf/printf.c \
			${PATHSRCS}printf/putnbrs.c \
			${PATHSRCS}printf/utils.c

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
