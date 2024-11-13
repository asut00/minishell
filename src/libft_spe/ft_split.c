/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelaine <theo.helaine@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 10:30:54 by thelaine          #+#    #+#             */
/*   Updated: 2024/06/07 18:55:23 by thelaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_in_charset(char c, char *charset)
{
	int	i;

	i = 0;
	if (!charset)
		return (0);
	while (charset[i])
		if (c == charset[i++])
			return (1);
	return (0);
}

static int	ft_strreallen(char const *s, char *charset)
{
	int	len;

	len = 0;
	while (s[len] && !is_in_charset(s[len], charset))
		len++;
	return (len);
}

static int	count_words(char const *s, char *charset)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s && s[i])
	{
		while (s[i] && is_in_charset(s[i], charset))
			i++;
		if (s[i])
			count++;
		while (s[i] && !is_in_charset(s[i], charset))
			i++;
	}
	return (count);
}

char	**ft_split(char *s, char *charset, t_var *pvar)
{
	int		i;
	int		j;
	int		count;
	char	**splitted;

	i = 0;
	j = 0;
	count = count_words(s, charset);
	splitted = (char **)ft_calloc(count + 1, sizeof(char *), pvar);
	if (!splitted)
		return (0);
	while (i < count)
	{
		while (s[j] && is_in_charset(s[j], charset))
			j++;
		splitted[i] = ft_substr(s, j, ft_strreallen(&s[j], charset), pvar);
		j += ft_strreallen(&s[j], charset);
		i++;
	}
	return (splitted);
}
