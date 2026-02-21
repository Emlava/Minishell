# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hudescam <hudescam@student.42belgium.be    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/14 13:05:16 by hudescam          #+#    #+#              #
#    Updated: 2026/02/21 12:00:37 by hudescam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBC =	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
		ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c \
		ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c \
		ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c \
		ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c \
		ft_inputchar.c ft_inputhexa.c ft_inputnbr.c ft_inputpoint.c \
		ft_inputstr.c ft_inputunsid.c ft_printf.c get_next_line.c \
		get_next_line_utils.c ft_strcmp.c

ADDITIONAL	=	ft_itoa.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
				ft_split.c ft_strjoin.c ft_strmapi.c ft_strtrim.c ft_substr.c ft_striteri.c \
				ft_dprintf/ft_dprintf.c ft_dprintf/ft_d_csu_percent.c ft_dprintf/ft_d_p.c \
				ft_dprintf/ft_d_di.c ft_dprintf/ft_d_xx.c

BONUS	=	ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c \
			ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c

SRCS = ${LIBC} ${ADDITIONAL} ${BONUS}

OBJS = ${SRCS:.c=.o}

LIB = libft.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra -I ./

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${LIB}:	${OBJS}
		ar -rsc ${LIB} ${OBJS}

all: 	${LIB}

clean:	
		rm -f ${OBJS}

fclean:	clean;
		rm -f ${LIB}

re:	fclean all

.PHONY: all clean fclean re bonus