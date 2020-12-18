SRCS =	fresh.c \
		./print/print.c \
		./commands/command.c ./commands/cd.c ./commands/clear.c ./commands/exit.c ./commands/export.c ./commands/pwd.c ./commands/unset.c ./commands/variable.c ./commands/env.c
GNL	= ./get_next_line/get_next_line.c
NAME = minishell
OBJS = ${SRCS:.c=.o}
CC = gcc
CFLAGS = #-Wall -Wextra -Werror
SANITIZE = -g -fsanitize=address

${NAME}:	${OBJS}
			make -C ../ft_printf/
			gcc ${GNL} ${OBJS} -Lft_printf -lftprintf -o ${NAME} ${SANITIZE}
all:		${NAME}
clean:
			rm ${OBJS}
			make clean -C ./libft
			make clean -C ./ft_printf
fclean:		clean
			rm ${NAME}
			make fclean -C ./libft
			make fclean -C ./ft_printf
re:			fclean all
.PHONY:		all clean fclean re
