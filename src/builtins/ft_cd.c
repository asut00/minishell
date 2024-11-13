/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:46:10 by thelaine          #+#    #+#             */
/*   Updated: 2024/08/07 18:46:12 by thelaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	do_cd_error(char *path)
{
	ft_putstr_fd("mnsh: cd: ", 2);
	ft_putstr_fd(path, 2);
	if (access(path, F_OK) == 0)
		ft_putstr_fd(": Not a directory\n", 2);
	else if (ft_strlen(path) >= 256)
		ft_putstr_fd(": File name too long\n", 2);
	else
		ft_putstr_fd(": No such file or directory\n", 2);
	return (1);
}

static int	do_cd_success(t_var *pvar, char *path, int i)
{
	char	*oldpwd;
	char	*newpwd;

	oldpwd = ft_get_cwd(pvar);
	if (chdir(path) == 0)
	{
		newpwd = ft_get_cwd(pvar);
		ft_change_env_var(pvar, "PWD", newpwd);
		ft_change_env_var(pvar, "OLDPWD", oldpwd);
		if (pvar->cmd_lengths[i] > 1 && !ft_strcmp(pvar->cmds[i][1], "-"))
		{
			ft_putstr_fd(newpwd, 1);
			ft_putchar_fd('\n', 1);
		}
		ft_free(pvar, newpwd);
		ft_free(pvar, oldpwd);
		return (0);
	}
	return (ft_free(pvar, oldpwd), do_cd_error(path));
}

static void	deal_with_cd_quotes(t_var *pvar, int i)
{
	char	*new_arg;

	new_arg = 0;
	new_arg = ft_malloc(2, sizeof(char), pvar);
	new_arg[0] = '.';
	new_arg[1] = '\0';
	ft_free(pvar, pvar->cmds[i][1]);
	pvar->cmds[i][1] = new_arg;
}

static int	do_cd(t_var *pvar, int i)
{
	char	*path;

	if (pvar->cmd_lengths[i] == 2 && pvar->cmds[i][1][0] == '\0')
		deal_with_cd_quotes(pvar, i);
	path = pvar->cmds[i][1];
	if (pvar->cmd_lengths[i] == 1 || pvar->cmds[i][1][0] == '\0'
		|| !ft_strcmp(pvar->cmds[i][1], "~"))
	{
		path = ft_getenv(pvar, "HOME");
		if (!path)
			return (ft_putstr_fd("mnsh: cd: HOME not set\n", 2), 1);
	}
	else if (!ft_strcmp(pvar->cmds[i][1], "-"))
	{
		path = ft_getenv(pvar, "OLDPWD");
		if (!path)
			return (ft_putstr_fd("mnsh: cd: OLDPWD not set\n", 2), 1);
	}
	else if (pvar->cmds[i][1][0] == '\0')
		return (0);
	return (do_cd_success(pvar, path, i));
}

void	ft_cd(t_var *pvar, int i)
{
	int	ret;

	if (pvar->cmd_lengths[i] > 2)
	{
		ft_putstr_fd("mnsh: cd: too many arguments\n", 2);
		ft_change_env_var(pvar, "?", ft_itoa(EXIT_FAILURE, pvar));
		pvar->last_cmd_exit_status = EXIT_FAILURE;
	}
	else
	{
		ret = do_cd(pvar, i);
		ft_change_env_var(pvar, "?", ft_itoa(ret, pvar));
		pvar->last_cmd_exit_status = ret;
	}
	if (pvar->num_of_cmd > 1)
		clear_all_and_exit(pvar, pvar->last_cmd_exit_status);
}
