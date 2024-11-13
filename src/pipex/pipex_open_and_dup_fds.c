/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_open_and_dup_fds.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:18:04 by thelaine          #+#    #+#             */
/*   Updated: 2024/08/29 11:18:12 by thelaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_input_fd(t_var *pvar, int i, char *file)
{
	pvar->exec_fds[i][STDIN_FILENO] = open(file, O_RDONLY);
	if (pvar->exec_fds[i][0] == -1)
	{
		ft_putstr_fd("mnsh: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": No such file or directory", 2);
		ft_putstr_fd(": or permission denied\n", 2);
		pvar->do_the_exec = FALSE;
		pvar->last_cmd_exit_status = 1;
		if (pvar->pids[i] == 0)
		{
			close_all_pipes_children(pvar, i);
			clear_all_and_exit(pvar, 1);
		}
		return (1);
	}
	return (0);
}

int	open_output_fd(t_var *pvar, int i, char *file, int mode)
{
	if (mode == APPEND)
		pvar->exec_fds[i][1] = open(file,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		pvar->exec_fds[i][1] = open(file,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pvar->exec_fds[i][1] == -1)
	{
		ft_putstr_fd("mnsh: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": No such file or directory", 2);
		ft_putstr_fd(": or permission denied\n", 2);
		pvar->do_the_exec = FALSE;
		pvar->last_cmd_exit_status = 1;
		if (pvar->pids[i] == 0)
		{
			close_all_pipes_children(pvar, i);
			clear_all_and_exit(pvar, 1);
		}
		return (1);
	}
	return (0);
}
