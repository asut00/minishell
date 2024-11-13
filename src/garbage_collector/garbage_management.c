/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:47:46 by thelaine          #+#    #+#             */
/*   Updated: 2024/07/16 16:00:51 by thelaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_sig;

t_garbage	*ft_garbagenew(void *content)
{
	t_garbage	*new_elem;

	new_elem = (t_garbage *)malloc(sizeof(t_garbage));
	if (!new_elem)
		return (free(content), NULL);
	new_elem->content = content;
	new_elem->next = 0;
	return (new_elem);
}

static void	clear_tmp_files(t_var *var)
{
	int	i;

	if (var->heredocs == 0)
		return ;
	i = 0;
	while (var->heredocs[i])
	{
		unlink(var->heredocs[i]);
		i++;
	}
}

static void	clear_var(t_var *var)
{
	var->commands = 0;
	var->garbage_collector = 0;
	var->input = 0;
	var->heredocs = 0;
	var->saved_stdin = -1;
	var->saved_stdout = -1;
	var->do_the_exec = TRUE;
}

void	ft_cleargarbage(t_var *var)
{
	t_garbage	*current_node;
	t_garbage	*next_node;

	clear_tmp_files(var);
	current_node = var->garbage_collector;
	while (current_node)
	{
		next_node = current_node->next;
		if (current_node->content)
			free(current_node->content);
		free(current_node);
		current_node = next_node;
	}
	g_sig = KEEP_GOING;
	clear_var(var);
}

void	ft_clear_line_memory(t_var *var)
{
	t_line_memory	*current_node;
	t_line_memory	*next_node;

	current_node = var->first_line;
	while (current_node)
	{
		next_node = current_node->next;
		free(current_node->line);
		free(current_node);
		current_node = next_node;
	}
	var->first_line = 0;
	var->line_memory = 0;
}
