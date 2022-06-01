# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjhin <mjhin@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/16 10:57:09 by mvenmo            #+#    #+#              #
#    Updated: 2022/04/14 15:20:36 by mjhin            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	libft.a

SRCS =	ft_atoi.c		ft_isdigit.c	ft_memmove.c	ft_split.c		ft_strlcpy.c	\
		ft_strtrim.c	ft_bzero.c		ft_isprint.c	ft_memset.c		ft_strchr.c		\
		ft_strlen.c		ft_substr.c		ft_calloc.c		ft_itoa.c		ft_putchar_fd.c	\
		ft_strdup.c		ft_strmapi.c	ft_tolower.c	ft_isalnum.c	ft_memchr.c		\
		ft_putendl_fd.c	ft_striteri.c	ft_strncmp.c	ft_toupper.c	ft_isalpha.c	\
		ft_memcmp.c		ft_putnbr_fd.c	ft_strjoin.c	ft_strnstr.c	ft_isascii.c	\
		ft_memcpy.c		ft_putstr_fd.c	ft_strlcat.c	ft_strrchr.c	ft_strcmp.c		\
		ft_lstadd_back_bonus.c   ft_lstdelone_bonus.c  ft_lstmap_bonus.c	\
		ft_lstadd_front_bonus.c  ft_lstiter_bonus.c    ft_lstnew_bonus.c	\
		ft_lstclear_bonus.c      ft_lstlast_bonus.c    ft_lstsize_bonus.c

SRCS_B =ft_lstadd_back_bonus.c   ft_lstdelone_bonus.c  ft_lstmap_bonus.c	\
		ft_lstadd_front_bonus.c  ft_lstiter_bonus.c    ft_lstnew_bonus.c	\
		ft_lstclear_bonus.c      ft_lstlast_bonus.c    ft_lstsize_bonus.c

OBJS	=	${SRCS:.c=.o}
OBJS_B	=	${SRCS_B:.c=.o}

DFILE	=	dependencies.d

CC		= cc -Wall -Wextra -Werror

.SILENT:
.PHONY:		all clean fclean bonus re

all:		${NAME}

-include $(DFILE)

${NAME}:	${OBJS}
			ar rcs ${NAME} $?

%.o:		%.c Makefile
			${CC} -c -o $@ $< 
			${CC} -MM $< >> $(DFILE)

bonus:
			make SRCS="${SRCS_B}"

clean:
			rm -f ${OBJS} ${OBJS_B} $(DFILE)

fclean:		clean
			rm -f ${NAME}

re:			fclean all