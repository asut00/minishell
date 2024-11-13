/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_one.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 11:38:45 by thelaine          #+#    #+#             */
/*   Updated: 2024/08/02 11:39:01 by thelaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_or_change(t_env_var *env_var, char *value, int mode)
{
	if (!value)
		return (SUCCESS);
	if (mode == DEFINE)
	{
		free(env_var->value);
		env_var->value = value;
	}
	else if (mode == ADD)
	{
		env_var->value = ft_strjoin_malloc(env_var->value, value);
		if (!env_var->value)
			return (FAILURE);
	}
	return (SUCCESS);
}

static void	check_if_existing(t_var *var, char *var_name, char *value, int mode)
{
	t_env_var	*new_elem;

	new_elem = var->env_var;
	while (new_elem)
	{
		if (!ft_strcmp(new_elem->var_name, var_name))
		{
			free(var_name);
			if (add_or_change(new_elem, value, mode) == FAILURE)
				clear_all_and_exit(var, 1);
			return ;
		}
		new_elem = new_elem->next;
	}
	ft_malloc_env_var(var, var_name, value);
}

void	ft_export_one(t_var *var, char *new_var, int mode)
{
	char	*var_name;
	char	*value;
	char	*srch;

	srch = ft_strchr(new_var, '=');
	if (!srch)
	{
		var_name = ft_substr_malloc(new_var, 0, ft_strlen(new_var));
		if (!var_name)
			clear_all_and_exit(var, 1);
		value = 0;
	}
	else
	{
		if (mode == DEFINE)
			var_name = ft_substr_malloc(new_var, 0, srch - new_var);
		else
			var_name = ft_substr_malloc(new_var, 0, srch - new_var - 1);
		if (!var_name)
			clear_all_and_exit(var, 1);
		value = ft_substr_malloc(srch, 1, ft_strlen(srch));
		if (!value)
			return (free(var_name), clear_all_and_exit(var, 1));
	}
	check_if_existing(var, var_name, value, mode);
}
