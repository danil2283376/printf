/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threatment_d.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:02:52 by scolen            #+#    #+#             */
/*   Updated: 2020/12/12 12:54:14 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	con_th_int1(t_varible *g_v, int new_width, int number)
{
	int boolean;

	boolean = 0;
	if (g_v->accuracy < 0)
		g_v->exist_accuracy = 0;
	if (g_v->width >= 0)
	{
		if (zero_exist(g_v->str) && g_v->exist_accuracy == 0 && number < 0)
		{
			ft_putchar_fd('-', 1, g_v);
			boolean = 1;
		}
		output_width_int(0, new_width, g_v, 'd');
	}
	if (boolean == 0 && number < 0)
		ft_putchar_fd('-', 1, g_v);
}

static void	continue_thretment_int(t_varible *g_varible,
	int number, char *n_s)
{
	int length_number;
	int new_len_nbr;
	int start_number;
	int new_width;

	start_number = 0;
	length_number = len_number(number);
	new_len_nbr = g_varible->accuracy - length_number;
	if (new_len_nbr < 0)
		new_len_nbr = 0;
	new_len_nbr = new_len_nbr + length_number;
	if (number < 0)
	{
		new_len_nbr = new_len_nbr + 1;
		start_number = 1;
	}
	new_width = new_width1(g_varible->width, new_len_nbr);
	con_th_int1(g_varible, new_width, number);
	output_accuracy_int(length_number, new_len_nbr, number, g_varible);
	while (n_s[start_number])
		ft_putchar_fd(n_s[start_number++], 1, g_varible);
	if (g_varible->width < 0)
		output_width_int(0, new_width, g_varible, 'd');
}

void		threatment_int(const char *s,
	va_list *va_args, t_varible *g_varible)
{
	int		number_from_args;
	char	*number_str;

	g_varible->width = take_width(&s[0]);
	g_varible->accuracy = take_accuracy(&s[0], g_varible);
	g_varible->str = &s[0];
	substitution_value_width(&s[0], g_varible, va_args, 'd');
	substitution_value_accuracy(&s[0], g_varible, va_args);
	number_from_args = va_arg(*va_args, int);
	g_varible->number = number_from_args;
	if (number_from_args == 0 && g_varible->accuracy == 0
		&& g_varible->exist_accuracy != 0)
	{
		number_str = ft_strdup("");
		if (g_varible->width >= 0)
			g_varible->width = g_varible->width + 1;
		else
			g_varible->width = g_varible->width - 1;
	}
	else
		number_str = ft_itoa(number_from_args);
	continue_thretment_int(g_varible, number_from_args, number_str);
	free(number_str);
	zeroing_value(g_varible);
}
