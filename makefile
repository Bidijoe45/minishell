SRCS =	fresh.c \
		./print/print.c \
		./commands/variable.c \
		./commands/command.c \
		./music.c \
		./parser/parser.c \
		./list/list.c \
		./commands/echo.c ./commands/exit.c ./commands/pwd.c ./commands/cd.c \
		./commands/env.c ./commands/export.c ./commands/unset.c
GNL	= ./get_next_line/get_next_line.c
NAME = minishell
OBJS = ${SRCS:.c=.o}
CC = gcc
CFLAGS = #-Wall -Wextra -Werror
SANITIZE = -g3 -fsanitize=address

${NAME}:	${OBJS}
			make -C ./ft_printf/
			gcc ${GNL} ${OBJS} -Lft_printf -lftprintf -o ${NAME}
all:		${NAME}
clean:
			rm -f ${OBJS}
			make clean -C ./libft
			make clean -C ./ft_printf
fclean:		clean
			rm -f ${NAME}
			make fclean -C ./libft
			make fclean -C ./ft_printf
re:			fclean all
.PHONY:		all clean fclean re
