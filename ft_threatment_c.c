/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threatment_c.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 19:16:59 by scolen            #+#    #+#             */
/*   Updated: 2020/12/09 19:20:53 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	continue_char(char symbol, global_varible *g_varible)
{
	int length_string;
	// int new_len_nbr;
	int start;
	int new_width;
	// int varible_value;

	// length_number = len_number(number);
	length_string = 1;
	start = 0;
	// length_string = output_accuracy_string(length_string, &symbol, g_varible, 0);
	new_width = new_width1(g_varible->width, length_string/*, number*/);
	if (g_varible->width >= 0)
		output_width_int/*string*/(0, new_width, g_varible, 'c');
	write(1, &symbol, 1);
	g_varible->length++;
	// output_accuracy_string(length_string, s, g_varible, 1);
	if (g_varible->width < 0)
		output_width_int/*string*/(0, new_width, g_varible, 'c');
}

void	threatment_char(const char *s, va_list *va_args, global_varible *g_varible)
{
	char number_from_args;
	int value_is_null;

	value_is_null = 0;
	g_varible->width = take_width(&s[0]); // ширина
	// g_varible->accuracy = take_accuracy(&s[0], g_varible); // точность
	// printf("accuracy: %d", g_varible->accuracy);
	g_varible->str = &s[0]; // передал место с флагом (d)
	substitution_value_width(&s[0], g_varible, va_args, 'c');
	// substitution_value_accuracy(&s[0], g_varible, va_args);
	number_from_args = va_arg(*va_args, int); // строка из аргумента
	// printf("%c", number_from_args);
	// if (number_from_args == NULL)
	// {
	// 	number_from_args = ft_strdup("(null)");
	// 	value_is_null = 1;
	// 	// printf("1%s", number_from_args);
	// }
	// printf("%s", number_from_args);
	continue_char(number_from_args/*, va_args*/, g_varible);
	// if (value_is_null)
	// 	free(number_from_args);
	zeroing_value(g_varible);
	va_end(*va_args);
}
