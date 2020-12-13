SRC = ft_atoi.c ft_continue_procent.c ft_itoa_u.c ft_itoa.c ft_output_w_a.c \
	ft_pars.c ft_printf.c ft_putchar_fd.c ft_strdup.c ft_strlen.c ft_threatment_c.c \
	ft_threatment_d.c ft_threatment_high_x.c ft_threatment_i.c ft_threatment_p.c \
	ft_threatment_procent.c ft_threatment_star.c ft_threatment_str.c \
	ft_threatment_unsigned.c ft_threatment_x.c ft_toupper.c

OBJC = ${SRS:.c=.o}

NAME = libftprintf.a

FLAG = -Wall -Wextra -Werror

OBJC = ${SRC:.c=.o}

GCC = gcc

.c.o:
	${GCC} ${FLAG} -I. -c $< -o ${<:.c=.o}

all: ${NAME}

${NAME}: ${OBJC} libftprintf.h
	ar rc ${NAME} ${OBJC}

bonus: all

clean:
	rm -f ${OBJC}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re bonus
