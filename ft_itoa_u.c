/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 15:16:22 by scolen            #+#    #+#             */
/*   Updated: 2020/12/10 13:22:42 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	length_number(long n)
{
	int length_nbr;

	length_nbr = 0;
	while (n > 0)
	{
		n = n / 10;
		length_nbr++;
	}
	return (length_nbr);
}

static char	*convert_to_string(long nbr, int len_n, int nbr_is_negative)
{
	char *ptr;

	ptr = malloc((len_n + 1 + nbr_is_negative) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ptr[len_n + nbr_is_negative] = '\0';
	if (ptr == NULL)
		return (NULL);
	if (!nbr_is_negative)
		len_n--;
	while (nbr != 0)
	{
		ptr[len_n] = (nbr % 10) + '0';
		nbr = nbr / 10;
		len_n--;
	}
	if (nbr_is_negative)
		ptr[0] = '-';
	return (ptr);
}

static char	*convert_zero(void)
{
	char *ptr;

	ptr = malloc(2);
	ptr[0] = '0';
	ptr[1] = '\0';
	return (ptr);
}

char		*ft_itoa_u(unsigned int n)
{
	int		len_n;
	int		nbr_is_negative;
	long	number;

	number = n;
	len_n = 0;
	if (n == 0)
		return (convert_zero());
	if (number < 0)
	{
		nbr_is_negative = 1;
		number = number * (-1);
	}
	else
		nbr_is_negative = 0;
	len_n = length_number(number);
	return (convert_to_string(number, len_n, nbr_is_negative));
}
