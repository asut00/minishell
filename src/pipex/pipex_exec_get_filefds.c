/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec_get_filefds.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:49:49 by asuteau           #+#    #+#             */
/*   Updated: 2024/07/16 14:49:50 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_the_dups(t_var *pvar, int i)
{
	if (pvar->exec_fds[i][0] != 0
		&& dup2(pvar->exec_fds[i][0], STDIN_FILENO) == -1)
	{
		ft_putstr_fd("mnsh: input file dup2 error\n", 2);
		if (pvar->pids[i] == 0)
			close_all_pipes_children(pvar, i);
		clear_all_and_exit(pvar, 1);
	}
	if (pvar->exec_fds[i][1] != 1
		&& dup2(pvar->exec_fds[i][1], STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("mnsh: output dup2 error \n", 2);
		if (pvar->pids[i] == 0)
			close_all_pipes_children(pvar, i);
		clear_all_and_exit(pvar, 1);
	}
}

static void	get_input_fd(t_var *pvar, int i)
{
	int	k;

	k = 0;
	if (pvar->infiles[i] && !pvar->infiles[i][0] && i == 0)
		pvar->exec_fds[i][0] = STDIN_FILENO;
	else if (pvar->infiles[i] && !pvar->infiles[i][0] && i != 0)
		pvar->exec_fds[i][0] = pvar->pipe_fds[i - 1][0];
	while (pvar->infiles[i] && pvar->infiles[i][k])
	{
		if (open_input_fd(pvar, i, pvar->infiles[i][k]))
		{
			pvar->do_the_exec = FALSE;
			pvar->last_cmd_exit_status = 1;
			return ;
		}
		k++;
		if (pvar->infiles[i] && pvar->infiles[i][k])
			close(pvar->exec_fds[i][0]);
	}
}

static void	get_output_fd(t_var *pvar, int i)
{
	int	l;

	l = 0;
	pvar->exec_fds[i][1] = STDOUT_FILENO;
	if (pvar->outfiles[i] && !pvar->outfiles[i][0]
		&& i == pvar->num_of_cmd - 1)
		pvar->exec_fds[i][1] = STDOUT_FILENO;
	else if (pvar->outfiles[i] && !pvar->outfiles[i][0]
		&& i != pvar->num_of_cmd - 1)
		pvar->exec_fds[i][1] = pvar->pipe_fds[i][1];
	while (pvar->outfiles[i] && pvar->outfiles[i][l])
	{
		if (open_output_fd(pvar, i, pvar->outfiles[i][l],
			pvar->out_types[i][l]))
		{
			pvar->do_the_exec = FALSE;
			pvar->last_cmd_exit_status = 1;
			return ;
		}
		l++;
		if (pvar->outfiles[i] && pvar->outfiles[i][l])
			close(pvar->exec_fds[i][1]);
	}
}

void	get_filefds_and_cmdpath(t_var *pvar, int i)
{
	get_input_fd(pvar, i);
	if (pvar->do_the_exec == TRUE)
	{
		get_output_fd(pvar, i);
		if (pvar->do_the_exec == TRUE)
		{
			do_the_dups(pvar, i);
			pipex_get_cmd_path(pvar, i);
			return ;
		}
	}
	ft_change_env_var(pvar, "?", ft_itoa(pvar->last_cmd_exit_status, pvar));
}
