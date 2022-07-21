# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xle-baux <xle-baux@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/18 14:12:28 by wdebotte          #+#    #+#              #
#    Updated: 2022/07/21 15:08:06 by wdebotte         ###   ########.fr        #
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

PATHSRCS	= srcs/
PATHHEADERS	= includes/
PATHLIBFT	= libft/
PATHNULL	= /dev/null

SRCS		= $(addprefix ${PATHSRCS}, main.c) \
			$(addprefix ${PATHSRCS}builtins/, is_builtin.c exec_builtin.c \
						export.c unset.c env.c cd.c pwd.c echo.c export_utils.c \
						exit.c) \
			$(addprefix ${PATHSRCS}execution/, exec_pipes.c exec_cmd.c \
						pipes_utils.c exec_simplecmd.c redirections_control.c) \
			$(addprefix ${PATHSRCS}utils/, memory.c is_str_clear.c \
						strcmp.c fill_command_path.c puterror.c print_message.c) \
			$(addprefix ${PATHSRCS}utils/env/, env_add_and_remove.c varcmp.c \
						cp_env.c is_var_in_env.c get_env_var_value.c \
						set_pwd_var.c set_shlvl.c) \
			$(addprefix ${PATHSRCS}signals/, signals.c) \
			$(addprefix ${PATHSRCS}parser/, parser.c token_lexer.c \
						quotes_format.c dollar_format.c cat_word.c tools.c \
						command_set.c tmp_tools.c get_command_path.c \
						check_syntax.c redir.c heredoc.c check_redir_syntax.c)

OBJS		= ${SRCS:.c=.o}
HEADERS		= ${PATHHEADERS}

CC			= clang
CFLAGS		= -Wall -Wextra -Werror -g3
INCS		= -I${PATHHEADERS} -I${PATHLIBFT}${PATHHEADERS}

RM			= rm -rf
MAKE		= make -C
NORM		= norminette

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
				${NORM} ${SRCS}
				@echo "${BOLD}${GREEN}Norminette:${END}\tOK !\n"
				@echo "${BOLD}${YELLOW}Norminette:${END}\tAll .h files"
				${NORM} ${HEADERS}
				@echo "${BOLD}${GREEN}Norminette:${END}\tOK !"

re:			fclean all

.PHONY:		all clean fclean re norminette

################################################################################
