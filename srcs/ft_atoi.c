/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 01:58:05 by hlesny            #+#    #+#             */
/*   Updated: 2023/03/22 03:29:00 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_strchr_b(const char *s, char c)
{
	size_t	i;

	i = 0;
	if (c == '\0')
		return (-1);
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

static int	is_whitespace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\f'
		|| c == '\r');
}

long long	ft_atoi(const char *nptr, int *j)
{
	int			i;
	int			neg;
	long long	number;

	i = 0;
	if (j)
		i = *j;
	neg = 1;
	number = 0;
	while (nptr[i] && is_whitespace(nptr[i]))
		i++;
	if (nptr[i] && (nptr[i] == '-' || nptr[i] == '+'))
	{
		if (nptr[i] == '-')
			neg = -neg;
		i++;
	}
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9')
		&& number <= __INT_MAX__)
		number = number * 10 + (nptr[i++] - 48);
	if (j)
		*j = i;
	return (neg * number);
}

unsigned int	atoi_base(const char *s)
{
	int				i;
	unsigned int	number;

	i = 0;
	number = 0;
	while (s[i] && is_whitespace(s[i]))
		i++;
	if (s[i] && s[i] == '-')
		return (-1);
	if (s[i] && s[i] == '+')
		i++;
	i += 2;
	while (s[i] && ((s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'f')
			|| (s[i] >= 'A' && s[i] <= 'F')))
	{
		number = number * 16 + ft_strchr_b("0123456789ABCDEF", s[i]);
		i++;
	}
	return (number);
}
