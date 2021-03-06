SRCS =	./srcs/fresh.c \
		./srcs//print/print.c \
		./srcs/commands/variable.c \
		./srcs/commands/command.c \
		./srcs/parser/parser.c\
		./srcs/list/list.c \
		./srcs/signal/signal.c \
		./srcs/syntax/syntax_checker.c \
		./srcs/syntax/syntax_error_1.c ./srcs/syntax/syntax_error_2.c ./srcs/syntax/syntax_error_3.c ./srcs/syntax/syntax_error_aux.c \
		./srcs/commands/echo.c ./srcs/commands/exit.c ./srcs/commands/pwd.c ./srcs/commands/cd.c \
		./srcs/commands/env.c ./srcs/commands/export.c ./srcs/commands/unset.c \
		./srcs/pipe/pipes.c ./srcs/pipe/fork.c ./srcs/exec/exec.c ./srcs/memory/free_1.c ./srcs/file/file.c \
		./srcs/exec/exec_aux_1.c ./srcs/exec/exec_aux_2.c ./srcs/exec/exec_aux_3.c \
		./srcs/commands/export_aux.c \
		./srcs/parser/parser_aux1.c ./srcs/parser/parser_aux2.c ./srcs/parser/parser_aux3.c \
		./srcs/parser/parser_aux4.c ./srcs/parser/parser_aux5.c ./srcs/parser/parser_aux6.c \
		./srcs/print/replace2.c
NAME = minishell
OBJS = ${SRCS:.c=.o}
CC = clang
CFLAGS = -Wall -Wextra -Werror
SANITIZE = -g3 -fsanitize=address

${NAME}:	${OBJS}
			make -C ./resources/libft/
			gcc ${OBJS} -L ./resources/libft/ -l ft -o ${NAME}
all:		${NAME}
clean:
			rm -f ${OBJS}
			make clean -C ./resources/libft
fclean:		clean
			rm -f ${NAME}
			make fclean -C ./resources/libft
re:			fclean all
.PHONY:		all clean fclean re
