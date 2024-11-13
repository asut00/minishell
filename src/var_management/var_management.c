/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:39:56 by thelaine          #+#    #+#             */
/*   Updated: 2024/07/11 18:35:46 by thelaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**create_env_for_var_init(t_var *var, char **env, int len)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = ft_malloc(len + 3, sizeof(char *), var);
	new_env[0] = ft_malloc(1, sizeof(char), var);
	new_env[0][0] = '\0';
	while (env[i])
	{
		new_env[i + 1] = ft_strdup_spe(env[i], var);
		i++;
	}
	new_env[i + 1] = 0;
	return (new_env);
}

void	var_init(t_var *var, char **env)
{
	int		len;
	char	**new_env;

	len = 0;
	while (env[len])
		len++;
	new_env = create_env_for_var_init(var, env, len);
	ft_export(var, new_env);
	len = 0;
	while (new_env[len])
	{
		ft_free(var, new_env[len]);
		len++;
	}
	ft_free(var, new_env);
	ft_change_env_var(var, "?", "0");
}

char	*ft_getenv(t_var *var, char *to_get)
{
	t_env_var	*elem;

	elem = var->env_var;
	while (elem)
	{
		if (!ft_strcmp(elem->var_name, to_get))
			return (elem->value);
		elem = elem->next;
	}
	return (0);
}

void	ft_env(t_var *var, char **cmds)
{
	t_env_var	*env_var;

	if (cmds[1])
	{
		ft_putstr_fd("env takes no arguments in minishell\n", 2);
		return ;
	}
	env_var = var->env_var;
	while (env_var)
	{
		if (env_var->value && ft_strcmp("?", env_var->var_name))
			printf("%s=%s\n", env_var->var_name, env_var->value);
		env_var = env_var->next;
	}
}

void	ft_change_env_var(t_var *pvar, char *var_name, char *value)
{
	int		new_var_len;
	char	**format_for_export;

	format_for_export = ft_malloc(3, sizeof(char *), pvar);
	format_for_export[0] = ft_malloc(1, sizeof(char), pvar);
	format_for_export[0][0] = '\0';
	new_var_len = ft_strlen(var_name) + ft_strlen("=") + ft_strlen(value) + 1;
	format_for_export[1] = ft_malloc(new_var_len, sizeof(char), pvar);
	format_for_export[1][0] = '\0';
	ft_strcat(format_for_export[1], var_name);
	ft_strcat(format_for_export[1], "=");
	ft_strcat(format_for_export[1], value);
	format_for_export[2] = 0;
	ft_export(pvar, format_for_export);
	ft_free(pvar, format_for_export[0]);
	ft_free(pvar, format_for_export[1]);
	ft_free(pvar, format_for_export);
}
