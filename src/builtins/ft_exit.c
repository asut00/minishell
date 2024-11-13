/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:36:34 by asuteau           #+#    #+#             */
/*   Updated: 2024/07/17 11:36:37 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_numarg_error(t_var *pvar, int i)
{
	ft_putstr_fd("mnsh: exit: ", 2);
	ft_putstr_fd(pvar->cmds[i][1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	clear_all_and_exit(pvar, 2);
}

static void	exit_too_many_arg_error(t_var *pvar, int i)
{
	(void)i;
	ft_putstr_fd("mnsh: exit: too many arguments\n", 2);
	ft_change_env_var(pvar, "?", "1");
	pvar->last_cmd_exit_status = 1;
}

static void	exit_error(t_var *pvar, int i)
{
	if (ft_strisnumber_spe(pvar->cmds[i][1]))
		exit_too_many_arg_error(pvar, i);
	else
		exit_numarg_error(pvar, i);
}

void	handle_tricky_numbers(t_var *pvar, int i)
{
	if ((ft_strlen(pvar->cmds[i][1]) > 20 && pvar->cmds[i][1][0] != '0')
		|| (ft_strlen(pvar->cmds[i][1]) == 20 && pvar->cmds[i][1][0] != '0'
		&& pvar->cmds[i][1][0] != '-')
		|| (ft_atoll(pvar->cmds[i][1]) > __INT_MAX__
		&& pvar->cmds[i][1][0] == '-'))
		exit_numarg_error(pvar, i);
	if (ft_islonglong(pvar->cmds[i][1]))
	{
		clear_all_and_exit(pvar, ft_atoi(pvar->cmds[i][1]));
	}
	if (ft_atoull(pvar->cmds[i][1]) > __LONG_MAX__)
		exit_numarg_error(pvar, i);
	else
		clear_all_and_exit(pvar, ft_atoi(pvar->cmds[i][1]));
}

void	ft_exit(t_var *pvar, int i)
{
	ft_putstr_fd("exit\n", 1);
	if (pvar->cmd_lengths[i] == 1 || !pvar->cmds[i][1])
		clear_all_and_exit(pvar, pvar->last_cmd_exit_status);
	if (pvar->cmd_lengths[i] == 2 && !ft_strcmp("--", pvar->cmds[i][1]))
		clear_all_and_exit(pvar, pvar->last_cmd_exit_status);
	else if (pvar->cmd_lengths[i] == 2 && ft_strisnumber_spe(pvar->cmds[i][1]))
		handle_tricky_numbers(pvar, i);
	else
		exit_error(pvar, i);
	if (pvar->num_of_cmd > 1)
		clear_all_and_exit(pvar, pvar->last_cmd_exit_status);
}
