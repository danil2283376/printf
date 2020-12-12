/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threatment_c.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 19:16:59 by scolen            #+#    #+#             */
/*   Updated: 2020/12/12 12:54:06 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	continue_char(char symbol, t_varible *g_varible)
{
	int length_string;
	int start;
	int new_width;

	length_string = 1;
	start = 0;
	new_width = new_width1(g_varible->width, length_string);
	if (g_varible->width >= 0)
		output_width_int(0, new_width, g_varible, 'c');
	ft_putchar_fd(symbol, 1, g_varible);
	if (g_varible->width < 0)
		output_width_int(0, new_width, g_varible, 'c');
}

void		threatment_char(const char *s, va_list *va_ar, t_varible *g_v)
{
	char	number_from_args;
	int		value_is_null;

	value_is_null = 0;
	g_v->width = take_width(&s[0]);
	g_v->str = &s[0];
	substitution_value_width(&s[0], g_v, va_ar, 'c');
	number_from_args = va_arg(*va_ar, int);
	continue_char(number_from_args, g_v);
	zeroing_value(g_v);
	va_end(*va_ar);
}
