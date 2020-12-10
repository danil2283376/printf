SRC = $(shell find . -name "ft_*.c")

OBJC = ${SRS:.c=.o}

NAME = libftprintf.a

FLAG = -Wall -Wextra -Werror

OBJC = ${SRC:.c=.o}

GCC = gcc

.c.o:
	${GCC} ${FLAG} -I. -c $< -o ${<:.c=.o}

all: ${NAME}

${NAME}: ${OBJC}
	ar rc ${NAME} ${OBJC}

bonus: all

clean:
	rm -f ${OBJC}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re bonus
