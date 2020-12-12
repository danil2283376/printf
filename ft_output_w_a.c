/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output_w_a.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 14:43:07 by scolen            #+#    #+#             */
/*   Updated: 2020/12/12 12:52:26 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	zeroing_value_struct(t_varible *g_varible)
{
	if (g_varible->accuracy < 0)
	{
		g_varible->exist_accuracy = 0;
	}
}

void	output_width_int(int length_number,
	int number_width, t_varible *g_varible, char c)
{
	int		start;
	char	symbol1;
	int		boolean_zero;
	int		symbol_negative;
	int		boolean;

	start = 0;
	(void)c;
	symbol1 = ' ';
	symbol_negative = 0;
	boolean = 0;
	boolean_zero = zero_exist(g_varible->str);
	symbol_negative = negative_exist(g_varible->str, c);
	if (length_number > number_width)
		return ;
	if (number_width < 0)
		number_width = number_width * (-1);
	if (length_number > number_width)
		return ;
	zeroing_value_struct(g_varible);
	if (boolean_zero == 1 && g_varible->exist_accuracy == 0
		&& symbol_negative == 0 && g_varible->width >= 0)
		symbol1 = '0';
	while (length_number++ < number_width)
		ft_putchar_fd(symbol1, 1, g_varible);
}

void	output_accuracy_int(int length_number,
	int number_accuracy, long number, t_varible *g_v)
{
	if (g_v->accuracy == 0)
		number_accuracy = 0;
	if (number_accuracy < 0)
		number_accuracy = 0;
	if (number < 0)
	{
		number = number * (-1);
		number_accuracy = number_accuracy - 1;
	}
	while (length_number++ < number_accuracy)
		ft_putchar_fd('0', 1, g_v);
}

int		new_width1(int width, int length_number)
{
	if (width < 0)
	{
		width = width * (-1);
		width = width - length_number;
	}
	else
		width = width - length_number;
	return (width);
}
