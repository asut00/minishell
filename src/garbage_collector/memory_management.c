/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:23:12 by thelaine          #+#    #+#             */
/*   Updated: 2024/07/11 18:35:29 by thelaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_malloc(int len, int size, t_var *pvar)
{
	void		*ptr;
	t_garbage	*garbage;

	ptr = malloc(len * size);
	if (!ptr)
		clear_all_and_exit(pvar, 1);
	garbage = ft_garbagenew(ptr);
	if (!(garbage))
		clear_all_and_exit(pvar, 1);
	garbage->next = pvar->garbage_collector;
	pvar->garbage_collector = garbage;
	return (ptr);
}

void	ft_malloc_env_var(t_var *pvar, char *var_name, char *value)
{
	t_env_var	*env_var;

	env_var = malloc(sizeof(t_env_var));
	if (!env_var)
	{
		free(var_name);
		if (value)
			free(value);
		clear_all_and_exit(pvar, 1);
	}
	env_var->var_name = var_name;
	env_var->value = value;
	env_var->is_printed = 0;
	env_var->next = pvar->env_var;
	pvar->env_var = env_var;
}

void	ft_free(t_var *var, void *content_to_find)
{
	t_garbage	*current_elem;
	t_garbage	*previous_elem;

	if (content_to_find == 0)
		return ;
	current_elem = var->garbage_collector;
	if (current_elem->content == content_to_find)
	{
		var->garbage_collector = current_elem->next;
		return (free(current_elem->content), free(current_elem));
	}
	previous_elem = current_elem;
	current_elem = current_elem->next;
	while (current_elem)
	{
		if (current_elem->content == content_to_find)
		{
			previous_elem->next = current_elem->next;
			return (free(current_elem->content), free(current_elem));
		}
		previous_elem = current_elem;
		current_elem = current_elem->next;
	}
}
