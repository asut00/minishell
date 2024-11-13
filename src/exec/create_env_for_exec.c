/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_for_exec.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:08:55 by thelaine          #+#    #+#             */
/*   Updated: 2024/07/18 12:09:11 by thelaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_var_size(t_var *var)
{
	t_env_var	*env_var;
	int			len;

	len = 0;
	env_var = var->env_var;
	while (env_var)
	{
		len++;
		env_var = env_var->next;
	}
	return (len);
}

void	create_env_for_exec(t_var *var)
{
	int			i;
	t_env_var	*env_var;

	i = 0;
	env_var = var->env_var;
	var->tmp_envp = ft_malloc(env_var_size(var) + 1, sizeof(char *), var);
	while (env_var)
	{
		var->tmp_envp[i] = ft_strdup_spe(env_var->var_name, var);
		var->tmp_envp[i] = ft_strjoin(var->tmp_envp[i], "=", var);
		var->tmp_envp[i] = ft_strjoin(var->tmp_envp[i], env_var->value, var);
		env_var = env_var->next;
		i++;
	}
	var->tmp_envp[i] = 0;
}
