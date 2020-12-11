/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threatment_high_x.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 19:30:31 by scolen            #+#    #+#             */
/*   Updated: 2020/12/11 15:16:33 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	hex_continue_h(char *ptr, int count_devision, long number, global_varible *g_varible)
{
	int start;
	int new_len_nbr;
	int new_width;

	start = 0;
	new_len_nbr = g_varible->accuracy - count_devision;
	if (new_len_nbr < 0)
		new_len_nbr = 0;
	new_len_nbr = new_len_nbr + count_devision;
	if (number == 0 && g_varible->flag == 0)
		ptr[0] = '0';
	while (start < count_devision && number > 0)
	{
		ptr[start++] = ft_toupper(value_hex/*_h*/(number % 16));
		number = number / 16;
	}
	new_width = new_width1(g_varible->width, new_len_nbr/*, number*/);
	if (g_varible->width >= 0)
		output_width_int/*hex_h*/(0, new_width, g_varible, 'X');
	output_accuracy_int(count_devision, new_len_nbr, number, g_varible);
	// g_varible->length = g_varible->length + count_devision;
	while (count_devision > 0 && ptr[count_devision - 1])
		ft_putchar_fd(ptr[--count_devision], 1, g_varible);
		// write(1, &ptr[--count_devision], 1);
	if (g_varible->width < 0)
		output_width_int/*hex_h*/(0, new_width, g_varible, 'X');
}

void	threatment_hex_h(const char *s, va_list *va_args, global_varible *g_varible)
{
	long number;
	char *ptr;
	int count_devision;

	g_varible->width = take_width(&s[0]);
	count_devision = 0;
	g_varible->accuracy = take_accuracy(&s[0], g_varible);
	g_varible->str = &s[0];
	substitution_value_width(&s[0], g_varible, va_args, 'X');
	substitution_value_accuracy(&s[0], g_varible, va_args);
	number = va_arg(*va_args, unsigned int);
	if (number == 0 && g_varible->accuracy == 0
		&& g_varible->exist_accuracy == 1)
	{
		ptr = ft_strdup("");
		g_varible->flag = 1;
	}
	else
	{
		count_devision = count_devisions(number);
		ptr = malloc(count_devision * sizeof(char));
	}
	hex_continue_h(ptr, count_devision, number, g_varible);
	zeroing_value(g_varible);
	free(ptr);
}
