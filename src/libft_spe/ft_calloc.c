/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelaine <theo.helaine@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:15:52 by thelaine          #+#    #+#             */
/*   Updated: 2024/07/11 16:21:36 by thelaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_calloc(size_t nb_elem, size_t size_elem, t_var *var)
{
	void	*tab;
	size_t	i;

	if (size_elem != 0 && nb_elem > ((size_t) -1 / size_elem))
		return (0);
	i = 0;
	tab = (void *)ft_malloc(nb_elem, size_elem, var);
	if (!tab)
		return (0);
	while (i < nb_elem * size_elem)
	{
		*(unsigned char *)(tab + i) = 0;
		i++;
	}
	return (tab);
}
