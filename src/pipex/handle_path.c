/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:49:20 by thelaine          #+#    #+#             */
/*   Updated: 2024/08/06 19:49:22 by thelaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_absolute_path(t_var *pvar, int *path_found, int i)
{
	(*path_found)++;
	pvar->cmd_paths[i] = pvar->cmds[i][0];
}

void	handle_path_not_found(t_var *pvar, int i)
{
	ft_putstr_fd("mnsh: ", 2);
	if (!pvar->cmds[i][0][0])
		ft_putstr_fd("\'\'", 2);
	else
		ft_putstr_fd(pvar->cmds[i][0], 2);
	ft_putstr_fd(": command not found or execution permission denied\n", 2);
}
