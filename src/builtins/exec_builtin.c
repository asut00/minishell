/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bultin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:48:33 by thelaine          #+#    #+#             */
/*   Updated: 2024/08/07 18:49:27 by thelaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execbuiltin_2(t_var *pvar, int i)
{
	if (!ft_strcmp(pvar->cmds[i][0], "unset"))
	{
		ft_unset(pvar, pvar->cmds[i]);
		if (pvar->num_of_cmd > 1)
			clear_all_and_exit(pvar, pvar->last_cmd_exit_status);
	}
	else if (!ft_strcmp(pvar->cmds[i][0], "env"))
	{
		ft_env(pvar, pvar->cmds[i]);
		if (pvar->num_of_cmd > 1)
			clear_all_and_exit(pvar, pvar->last_cmd_exit_status);
	}
	else if (!ft_strcmp(pvar->cmds[i][0], "exit"))
		ft_exit(pvar, i);
}

void	execbuiltin(t_var *pvar, int i)
{
	int	ret;

	if (!ft_strcmp(pvar->cmds[i][0], "echo"))
	{
		ft_echo(pvar, i);
		if (pvar->num_of_cmd > 1)
			clear_all_and_exit(pvar, pvar->last_cmd_exit_status);
	}
	else if (!ft_strcmp(pvar->cmds[i][0], "cd"))
		ft_cd(pvar, i);
	else if (!ft_strcmp(pvar->cmds[i][0], "pwd"))
		ft_pwd(pvar);
	else if (!ft_strcmp(pvar->cmds[i][0], "export"))
	{
		ret = ft_export_spe(pvar, pvar->cmds[i]);
		pvar->last_cmd_exit_status = ret;
		if (pvar->num_of_cmd > 1)
			clear_all_and_exit(pvar, pvar->last_cmd_exit_status);
		ft_change_env_var(pvar, "?", ft_itoa(pvar->last_cmd_exit_status, pvar));
	}
	else
		execbuiltin_2(pvar, i);
}
