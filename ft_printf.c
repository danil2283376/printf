/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 09:22:52 by scolen            #+#    #+#             */
/*   Updated: 2020/12/13 17:00:48 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void			standart_value(t_varible *g_varible)
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

static int		m_f1(const char *s, t_varible *g_varible, va_list *va_args)
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

static int		m_f2(const char *s, t_varible *g_varible, va_list *va_args)
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

static void		m_f(const char *s, t_varible *g_v, va_list *va_args)
{
	g_v->start = 0;
	while (s[g_v->start])
	{
		if (s[g_v->start] == 'd')
		{
			threatment_int(&s[g_v->start], va_args, g_v);
			break ;
		}
		else if (s[g_v->start] == 'u')
		{
			threatment_unsigned(&s[g_v->start], va_args, g_v);
			break ;
		}
		else if (m_f2(s, g_v, va_args))
			break ;
		else if (m_f1(s, g_v, va_args))
			break ;
		g_v->start++;
	}
	(*g_v).index_main_str = (*g_v).index_main_str + g_v->start;
	g_v->start = 0;
}

int				ft_printf(const char *s, ...)
{
	int				start;
	t_varible		g_varible;
	va_list			va_args;

	start = 0;
	va_start(va_args, s);
	g_varible.length = 0;
	standart_value(&g_varible);
	while (s[start])
	{
		if (s[start] == '%')
		{
			g_varible.index_main_str = start;
			m_f(&s[start], &g_varible, &va_args);
			start = g_varible.index_main_str;
			g_varible.accuracy = 0;
		}
		else
			ft_putchar_fd(s[start], 1, &g_varible);
		start++;
	}
	va_end(va_args);
	return (g_varible.length);
}
