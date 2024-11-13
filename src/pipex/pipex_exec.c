/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:13:36 by asuteau           #+#    #+#             */
/*   Updated: 2024/07/15 12:13:37 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isempty(char *str)
{
	while (*str && *str == ' ')
		str++;
	if (*str == '\0')
		return (1);
	return (0);
}

void	execute(t_var *pvar, int i)
{
	if (!pvar->cmds[i][0] || !pvar->cmds[i][0][0])
		clear_all_and_exit(pvar, 127);
	if (cmd_is_builtin(pvar, i))
		execbuiltin(pvar, i);
	else if (check_if_path_or_builtin(pvar, i) && !pvar->cmd_paths[i])
		handle_cmd_path_error(pvar, i);
	else if (!pvar->cmd_paths[i])
		clear_all_and_exit(pvar, 127);
	else if (execve(pvar->cmd_paths[i], pvar->cmds[i], pvar->tmp_envp) == -1)
		handle_execve_error(pvar);
}

void	forks_loop(t_var *pvar)
{
	int	i;

	i = -1;
	set_signal_handler(SIGQUIT, signal_handler_parent);
	while (++i < pvar->num_of_cmd)
	{
		if (pvar->num_of_cmd > 1 || (pvar->num_of_cmd == 1
				&& !cmd_is_builtin(pvar, 0)))
			pvar->pids[i] = fork();
		if (pvar->pids[i] == -1)
		{
			ft_putstr_fd("mnsh: fork error \n", 2);
			clear_all_and_exit(pvar, 1);
		}
		if (pvar->pids[i] == 0 || (pvar->num_of_cmd == 1
				&& cmd_is_builtin(pvar, 0)))
		{
			if (pvar->pids[i] == 0)
				set_signal_child_process();
			get_filefds_and_cmdpath(pvar, i);
			close_all_pipes_children(pvar, i);
			if (pvar->do_the_exec == TRUE)
				execute(pvar, i);
		}
	}
}

static void	do_post_pipex_dups(t_var *pvar)
{
	if (dup2(pvar->saved_stdin, STDIN_FILENO) == -1
		|| dup2(pvar->saved_stdout, STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("error during the dups, exiting the program\n", 2);
		clear_all_and_exit(pvar, 2);
	}
}

void	pipex_execute_cmds(t_var *pvar)
{
	init_exec_vars(pvar);
	init_pids(pvar);
	forks_loop(pvar);
	if (pvar->num_of_cmd > 1 || (pvar->num_of_cmd == 1
			&& !cmd_is_builtin(pvar, 0)))
	{
		close_all_pipes_parent(pvar);
		wait_and_get_status(pvar);
		ft_change_env_var(pvar, "?", ft_itoa(pvar->last_cmd_exit_status, pvar));
		if (pvar->num_of_cmd == 1)
			do_post_pipex_dups(pvar);
	}
}
