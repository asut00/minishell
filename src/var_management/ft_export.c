/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:46:42 by thelaine          #+#    #+#             */
/*   Updated: 2024/07/18 13:46:44 by thelaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_export_format(char *s)
{
	int	mode;

	mode = DEFINE;
	if (*s == '=' || ft_isdigit(*s))
		return (WRONG_FORMAT);
	while (*s && *s != '=' && *s != '+')
	{
		if (!ft_isalpha(*s) && *s != '_')
			return (WRONG_FORMAT);
		s++;
	}
	if (*s == '+')
	{
		if (*(s + 1) != '=')
			return (WRONG_FORMAT);
		mode = ADD;
		s++;
	}
	if (!*s)
		return (mode);
	if (*s == '=')
		s++;
	while (*s)
		s++;
	return (mode);
}

int	ft_export_spe(t_var *var, char **cmds)
{
	int	i;
	int	retvalue;
	int	mode;

	i = 1;
	retvalue = 0;
	if (!cmds[i])
		ft_env_export(var);
	while (cmds[i])
	{
		mode = is_export_format(cmds[i]);
		if (mode != WRONG_FORMAT)
			ft_export_one(var, cmds[i], mode);
		else
		{
			ft_putstr_fd("mnsh: export: `", 2);
			ft_putstr_fd(cmds[i], 2);
			ft_putstr_fd("\': not a valid identifier\n", 2);
			retvalue = 1;
		}
		i++;
	}
	return (retvalue);
}

void	ft_export(t_var *var, char **cmds)
{
	int	i;

	i = 1;
	if (!cmds[i])
		ft_env_export(var);
	while (cmds[i])
	{
		ft_export_one(var, cmds[i], DEFINE);
		i++;
	}
}
