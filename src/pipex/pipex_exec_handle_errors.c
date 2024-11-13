/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec_handle_errors.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:45:33 by asuteau           #+#    #+#             */
/*   Updated: 2024/07/16 14:45:36 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_cmd_path_error(t_var *pvar, int i)
{
	ft_putstr_fd("mnsh: command not found : ", 2);
	ft_putstr_fd(pvar->cmds[i][0], 2);
	ft_putstr_fd(", execve not happening\n", 2);
	clear_all_and_exit(pvar, 127);
}

void	handle_execve_error(t_var *pvar)
{
	ft_putstr_fd("mnsh: execve failed \n", 2);
	clear_all_and_exit(pvar, 1);
}
