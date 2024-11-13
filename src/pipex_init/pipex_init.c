/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:34:18 by asuteau           #+#    #+#             */
/*   Updated: 2024/07/12 17:34:19 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_num_of_cmd(t_var *pvar)
{
	int			count;
	t_commands	*command_line;

	command_line = pvar->commands;
	count = 1;
	while (command_line)
	{
		if (command_line->type == PIPELINE)
			count++;
		command_line = command_line->next;
	}
	pvar->num_of_cmd = count;
}

static void	malloc_arrays(t_var *pvar)
{
	int	i;

	pvar->cmds = ft_malloc(pvar->num_of_cmd + 1, sizeof(char **), pvar);
	pvar->infiles = ft_malloc(pvar->num_of_cmd + 1, sizeof(char **), pvar);
	pvar->outfiles = ft_malloc(pvar->num_of_cmd + 1, sizeof(char **), pvar);
	pvar->out_types = ft_malloc(pvar->num_of_cmd + 1, sizeof(int **), pvar);
	pvar->exec_fds = ft_malloc(pvar->num_of_cmd + 1, sizeof(int **), pvar);
	pvar->cmd_paths = ft_calloc(pvar->num_of_cmd + 1, sizeof(char *), pvar);
	pvar->cmd_lengths = ft_calloc(pvar->num_of_cmd + 1, sizeof(int), pvar);
	pvar->redir = ft_calloc(pvar->num_of_cmd + 1, sizeof(int), pvar);
	i = 0;
	while (i < pvar->num_of_cmd)
	{
		pvar->exec_fds[i] = ft_malloc(2, sizeof(int), pvar);
		i++;
	}
}

static void	malloc_and_init_pipe_fds(t_var *pvar)
{
	int	i;

	pvar->pipe_fds = ft_malloc(pvar->num_of_cmd + 1, sizeof(int *), pvar);
	i = 0;
	while (i < pvar->num_of_cmd)
	{
		pvar->pipe_fds[i] = ft_malloc(2, sizeof(int), pvar);
		if (pipe(pvar->pipe_fds[i]) == -1)
		{
			close_previous_pipes(pvar, i);
			ft_putstr_fd("mnsh: pipe function error\n", 2);
			clear_all_and_exit(pvar, 1);
		}
		i++;
	}
}

void	pipex_init(t_var *pvar)
{
	t_iter		iter;
	t_commands	*command_line;

	command_line = pvar->commands;
	get_num_of_cmd(pvar);
	malloc_arrays(pvar);
	malloc_and_init_pipe_fds(pvar);
	command_line = pvar->commands;
	iter.i = 0;
	init_cmd_arrays(pvar, command_line, &iter);
}
