/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threatment_high_x.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 19:30:31 by scolen            #+#    #+#             */
/*   Updated: 2020/12/09 19:38:30 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	value_hex_h(int symbol)
// {
// 	char return_char;
// 	return_char = '0';
// 	if (symbol >= 0 && symbol <= 9)
// 		return_char = symbol + '0';
// 	else if (symbol == 10)
// 		return_char = 'A';
// 	else if (symbol == 11)
// 		return_char = 'B';
// 	else if (symbol == 12)
// 		return_char = 'C';
// 	else if (symbol == 13)
// 		return_char = 'D';
// 	else if (symbol == 14)
// 		return_char = 'E';
// 	else if (symbol == 15)
// 		return_char = 'F';
// 	return (return_char);
// }

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
	while (start < count_devision && number > 0)
	{
		ptr[start] = ft_toupper(value_hex/*_h*/(number % 16));
		number = number / 16;
		start++;
	}
	new_width = new_width1(g_varible->width, new_len_nbr/*, number*/);
	if (g_varible->width >= 0)
		output_width_int/*hex_h*/(0, new_width, g_varible, 'X');
	output_accuracy_int(count_devision, new_len_nbr, number, g_varible->accuracy);
	g_varible->length = g_varible->length + count_devision;
	while (count_devision > 0 && ptr[count_devision - 1])
		write(1, &ptr[--count_devision], 1);
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
	// printf("exist_accuracy: %d\n", g_varible->exist_accuracy);
	g_varible->str = &s[0];
	substitution_value_width(&s[0], g_varible, va_args, 'X');
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
	hex_continue_h(ptr, count_devision, number, g_varible);
	zeroing_value(g_varible);
	free(ptr);
}
