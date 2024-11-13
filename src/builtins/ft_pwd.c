/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:00:22 by thelaine          #+#    #+#             */
/*   Updated: 2024/07/04 14:05:46 by thelaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_cwd(t_var *pvar)
{
	char	*cwd;

	cwd = ft_malloc(PATH_MAX, sizeof(char), pvar);
	if (!getcwd(cwd, PATH_MAX))
	{
		ft_change_env_var(pvar, "?", "1");
		pvar->last_cmd_exit_status = 1;
		ft_putstr_fd("mnsh: pwd: pwd failed\n", 2);
		return (NULL);
	}
	return (cwd);
}

void	ft_pwd(t_var *pvar)
{
	char	*cwd;

	cwd = ft_get_cwd(pvar);
	ft_putstr_fd(cwd, 1);
	if (cwd)
		ft_putchar_fd('\n', 1);
	ft_free(pvar, cwd);
	if (pvar->num_of_cmd > 1)
		clear_all_and_exit(pvar, pvar->last_cmd_exit_status);
}
