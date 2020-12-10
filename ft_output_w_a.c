/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output_w_a.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 14:43:07 by scolen            #+#    #+#             */
/*   Updated: 2020/12/10 17:02:31 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	output_width_int(int length_number, int number_width, global_varible *g_varible, char symbol)
{
	int start;
	char symbol1;
	int boolean_zero;
	int symbol_negative;
	int boolean;

	start = 0;
	(void)symbol;
	symbol1 = ' ';
	symbol_negative = 0;
	boolean = 0;
	boolean_zero = zero_exist(g_varible->str);
	symbol_negative = negative_exist(g_varible->str, symbol);
	if (length_number > number_width)
		return ;
	if (number_width < 0)
		number_width = number_width * (-1);
	if (length_number > number_width)
		return ;
	if (boolean_zero == 1 && g_varible->exist_accuracy == 0
		&& symbol_negative == 0)
			symbol1 = '0';
	while (length_number++ < number_width)
		write(1, &symbol1, 1);
}

// длина числа в символах, и число точности, и само число
void	output_accuracy_int(int length_number, int number_accuracy, long number, global_varible *g_varible)
{
	if (g_varible->accuracy == 0)
		number_accuracy = 0;
	if (number_accuracy < 0)
		number_accuracy = 0;
	if (number < 0)
	{
		// if (g_varible->exist_accuracy == 0)
		// if (g_varible->exist_accuracy == 1)
		// if (g_varible->exist_accuracy == 1)
		// if (zero_exist(g_varible->str) == 0)
			// write(1, "-", 1);
		number = number * (-1);
		number_accuracy = number_accuracy - 1;
	}
	while (length_number++ < number_accuracy)
		write(1, "0", 1);
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
