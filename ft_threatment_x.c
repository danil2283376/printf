/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threatment_x.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 19:22:22 by scolen            #+#    #+#             */
/*   Updated: 2020/12/09 19:28:48 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		count_devisions(long number)
{
	int quantity_devision;
	long duplicate;

	duplicate = number;
	quantity_devision = 1;
	// printf("%d\n", quantity_devision);
	while (duplicate > 15)
	{
		quantity_devision++;
		duplicate = duplicate / 16;
	}
	return (quantity_devision);
}

char	value_hex(int symbol)
{
	char return_char;
	return_char = '0';
	if (symbol >= 0 && symbol <= 9)
		return_char = symbol + '0';
	else if (symbol == 10)
		return_char = 'a';
	else if (symbol == 11)
		return_char = 'b';
	else if (symbol == 12)
		return_char = 'c';
	else if (symbol == 13)
		return_char = 'd';
	else if (symbol == 14)
		return_char = 'e';
	else if (symbol == 15)
		return_char = 'f';
	return (return_char);
}

static void	hex_continue(char *ptr, int count_devision, long number, global_varible *g_varible)
{
	int start;
	int new_len_nbr;
	int new_width;

	start = 0;
	new_len_nbr = g_varible->accuracy - count_devision;
	if (new_len_nbr < 0)
		new_len_nbr = 0;
	new_len_nbr = new_len_nbr + count_devision;
	while (start < count_devision && number > 0)
	{
		ptr[start] = value_hex(number % 16);
		number = number / 16;
		start++;
	}
	new_width = new_width1(g_varible->width, new_len_nbr/*, number*/);
	if (g_varible->width >= 0)
		output_width_int/*hex*/(0, new_width, g_varible, 'x');
	output_accuracy_int(count_devision, new_len_nbr, number, g_varible->accuracy);
	g_varible->length = g_varible->length + count_devision;
	while (count_devision > 0 && ptr[count_devision - 1])
		write(1, &ptr[--count_devision], 1);
	if (g_varible->width < 0)
		output_width_int/*hex*/(0, new_width, g_varible, 'x');
}

void	threatment_hex(const char *s, va_list *va_args, global_varible *g_varible)
{
	long number;
	char *ptr;
	int count_devision;

	g_varible->width = take_width(&s[0]);
	g_varible->accuracy = take_accuracy(&s[0], g_varible);
	g_varible->str = &s[0];
	count_devision = 1;
	substitution_value_width(&s[0], g_varible, va_args, 'x');
	substitution_value_accuracy(&s[0], g_varible, va_args);
	number = va_arg(*va_args, unsigned int);
	if (number == 0 && g_varible->accuracy == 0)
	{
		ptr = ft_strdup("");
		if (g_varible->width >= 0)
			g_varible->width = g_varible->width + 1;
		else
			g_varible->width = g_varible->width - 1;
	}
	else
	{
		count_devision = count_devisions(number);
		ptr = malloc(count_devision * sizeof(char));
	}
	hex_continue(ptr, count_devision, number, g_varible);
	zeroing_value(g_varible);
	free(ptr);
}