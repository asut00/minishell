/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <asuteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 07:47:56 by asuteau           #+#    #+#             */
/*   Updated: 2024/05/24 16:58:23 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	ft_atoll(const char *str)
{
	long long	res;
	long long	sign;
	long long	sign_count;

	res = 0;
	sign = 1;
	sign_count = 0;
	while (*str && (*str == 32 || (9 <= *str && *str <= 13)))
		str++;
	while (*str && (*str == '+' || *str == '-'))
	{
		if (*str == '-')
			sign = sign * -1;
		sign_count++;
		str++;
	}
	if (sign_count > 1)
		return (0);
	while (*str && '0' <= *str && *str <= '9')
		res = res * 10 + (*str++ - '0');
	return (res * sign);
}

t_ull	ft_atoull(const char *str)
{
	unsigned long long	res;
	unsigned long long	sign;
	long long			sign_count;

	res = 0;
	sign = 1;
	sign_count = 0;
	while (*str && (*str == 32 || (9 <= *str && *str <= 13)))
		str++;
	while (*str && (*str == '+' || *str == '-'))
	{
		if (*str == '-')
			sign = sign * -1;
		sign_count++;
		str++;
	}
	if (sign_count > 1)
		return (0);
	while (*str && '0' <= *str && *str <= '9')
		res = res * 10 + (*str++ - '0');
	return (res * sign);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;
	int	sign_count;

	res = 0;
	sign = 1;
	sign_count = 0;
	while (*str && (*str == 32 || (9 <= *str && *str <= 13)))
		str++;
	while (*str && (*str == '+' || *str == '-'))
	{
		if (*str == '-')
			sign = sign * -1;
		sign_count++;
		str++;
	}
	if (sign_count > 1)
		return (0);
	while (*str && '0' <= *str && *str <= '9')
		res = res * 10 + (*str++ - '0');
	return (res * sign);
}
