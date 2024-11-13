/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelaine <theo.helaine@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 09:40:44 by thelaine          #+#    #+#             */
/*   Updated: 2024/07/11 16:23:19 by thelaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char *str, unsigned int start, size_t len, t_var *var)
{
	size_t	len_dest;
	char	*substr;

	if (start >= ft_strlen(str))
		len_dest = 0;
	else
		len_dest = ft_strlen(str + start);
	if (len_dest > len)
		len_dest = len;
	substr = ft_calloc(len_dest + 1, sizeof(char), var);
	if (!substr)
		return (0);
	if (len_dest == 0)
		ft_strlcpy(substr, str, len_dest + 1);
	else
		ft_strlcpy(substr, str + start, len_dest + 1);
	return (substr);
}

char	*ft_substr_malloc(char *str, unsigned int start, size_t len)
{
	size_t	len_dest;
	char	*substr;

	if (start >= ft_strlen(str))
		len_dest = 0;
	else
		len_dest = ft_strlen(str + start);
	if (len_dest > len)
		len_dest = len;
	substr = malloc(len_dest + 2 * sizeof(char));
	if (!substr)
		return (0);
	if (len_dest == 0)
		ft_strlcpy(substr, str, len_dest + 1);
	else
		ft_strlcpy(substr, str + start, len_dest + 1);
	substr[len_dest + 1] = 0;
	return (substr);
}
