/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisnumber.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:54:33 by asuteau           #+#    #+#             */
/*   Updated: 2024/07/17 17:54:35 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strisnumber_spe(char *s)
{
	if (!s)
		return (0);
	while (*s == ' ')
		s++;
	if (*s == '-' || *s == '+')
		s++;
	if (*s == '\0')
		return (0);
	while (*s && *s != ' ')
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	while (*s == ' ')
		s++;
	if (*s == '\0')
		return (1);
	return (0);
}
