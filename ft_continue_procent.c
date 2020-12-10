/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_continue_procent.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 19:45:21 by scolen            #+#    #+#             */
/*   Updated: 2020/12/10 13:22:39 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		negative_exist_procent(const char *str, char symbol)
{
	int start;
	int symbol_negative;

	start = 0;
	symbol_negative = 0;
	while (str[start - 1] != '%')
		start--;
	while (str[start] != '-' && str[start] != '.' && str[start] != symbol)
		start++;
	if (str[start] == '-')
		return (1);
	return (0);
}

int		take_width_procent(const char *s)
{
	int start;
	int number;
	int value_zero;

	start = 0;
	number = 0;
	value_zero = 0;
	while (s[start - 1] != '%' && s[start - 1])
		start--;
	while (s[start] == '0')
	{
		value_zero = 1;
		start++;
	}
	number = ft_atoi(&s[start]);
	return (number);
}
