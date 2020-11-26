/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 15:00:02 by scolen            #+#    #+#             */
/*   Updated: 2020/11/26 20:40:04 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

/*
аргументы которые нужно распарсить
*/

typedef struct	args
{
	int index;
	int space;
}				args_struct;

int	len_number(int nbr)
{
	int len_nbr;
	int start;

	len_nbr = 0;
	start = 0;
	while (nbr != 0)
	{
		nbr = nbr / 10;
		start++;
	}
	return (len_nbr);
}

int	value_not_zero(const char *s)
{
	int start;

	start = 0;
	while (s[start] == '0')
		start++;
	return (start);
}

void	treatment_width(const char *s, va_list **arg, args_struct **a_s, int len_w)
{
	long nbr;
	(void)arg;
	(void)a_s;
	int start;
	int boolean;

	start = 0;
	nbr = 0;
	boolean = 0;
	while (s[start] == '0')
	{
		start++;
		boolean = 1;
	}
	nbr = ft_atoi(&s[start]);
	// printf("%d", nbr);
	if (nbr < 0)
		nbr = nbr * (-1);
	if (s[start] == '0' || boolean)
		while (nbr > len_w++)
			write(1, "0", 1);
	else
		while (nbr > len_w++)
			write(1, " ", 1);
}

void	treatment_str(const char *s, va_list **arg, args_struct **a_s)
{
	char *str;
	int start;
	int number;

	str = va_arg(**arg, char *);
	start = 0;
	number = 0;
	while (s[start] != '%' && s[start])
		start--;
	//start = start + value_not_zero(&s[start + 1]);
	//printf("number = %d", start);
	number = ft_atoi(&s[start + 1]);
	if (number >= 0)
		treatment_width(&s[start + 1], arg, a_s, ft_strlen(str));
	(**a_s).index = (**a_s).index - start;
	write(1, str, ft_strlen(str));
	if (number < 0)
		treatment_width(&s[start + 1], arg, a_s, ft_strlen(str));
	va_end(**arg);
}

void	treatment_char(const char *s, va_list **arg, args_struct **a_s)
{
	char c;
	int start;
	(void)arg;
	int number;

	c = va_arg(**arg, int);
	start = 0;
	number = 0;
	while (s[start] != '%' && s[start])
		start--;
	number = ft_atoi(&s[start + 1]);
	if (number >= 0)
		treatment_width(&s[start + 1], arg, a_s, 1);
	(**a_s).index = (**a_s).index - start;
	write(1, &c, 1);
	if (number < 0)
		treatment_width(&s[start + 1], arg, a_s, 1);
	va_end(**arg);
}

void	func_manage(const char *s, va_list *args, args_struct **arg)
{
	int start;

	start = 0;
	// printf("index = %d", (*arg)->index);
	while (s[start])
	{
		if (s[start] == 's')
		{
			treatment_str(&s[start], &args, arg);
			break;
		}
		else if (s[start] == 'c')
		{
			treatment_char(&s[start], &args, arg);
			break;
		}
		start++;
		// else if (s[start] == 'd') // продолжать обрабатывать
	}
}

int	ft_printf(const char *s, ...)
{
	int start;
	va_list va_list;
	args_struct *args;

	start = 0;
	args = malloc(sizeof(args) * 1);
	va_start(va_list, s);
	while (s[start])
	{
		if (s[start] == '%')
		{
			args->index = start;
			func_manage(&s[start + 1], &va_list, &args);
			//printf("new_index = %d\n", args->index);
			start = args->index;
		}
		else
			write(1, &s[start], 1);
		args->index = 0;
		start++;
	}
	va_end(va_list);
	return (0);
}

int main(void)
{
	//ft_printf("hello %d", );
	//int item;
	//char *s = "ehgfndijskml,";
	//item = 1;

	// printf("asd %22s %14ss", s, "\nHELLO DANIL");
	//printf("%03c", 'a');
	ft_printf("Hello %0-6s! %5s %-10c", "Danil", "How are you?", 'A');
	printf("\n\nHello %0-6s! %5s %-10c", "Danil", "How are you?", 'A');
	//printf("");
	return (0);
}
