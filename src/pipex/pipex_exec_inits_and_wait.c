/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec_inits_and_wait.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:55:53 by asuteau           #+#    #+#             */
/*   Updated: 2024/07/16 14:55:54 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_exec_vars(t_var *pvar)
{
	char	*split_chars;

	split_chars = ft_malloc(2, sizeof(char), pvar);
	split_chars[0] = ':';
	split_chars[1] = '\0';
	pvar->env_path = ft_getenv(pvar, "PATH");
	pvar->splitted_env = ft_split(pvar->env_path, split_chars, pvar);
}

void	neutralize_pids(t_var *pvar)
{
	int	i;

	i = 0;
	while (i < pvar->num_of_cmd)
	{
		pvar->pids[i] = -2;
		i++;
	}
}

void	init_pids(t_var *pvar)
{
	pvar->pids = ft_malloc(pvar->num_of_cmd, sizeof(pid_t), pvar);
	neutralize_pids(pvar);
}

void	wait_and_get_status(t_var *pvar)
{
	int	i;

	i = 0;
	while (i < pvar->num_of_cmd)
	{
		if (waitpid(pvar->pids[i], &pvar->status, 0) == -1)
			return ;
		if (i == pvar->num_of_cmd - 1 && WIFEXITED(pvar->status))
			pvar->last_cmd_exit_status = WEXITSTATUS(pvar->status);
		i++;
	}
}
