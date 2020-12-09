/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other_f.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 14:25:25 by scolen            #+#    #+#             */
/*   Updated: 2020/12/09 14:32:37 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	len_number(long nbr)
{
	int len_nbr;
	int start;

	len_nbr = 0;
	start = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
		nbr = nbr * (-1);
	while (nbr != 0)
	{
		nbr = nbr / 10;
		len_nbr++;
	}
	return (len_nbr);
}

int		take_width(const char *s)
{
	int start;
	int number;
	int value_zero;

	start = 0;
	number = 0;
	value_zero = 0;
	while (s[start] != '%' && s[start])
		start--;
	while (s[start + 1] == '0')
	{
		value_zero = 1;
		start++;
	}
	number = ft_atoi(&s[start + 1]);
	// if (value_zero = 1 && va_args->accuracy == 0)
	// printf("\nnumber: %d\n", number);
	return (number);
}

int		take_accuracy(const char *s, global_varible *g_varible/*, va_list *va_args, */)
{
	int start;
	int number_accuracy;

	start = 0;
	number_accuracy = 0;
	while (s[start] != '.' && s[start] != '%' && s[start])
		start--;
	if (s[start] != '.')
	{
		// printf("exist_accuracy: %d", g_varible->exist_accuracy);
		g_varible->exist_accuracy = 0;
		return (0);
	}
	number_accuracy = ft_atoi(&s[start + 1]);
	if (number_accuracy < 0)
		return (0);
	//printf("%d", number_accuracy);
	return (number_accuracy);
}

int		zero_exist(const char *str)
{
	int start;

	start = 0;
	while (str[start] != '%')
		start--;
	if (str[start + 1] == '0')
		return (1);
	return (0);
}

int		negative_exist(const char *str, char symbol)
{
	int start;
	int symbol_negative;

	start = 0;
	symbol_negative = 0;
	while (str[start] != '%')
		start--;
	while (str[start] != '-' && str[start] != '.' && str[start] != symbol)
		start++;
	if (str[start] == '-')
		return (1);
	return (0);
}

// void	zeroing_value(global_varible *g_varible)
// {
// 	g_varible->accuracy = 0;
// 	g_varible->exist_accuracy = 1;
// 	g_varible->width = 0;
// 	g_varible->zero_exist = 0;
// }