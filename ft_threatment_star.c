/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threatment_star.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 15:18:56 by scolen            #+#    #+#             */
/*   Updated: 2020/12/12 12:54:58 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	zeroing_value(t_varible *g_varible)
{
	g_varible->accuracy = 0;
	g_varible->exist_accuracy = 1;
	g_varible->width = 0;
	g_varible->zero_exist = 0;
}

void	substitution_value_width(const char *s,
	t_varible *g_varible, va_list *va_args, char symbol)
{
	int	start;
	int	number_negative;

	start = 0;
	number_negative = 0;
	while (s[start] != '%')
		start--;
	while (s[start] != '-' && s[start] != '*'
		&& s[start] != symbol && s[start] != '.')
		start++;
	if (s[start] == '-')
	{
		number_negative = 1;
		start++;
	}
	while (s[start] != '*' && s[start] != symbol && s[start] != '.')
		start++;
	if (s[start] == '*')
	{
		g_varible->width = va_arg(*va_args, int);
		if (number_negative == 1 && g_varible->width > 0)
			g_varible->width = g_varible->width * (-1);
	}
	va_end(*va_args);
}

void	substitution_value_accuracy(const char *s,
	t_varible *g_varible, va_list *va_args)
{
	int start;

	start = 0;
	while (s[start] != '.' && s[start] != '%')
		start--;
	if (s[start] != '.')
		return ;
	else
	{
		if (s[start + 1] == '*')
			g_varible->accuracy = va_arg(*va_args, int);
	}
	va_end(*va_args);
}
