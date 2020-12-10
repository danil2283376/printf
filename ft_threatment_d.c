/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threatment_d.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:02:52 by scolen            #+#    #+#             */
/*   Updated: 2020/12/10 20:35:44 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	continue_thretment_int1(global_varible *g_varible, int new_width, int number)
{
	int boolean;

	boolean = 0;
	if (g_varible->width >= 0)
	{
		if (zero_exist(g_varible->str) && g_varible->exist_accuracy == 0 && number < 0)
		{
			write(1, "-", 1);
			boolean = 1;
		}
		output_width_int(0, new_width, g_varible, 'd');
	}
	if (boolean == 0 && number < 0)
		write(1, "-", 1);
}

static void	continue_thretment_int(global_varible *g_varible, int number, char *number_str)
{
	int length_number;
	int new_len_nbr;
	int start_number;
	int new_width;

	start_number = 0;
	length_number = len_number(number);
	new_len_nbr = g_varible->accuracy - length_number; // 5 - 2 = 3
	if (new_len_nbr < 0)
		new_len_nbr = 0;
	new_len_nbr = new_len_nbr + length_number; // 3 + 2 = 5
	if (number < 0) // если число отрицательное
	{
		new_len_nbr = new_len_nbr + 1;
		start_number = 1;
	}
	new_width = new_width1(g_varible->width, new_len_nbr/*, number*/);
	continue_thretment_int1(g_varible, new_width, number);
	output_accuracy_int(length_number, new_len_nbr, number, g_varible);
	while (number_str[start_number]) // вывод числа по символам
		write(1, &number_str[start_number++], 1);
	if (g_varible->width < 0)
		output_width_int(0, new_width, g_varible, 'd');
}

void	threatment_int(const char *s, va_list *va_args, global_varible *g_varible)
{
	int number_from_args;
	char *number_str;

	g_varible->width = take_width(&s[0]); // ширина
	g_varible->accuracy = take_accuracy(&s[0], g_varible); // точность
	g_varible->str = &s[0]; // передал место с флагом (d)
	substitution_value_width(&s[0], g_varible, va_args, 'd');
	substitution_value_accuracy(&s[0], g_varible, va_args);
	number_from_args = va_arg(*va_args, int); // число из аргумента
	g_varible->number = number_from_args;
	// printf("number_from_args: %d\n", number_from_args);0
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
		number_str = ft_itoa(number_from_args); // число в строке
	continue_thretment_int(g_varible, number_from_args, number_str); // продолжение
	free(number_str);
	zeroing_value(g_varible);
	va_end(*va_args);
}
