/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelaine <theo.helaine@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:23:47 by thelaine          #+#    #+#             */
/*   Updated: 2024/07/11 16:22:56 by thelaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	len_dest;
	size_t	len_src;
	size_t	i;

	len_dest = ft_strlen(dest);
	len_src = ft_strlen(src);
	if (len_dest >= n)
		return (n + len_src);
	i = 0;
	while (src[i] && i < n - len_dest - 1)
	{
		dest[len_dest + i] = src[i];
		i++;
	}
	if (i == n - len_dest - 1)
		dest[len_dest + i] = 0;
	else
		dest[len_dest + len_src] = 0;
	return (len_dest + len_src);
}
