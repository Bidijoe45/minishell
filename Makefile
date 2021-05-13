SRCS =	./srcs/fresh.c \
		./srcs//print/print.c \
		./srcs/commands/variable.c \
		./srcs/commands/command.c \
		./srcs/parser/parser.c \
		./srcs/list/list.c \
		./srcs/signal/signal.c \
		./srcs/syntax/syntax_checker.c \
		./srcs/syntax/syntax_error_1.c ./srcs/syntax/syntax_error_2.c ./srcs/syntax/syntax_error_3.c ./srcs/syntax/syntax_error_aux.c \
		./srcs/commands/echo.c ./srcs/commands/exit.c ./srcs/commands/pwd.c ./srcs/commands/cd.c \
		./srcs/commands/env.c ./srcs/commands/export.c ./srcs/commands/unset.c \
		./srcs/pipe/pipes.c ./srcs/exec/exec.c ./srcs/memory/free_1.c ./srcs/file/file.c \
		./srcs/exec/exec_aux_1.c ./srcs/exec/exec_aux_2.c \
		./srcs/commands/export_aux.c
NAME = minishell
OBJS = ${SRCS:.c=.o}
CC = gcc
CFLAGS = #-Wall -Wextra -Werror
SANITIZE = -g3 -fsanitize=address

${NAME}:	${OBJS}
			make -C ./resources/ft_printf/
			gcc ${OBJS} -L ./resources/ft_printf -l ftprintf -o ${NAME}
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
