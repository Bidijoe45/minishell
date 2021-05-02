SRCS =	./srcs/fresh.c \
		./srcs//print/print.c \
		./srcs/commands/variable.c \
		./srcs/commands/command.c \
		./srcs/parser/parser.c \
		./srcs/list/list.c \
		./srcs/commands/echo.c ./srcs/commands/exit.c ./srcs/commands/pwd.c ./srcs/commands/cd.c \
		./srcs/commands/env.c ./srcs/commands/export.c ./srcs/commands/unset.c
GNL	= ./resources/get_next_line/get_next_line.c
NAME = minishell
OBJS = ${SRCS:.c=.o}
CC = gcc
CFLAGS = #-Wall -Wextra -Werror
SANITIZE = -g3 -fsanitize=address

${NAME}:	${OBJS}
			make -C ./resources/ft_printf/
			gcc ${GNL} ${OBJS} -L ./resources/ft_printf -l ftprintf -o ${NAME}
all:		${NAME}
clean:
			rm -f ${OBJS}
			make clean -C ./resources/libft
			make clean -C ./resources/ft_printf
fclean:		clean
			rm -f ${NAME}
			make fclean -C ./resources/libft
			make fclean -C ./resources/ft_printf
re:			fclean all
.PHONY:		all clean fclean re
