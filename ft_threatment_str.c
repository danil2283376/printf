/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threatment_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 17:55:45 by scolen            #+#    #+#             */
/*   Updated: 2020/12/09 19:17:34 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	output_accuracy_string(int end, char *s, global_varible *g_varible, int boolean)
{
	int start;
	int length_string;

	start = 0;
	length_string = ft_strlen(s);
	if (boolean)
	{
		while (start < end)
			write(1, &s[start++], 1);
		g_varible->length = g_varible->length + start;
	}
	else
	{
		if (g_varible->accuracy <= length_string && g_varible->exist_accuracy)
		{
			// printf("1234");
			length_string = g_varible->accuracy;
		}
	}
	return (length_string);
}

static void	continue_string(char *s/*, va_list *va_args*/, global_varible *g_varible)
{
	int length_string;
	// int new_len_nbr;
	int start;
	int new_width;
	// int varible_value;

	// length_number = len_number(number);
	length_string = ft_strlen(s);
	start = 0;
	length_string = output_accuracy_string(length_string, s, g_varible, 0);
	new_width = new_width1(g_varible->width, length_string/*, number*/);
	if (g_varible->width >= 0)
		output_width_int/*string*/(0, new_width, g_varible, 's');
	output_accuracy_string(length_string, s, g_varible, 1);
	if (g_varible->width < 0)
		output_width_int/*string*/(0, new_width, g_varible, 's');
}

void	threatment_string(const char *s, va_list *va_args, global_varible *g_varible)
{
	//смысл один и тот же просто выводить строку
	//и при точности обрезать строку
	char *number_from_args;
	int value_is_null;

	value_is_null = 0;
	g_varible->width = take_width(&s[0]); // ширина
	g_varible->accuracy = take_accuracy(&s[0], g_varible); // точность
	// printf("accuracy: %d", g_varible->accuracy);
	g_varible->str = &s[0]; // передал место с флагом (d)
	substitution_value_width(&s[0], g_varible, va_args, 's');
	substitution_value_accuracy(&s[0], g_varible, va_args);
	number_from_args = va_arg(*va_args, char *); // строка из аргумента
	if (number_from_args == NULL)
	{
		number_from_args = ft_strdup("(null)");
		value_is_null = 1;
		// printf("1%s", number_from_args);
	}
	// printf("%s", number_from_args);
	continue_string(number_from_args/*, va_args*/, g_varible);
	if (value_is_null)
		free(number_from_args);
	zeroing_value(g_varible);
	va_end(*va_args);
}
