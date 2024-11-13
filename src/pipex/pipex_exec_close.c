/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_close.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:58:11 by asuteau           #+#    #+#             */
/*   Updated: 2024/07/10 18:58:12 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all_pipes_parent(t_var *pvar)
{
	int	i;

	i = 0;
	while (i < pvar->num_of_cmd)
	{
		close(pvar->pipe_fds[i][0]);
		close(pvar->pipe_fds[i][1]);
		i++;
	}
}

void	close_all_pipes_children(t_var *pvar, int i)
{
	int	j;

	j = 0;
	while (j < pvar->num_of_cmd)
	{
		close(pvar->pipe_fds[j][0]);
		close(pvar->pipe_fds[j][1]);
		j++;
	}
	if (pvar->do_the_exec == TRUE && pvar->exec_fds[i][0] != STDIN_FILENO)
		close(pvar->exec_fds[i][0]);
	if (pvar->do_the_exec == TRUE && pvar->exec_fds[i][1] != STDOUT_FILENO)
		close(pvar->exec_fds[i][1]);
	if (!(pvar->num_of_cmd == 1 && cmd_is_builtin(pvar, 0)))
	{
		close(pvar->saved_stdin);
		close(pvar->saved_stdout);
	}
}

void	close_previous_pipes(t_var *pvar, int i)
{
	close(pvar->pipe_fds[i][1]);
	i--;
	while (i >= 0)
	{
		i--;
		close(pvar->pipe_fds[i][0]);
		close(pvar->pipe_fds[i][1]);
	}
}
