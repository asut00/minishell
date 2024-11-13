/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:36:34 by asuteau           #+#    #+#             */
/*   Updated: 2024/07/17 11:36:37 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_the_echo(t_var *pvar, int i, int j, int mode)
{
	int	put_space;

	put_space = 0;
	while (pvar->cmds[i][j])
	{
		if (put_space)
			ft_putchar_fd(' ', 1);
		ft_putstr_fd(pvar->cmds[i][j], 1);
		j++;
		put_space = 1;
	}
	if (!mode)
		ft_putchar_fd('\n', 1);
}

static int	is_option(char *str)
{
	if (*str != '-')
		return (FALSE);
	str++;
	while (*str)
	{
		if (*str++ != 'n')
			return (FALSE);
	}
	return (TRUE);
}

static void	do_the_echo_no_args(int mode)
{
	if (!mode)
		ft_putchar_fd('\n', 1);
}

void	ft_echo(t_var *pvar, int i)
{
	int	j;
	int	mode;

	mode = 0;
	j = 1;
	if (!pvar->cmds[i][j])
	{
		return (do_the_echo_no_args(mode), ft_change_env_var(pvar, "?", "0"));
		pvar->last_cmd_exit_status = 0;
	}
	if (is_option(pvar->cmds[i][j]) == TRUE)
	{
		mode = 1;
		j++;
	}
	while (pvar->cmds[i][j] && is_option(pvar->cmds[i][j]) == TRUE)
		j++;
	if (!pvar->cmds[i][j])
	{
		pvar->last_cmd_exit_status = 0;
		return (do_the_echo_no_args(mode));
	}
	do_the_echo(pvar, i, j, mode);
	ft_change_env_var(pvar, "?", "0");
	pvar->last_cmd_exit_status = 0;
}
