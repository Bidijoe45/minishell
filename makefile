SRCS =	fresh.c \
		./print/print.c \
		./commands/command.c ./commands/cd.c ./commands/clear.c ./commands/env.c ./commands/exit.c ./commands/export.c ./commands/pwd.c ./commands/unset.c\
		./utils/env.c
GNL	= ./get_next_line/get_next_line.c
NAME = minishell
OBJS = ${SRCS:.c=.o}
CC = gcc
CFLAGS = #-Wall -Wextra -Werror

${NAME}:	${OBJS}
			make -C ../ft_printf/
			gcc ${GNL} ${OBJS} -Lft_printf -lftprintf -o ${NAME}
all:		${NAME}
clean:
			rm ${OBJS}
			make clean -C minishell
fclean:		clean
			rm ${NAME}
			make fclean -C minishell
re:			fclean all
.PHONY:		all clean fclean re
