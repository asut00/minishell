/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:04:23 by thelaine          #+#    #+#             */
/*   Updated: 2024/07/18 17:04:44 by thelaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_for_env_export(t_env_var *env_var)
{
	if (ft_strcmp("?", env_var->var_name) && ft_strcmp("_", env_var->var_name))
	{
		printf("declare -x ");
		if (env_var->value)
			printf("%s=\"%s\"\n", env_var->var_name, env_var->value);
		else
			printf("%s\n", env_var->var_name);
	}
	env_var->is_printed = 1;
}

static void	print_alphabetical_order(t_env_var *env_var, int len)
	{
	t_env_var	*element;
	t_env_var	*saved_element;
	int			i;

	i = 0;
	while (i < len)
	{
		element = env_var;
		while (element && element->is_printed)
			element = element->next;
		saved_element = element;
		while (element)
		{
			if (!(element->is_printed)
				&& ft_strcmp(element->var_name, saved_element->var_name) < 0)
				saved_element = element;
			element = element->next;
		}
		print_for_env_export(saved_element);
		i++;
	}
}

void	ft_env_export(t_var *var)
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
	env_var = var->env_var;
	print_alphabetical_order(env_var, len);
	while (env_var)
	{
			env_var->is_printed = 0;
			env_var = env_var->next;
	}
}
