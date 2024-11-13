/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:10:01 by thelaine          #+#    #+#             */
/*   Updated: 2024/08/06 17:10:05 by thelaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_unset_one(t_var *var, char *to_del)
{
	t_env_var	*current_elem;
	t_env_var	*previous_elem;

	current_elem = var->env_var;
	if (!ft_strcmp(current_elem->var_name, to_del))
	{
		var->env_var = current_elem->next;
		free(current_elem->var_name);
		free(current_elem->value);
		return (free(current_elem));
	}
	previous_elem = current_elem;
	current_elem = current_elem->next;
	while (current_elem)
	{
		if (!ft_strcmp(current_elem->var_name, to_del))
		{
			previous_elem->next = current_elem->next;
			free(current_elem->var_name);
			free(current_elem->value);
			return (free(current_elem));
		}
		previous_elem = current_elem;
		current_elem = current_elem->next;
	}
}

void	ft_unset(t_var *var, char **cmds)
{
	int	i;

	i = 1;
	while (cmds[i])
	{
		ft_unset_one(var, cmds[i]);
		i++;
	}
}
