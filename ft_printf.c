/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 09:22:52 by scolen            #+#    #+#             */
/*   Updated: 2020/12/10 21:05:32 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

void	standart_value(global_varible *g_varible)
{
	g_varible->index_main_str = 0;
	g_varible->length = 0;
	g_varible->accuracy = -1;
	g_varible->exist_accuracy = -1;
	g_varible->width = 0;
	g_varible->zero_exist = -1;
	g_varible->start = 0;
	g_varible->flag = 0;
}

static int		manage_fuction1(const char *s, global_varible *g_varible, va_list *va_args)
{
	if (s[g_varible->start] == 'x')
	{
		threatment_hex(&s[g_varible->start], va_args, g_varible);
		return (1);
	}
	else if (s[g_varible->start] == 'X')
	{
		threatment_hex_h(&s[g_varible->start], va_args, g_varible);
		return (1);
	}
	else if (s[g_varible->start] == 'p')
	{
		threatment_p(&s[g_varible->start], va_args, g_varible);
		return (1);
	}
	else if (s[g_varible->start + 1] == '%')
	{
		g_varible->start++;
		threatment_procent(&s[g_varible->start], va_args, g_varible);
		return (1);
	}
	return (0);
}

static int		manage_fuction2(const char *s, global_varible *g_varible, va_list *va_args)
{
	if (s[g_varible->start] == 'i')
	{
		threatment_int(&s[g_varible->start], va_args, g_varible);
		return (1);
	}
	else if (s[g_varible->start] == 's')
	{
		threatment_string(&s[g_varible->start], va_args, g_varible);
		return (1);
	}
	else if (s[g_varible->start] == 'c')
	{
		threatment_char(&s[g_varible->start], va_args, g_varible);
		return (1);
	}
	return (0);
}

static void	manage_fuction(const char *s, global_varible *g_varible, va_list *va_args)
{
	g_varible->start = 0;
	while (s[g_varible->start])
	{
		if (s[g_varible->start] == 'd')
		{
			threatment_int(&s[g_varible->start], va_args, g_varible);
			break ;
		}
		else if (s[g_varible->start] == 'u')
		{
			threatment_unsigned(&s[g_varible->start], va_args, g_varible);
			break ;
		}
		else if (manage_fuction2(s, g_varible, va_args))
			break ;
		else if (manage_fuction1(s, g_varible, va_args))
			break ;
		g_varible->start++;
	}
	(*g_varible).index_main_str = (*g_varible).index_main_str + g_varible->start;
	g_varible->start = 0;
}

static int		free_struct(global_varible *g_varible, va_list *va_args)
{
	free(g_varible);
	va_end(*va_args);
	return (-1);
}

int		ft_printf(const char *s, ...)
{
	int start;
	global_varible *g_varible;
	va_list va_args;

	start = 0;
	va_start(va_args, s);
	g_varible = malloc(sizeof(global_varible) * 1);
	if (g_varible == NULL)
		return (free_struct(g_varible, &va_args));
	g_varible->length = 0;
	standart_value(g_varible);
	// printf("index_main_str: %d\n", g_varible->index_main_str);
	// printf("length: %d\n", g_varible->length);
	// printf("accuracy: %d\n", g_varible->accuracy);
	// printf("exist_accuracy: %d\n", g_varible->exist_accuracy);
	// printf("width: %d\n", g_varible->width);
	// printf("zero_exist: %d\n", g_varible->zero_exist);
	// printf("start: %d\n", g_varible->start);
	while (s[start])
	{
		if (s[start] == '%')
		{
			// standart_value(g_varible);
			g_varible->index_main_str = start; // присваиваю глобальному индексу, где остановился
			manage_fuction(&s[start], g_varible, &va_args); // обработчик флагов
			start = g_varible->index_main_str; // передвигаю индекс вперед
			g_varible->accuracy = 0;
		}
		else
			write(1, &s[start], 1);
		start++;
		g_varible->length++;
	}
	free_struct(g_varible, &va_args);
	va_end(va_args);
	return (0);
}

int main()
{
	// printf("%.0X\n", 0);
	ft_printf("%.0X", 0);
}
