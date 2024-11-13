/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_array_loop.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:40:12 by thelaine          #+#    #+#             */
/*   Updated: 2024/08/06 18:40:28 by thelaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_cmd_length(t_commands	*command_line, t_var *pvar, int i)
{
	int	x;

	x = 0;
	while (command_line && command_line->type != PIPELINE)
	{
		command_line = command_line->next;
		x++;
	}
	pvar->cmd_lengths[i] = x;
}

static void	malloc_subarrays(t_var *pvar, int i)
{
	int	s;

	s = sizeof(char *);
	pvar->cmds[i] = ft_calloc(pvar->cmd_lengths[i] + 1, s, pvar);
	pvar->infiles[i] = ft_calloc(pvar->cmd_lengths[i] + 1, s, pvar);
	pvar->outfiles[i] = ft_calloc(pvar->cmd_lengths[i] + 1, s, pvar);
	pvar->out_types[i] = ft_calloc(pvar->cmd_lengths[i] + 1, sizeof(int), pvar);
}

static void	init_cmd_subloop(t_var *pvar, t_commands **cmd_line, t_iter *iter)
{
	if ((*cmd_line)->type == COMMAND)
		pvar->cmds[iter->i][0] = (*cmd_line)->word;
	else if ((*cmd_line)->type == ARGS || (*cmd_line)->type == OPTION)
	{
		pvar->cmds[iter->i][iter->j] = (*cmd_line)->word;
		iter->j++;
	}
	else if ((*cmd_line)->type == FILE_IN)
	{
		pvar->infiles[iter->i][iter->k] = (*cmd_line)->word;
		iter->k++;
	}
	else if ((*cmd_line)->type == FILE_OUT)
	{
		pvar->outfiles[iter->i][iter->l] = (*cmd_line)->word;
		pvar->redir[iter->i] = TRUE;
		iter->l++;
	}
	else if ((*cmd_line)->type == FILE_OUT_APPEND)
	{
		pvar->outfiles[iter->i][iter->l] = (*cmd_line)->word;
		pvar->out_types[iter->i][iter->l] = APPEND;
		pvar->redir[iter->i] = TRUE;
		iter->l++;
	}
}

static void	init_cmd_loop(t_var *pvar, t_commands **cmd_line, t_iter *iter)
{
	while ((*cmd_line) && (*cmd_line)->type != PIPELINE)
	{
		init_cmd_subloop(pvar, cmd_line, iter);
		(*cmd_line) = (*cmd_line)->next;
	}
}

void	init_cmd_arrays(t_var *pvar, t_commands *command_line, t_iter *iter)
{
	while (command_line)
	{
		get_cmd_length(command_line, pvar, iter->i);
		malloc_subarrays(pvar, iter->i);
		iter->j = 1;
		iter->k = 0;
		iter->l = 0;
		init_cmd_loop(pvar, &command_line, iter);
		pvar->cmds[iter->i][iter->j] = NULL;
		pvar->infiles[iter->i][iter->k] = NULL;
		pvar->outfiles[iter->i][iter->l] = NULL;
		if (command_line && command_line->type == PIPELINE)
		{
			iter->i++;
			command_line = command_line->next;
		}
	}
}
