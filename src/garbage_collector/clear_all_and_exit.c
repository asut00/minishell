/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_stuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:24:57 by thelaine          #+#    #+#             */
/*   Updated: 2024/07/16 12:25:01 by thelaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <readline/readline.h>
#include <readline/history.h>

static void	ft_clear_env_var(t_var *var)
{
	t_env_var	*current_node;
	t_env_var	*next_node;

	current_node = var->env_var;
	while (current_node)
	{
		next_node = current_node->next;
		free(current_node->var_name);
		free(current_node->value);
		free(current_node);
		current_node = next_node;
	}
	var->env_var = 0;
}

void	clear_all_and_exit(t_var *var, int exitvalue)
{
	ft_clear_env_var(var);
	ft_clear_line_memory(var);
	if (var->saved_stdin != -1)
		close(var->saved_stdin);
	if (var->saved_stdout != -1)
		close(var->saved_stdout);
	ft_cleargarbage(var);
	rl_clear_history();
	exit(exitvalue);
}
