# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/21 19:15:16 by apavel            #+#    #+#              #
#    Updated: 2021/05/29 15:03:25 by alvrodri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS    = ft_strlen.c ft_strchr.c ft_strncmp.c ft_isalpha.c ft_isdigit.c ft_strdup.c ft_atoi.c ft_strnstr.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_putstr_fd.c ft_split_ignore_quotes.c ft_free_split.c
BONUS_SRCS = ft_lstsize_bonus.c
NEW = ft_replace.c
OBJS    = ${SRCS:.c=.o}
BONUS_OBJS = ${BONUS_SRCS:.c=.o}
NEW_OBJS = ${NEW:.c=.o}
NAME    = libft.a
CC      = cc
RM      = rm -f
CFLAGS  = -Wall -Werror -Wextra
.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}
${NAME}: ${OBJS} ${BONUS_OBJS} ${NEW_OBJS}
	ar rc ${NAME} ${OBJS} ${BONUS_OBJS} ${NEW_OBJS}
	ranlib ${NAME}
all: ${NAME}
clean:
	${RM} ${OBJS} ${BONUS_OBJS} ${NEW_OBJS}
fclean: clean
	${RM} ${NAME}
bonus: ${OBJS} ${BONUS_OBJS}
	ar rc ${NAME} ${OBJS} ${NEW_OBJS} ${BONUS_OBJS}
	ranlib ${NAME}
re: fclean bonus

.PHONY: all clean fclean bonus re
