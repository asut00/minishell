/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelaine <theo.helaine@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 09:54:41 by thelaine          #+#    #+#             */
/*   Updated: 2024/07/11 16:22:40 by thelaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char *s1, char *s2, t_var *var)
{
	int		len_s1;
	int		len_s2;
	char	*join;

	if (!s2)
		return (s1);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	join = ft_calloc(len_s1 + len_s2 + 1, sizeof(char), var);
	ft_strlcat(join, s1, len_s1 + len_s2 + 1);
	ft_strlcat(join, s2, len_s1 + len_s2 + 1);
	return (ft_free(var, s1), join);
}

char	*ft_strjoin_no_free(char *s1, char *s2, t_var *var)
{
	int		len_s1;
	int		len_s2;
	char	*join;

	if (!s2)
		return (s1);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	join = ft_calloc(len_s1 + len_s2 + 1, sizeof(char), var);
	ft_strlcat(join, s1, len_s1 + len_s2 + 1);
	ft_strlcat(join, s2, len_s1 + len_s2 + 1);
	return (join);
}

static void	*ft_calloc_malloc(size_t nb_elem, size_t size_elem)
{
	void	*tab;
	size_t	i;

	if (size_elem != 0 && nb_elem > ((size_t) - 1 / size_elem))
		return (0);
	i = 0;
	tab = (void *)malloc(nb_elem * size_elem);
	if (!tab)
		return (0);
	while (i < nb_elem * size_elem)
	{
		*(unsigned char *)(tab + i) = 0;
		i++;
	}
	return (tab);
}

char	*ft_strjoin_malloc(char *s1, char *s2)
{
	int		len_s1;
	int		len_s2;
	char	*join;

	if (!s2)
		return (s1);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	join = ft_calloc_malloc(len_s1 + len_s2 + 1, sizeof(char));
	if (!join)
		return (free(s2), NULL);
	ft_strlcat(join, s1, len_s1 + len_s2 + 1);
	ft_strlcat(join, s2, len_s1 + len_s2 + 1);
	return (free(s1), free(s2), join);
}
