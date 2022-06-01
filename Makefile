# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvenmo <mvenmo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/14 10:10:30 by mvenmo            #+#    #+#              #
#    Updated: 2022/04/14 19:18:32 by mvenmo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

# List of mandatory files: 
SRC		=	main.c			str_array.c		command2.c		\
			list.c			parser.c		command3.c		\
			command.c		builtin.c		env_utils.c		\
			check_base.c	parser_pipe.c	builtin2.c		builtin3.c	\
			parser_utils.c	parser_cmd.c	prompt.c		here_doc.c	\
			add_infile_outfile_list.c	replace_tild.c

# List of bonus files:
SRC_B	=

OBJ		=	$(SRC:.c=.o)
DEPS	=	$(SRC:.c=.d)

CC		=	cc -Wall -Werror -Wextra

# Library "readline" must be installed before checking project
# On 21school-mac: 1. install homebrew 2. brew install readline 3. Check correct path:
#for school mac
 READLINE_PATH = ${HOME}/.brew/opt/readline
#for home mac
#READLINE_PATH = /usr/local/opt/readline
# On linux: sudo apt instal libreadline-dev 

#.SILENT:
.PHONY: all clean fclean re check&update_libft bonus

all:		check&update_libft $(NAME)

check&update_libft:
	@make -C libft all

-include $(DEPS)

$(NAME):	$(OBJ)
	$(CC) $^ -o $@ -lft -Llibft -lreadline -L$(READLINE_PATH)/lib

%.o:		%.c Makefile libft/libft.a
	$(CC) -MMD -c $< -o $@ -I. -Ilibft -I$(READLINE_PATH)/include

clean:
	@make -s -C libft $@
	rm -f $(OBJ) $(DEPS) $(SRC_B:.c=.o) $(SRC_B:.c=.d)

fclean:		clean
	@make -s -C libft $@
	rm -f $(NAME)

re:			fclean all

bonus:
#	@make SRC="$(SRC_B)"