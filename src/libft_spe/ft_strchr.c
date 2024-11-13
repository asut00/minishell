/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelaine <theo.helaine@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:48:27 by thelaine          #+#    #+#             */
/*   Updated: 2024/07/11 16:22:01 by thelaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr(const char *str, int val)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)val)
			return ((char *)&str[i]);
		i++;
	}
	if ((char)val == 0)
		return ((char *)&str[i]);
	return (0);
}
