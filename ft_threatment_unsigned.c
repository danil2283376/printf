/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threatment_unsigned.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 16:58:05 by scolen            #+#    #+#             */
/*   Updated: 2020/12/12 12:55:13 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	continue_thretment_unsigned(t_varible *g_varible,
	long number, char *number_str)
{
	int length_number;
	int new_len_nbr;
	int start_number;
	int new_width;

	length_number = len_number(number);
	new_len_nbr = g_varible->accuracy - length_number;
	if (new_len_nbr < 0)
		new_len_nbr = 0;
	new_len_nbr = new_len_nbr + length_number;
	start_number = 0;
	if (number < 0)
	{
		new_len_nbr = new_len_nbr + 1;
		start_number = 1;
	}
	new_width = new_width1(g_varible->width, new_len_nbr);
	if (g_varible->width >= 0)
		output_width_int(0, new_width, g_varible, 'u');
	output_accuracy_int(length_number, new_len_nbr, number, g_varible);
	while (number_str[start_number])
		ft_putchar_fd(number_str[start_number++], 1, g_varible);
	if (g_varible->width < 0)
		output_width_int(0, new_width, g_varible, 'u');
}

void		threatment_unsigned(const char *s,
	va_list *va_args, t_varible *g_varible)
{
	unsigned int	number_from_args;
	char			*number_str;

	g_varible->width = take_width(&s[0]);
	g_varible->accuracy = take_accuracy(&s[0], g_varible);
	g_varible->str = &s[0];
	substitution_value_width(&s[0], g_varible, va_args, 'u');
	substitution_value_accuracy(&s[0], g_varible, va_args);
	number_from_args = va_arg(*va_args, unsigned int);
	if (number_from_args == 0
		&& g_varible->accuracy == 0 && g_varible->exist_accuracy != 0)
	{
		number_str = ft_strdup("");
		if (g_varible->width >= 0)
			g_varible->width = g_varible->width + 1;
		else
			g_varible->width = g_varible->width - 1;
	}
	else
		number_str = ft_itoa_u(number_from_args);
	continue_thretment_unsigned(g_varible, number_from_args, number_str);
	free(number_str);
	zeroing_value(g_varible);
	va_end(*va_args);
}
