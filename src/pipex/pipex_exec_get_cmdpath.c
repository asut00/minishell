/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec_get_cmdpath.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:45:37 by asuteau           #+#    #+#             */
/*   Updated: 2024/07/11 13:45:39 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	try_env_path_loop(t_var *pvar, int *path_found, int i, int *j)
{
	char	*tmp_path;
	int		size;

	while (pvar->splitted_env[*j] && *path_found == 0 && pvar->cmds[i][0])
	{
		size = ft_strlen(pvar->splitted_env[*j]) + ft_strlen(pvar->cmds[i][0]);
		tmp_path = ft_malloc(size + 2, 1, pvar);
		tmp_path[0] = '\0';
		ft_strcat(tmp_path, pvar->splitted_env[*j]);
		ft_strcat(tmp_path, "/");
		ft_strcat(tmp_path, pvar->cmds[i][0]);
		if (access(tmp_path, X_OK) == 0)
		{
			(*path_found)++;
			pvar->cmd_paths[i] = tmp_path;
		}
		else
			ft_free(pvar, tmp_path);
		(*j)++;
	}
}

int	cmd_is_builtin(t_var *pvar, int i)
{
	if (!pvar->cmds[i][0] || !pvar->cmds[i][0][0])
		return (0);
	if (!ft_strcmp(pvar->cmds[i][0], "echo")
			|| !ft_strcmp(pvar->cmds[i][0], "cd")
			|| !ft_strcmp(pvar->cmds[i][0], "pwd")
			|| !ft_strcmp(pvar->cmds[i][0], "export")
			|| !ft_strcmp(pvar->cmds[i][0], "unset")
			|| !ft_strcmp(pvar->cmds[i][0], "env")
			|| !ft_strcmp(pvar->cmds[i][0], "exit"))
	{
		return (1);
	}
	return (0);
}

void	pipex_get_cmd_path(t_var *pvar, int i)
{
	int		j;
	int		path_found;

	j = 0;
	path_found = 0;
	if (pvar->cmds[i][0] && cmd_is_builtin(pvar, i))
		return ;
	if (!pvar->cmds[i][0][0])
		handle_path_not_found(pvar, i);
	else if (access(pvar->cmds[i][0], X_OK) == 0)
		handle_absolute_path(pvar, &path_found, i);
	else
		try_env_path_loop(pvar, &path_found, i, &j);
	if (pvar->cmds[i][0] && pvar->cmds[i][0][0] && path_found == 0)
		handle_path_not_found(pvar, i);
}

void	check_if_rel_path_loop(t_var *pvar, int *path_found, int i, int *j)
{
	char	*tmp_path;
	int		size;

	while (pvar->splitted_env[*j] && *path_found == 0 && pvar->cmds[i][0])
	{
		size = ft_strlen(pvar->splitted_env[*j]) + ft_strlen(pvar->cmds[i][0]);
		tmp_path = ft_malloc(size + 2, 1, pvar);
		tmp_path[0] = '\0';
		ft_strcat(tmp_path, pvar->splitted_env[*j]);
		ft_strcat(tmp_path, "/");
		ft_strcat(tmp_path, pvar->cmds[i][0]);
		if (access(tmp_path, X_OK) == 0)
		{
			(*path_found)++;
		}
		else
			ft_free(pvar, tmp_path);
		(*j)++;
	}
}

int	check_if_path_or_builtin(t_var *pvar, int i)
{
	int		j;
	int		path_found;

	j = 0;
	path_found = 0;
	if (!pvar->cmds[i][0])
		return (0);
	if (pvar->cmds[i][0] && cmd_is_builtin(pvar, i))
		return (1);
	if (access(pvar->cmds[i][0], X_OK) == 0)
		return (1);
	check_if_rel_path_loop(pvar, &path_found, i, &j);
	if (path_found > 0)
		return (1);
	else
		return (0);
}
