/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:06:30 by thelaine          #+#    #+#             */
/*   Updated: 2024/07/17 19:20:47 by thelaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	lexing_cmd_3(t_commands *command, int *pmode, int *set_cmd)
{
	(void)set_cmd;
	if (*pmode == LIM)
	{
		command->type = LIM;
		*pmode = ARGS;
	}
	else if (*pmode == FILE_IN || *pmode == FILE_OUT
		|| *pmode == FILE_OUT_APPEND)
	{
		command->type = *pmode;
		*pmode = ARGS;
	}
	else if (*pmode == ARGS && *set_cmd == 0)
	{
		command->type = COMMAND;
		*set_cmd = 1;
	}
	else if (*pmode == ARGS)
	{
		if (command->word[0] == '-')
			command->type = OPTION;
		else
			command->type = ARGS;
	}
}

static void	lexing_cmd_2(t_commands *cmd, int *pmode, int *set_cmd)
{
	if (cmd->type == NOT_DEFINED && !ft_strcmp(cmd->word, ">>"))
	{
		cmd->type = REDIR_OUT_APPEND;
		*pmode = FILE_OUT_APPEND;
	}
	else if (cmd->type == NOT_DEFINED && !ft_strcmp(cmd->word, "<<"))
	{
		cmd->type = HEREDOC;
		*pmode = LIM;
	}
	else
		lexing_cmd_3(cmd, pmode, set_cmd);
}

static void	lexing_cmd_1(t_commands *cmd, int *pmode, int *set_cmd)
{
	if (cmd->type == NOT_DEFINED && !ft_strcmp(cmd->word, "|"))
	{
		cmd->type = PIPELINE;
		*pmode = ARGS;
		*set_cmd = 0;
	}
	else if (cmd->type == NOT_DEFINED && !ft_strcmp(cmd->word, "<"))
	{
		cmd->type = REDIR_IN;
		*pmode = FILE_IN;
	}
	else if (cmd->type == NOT_DEFINED && !ft_strcmp(cmd->word, ">"))
	{
		cmd->type = REDIR_OUT;
		*pmode = FILE_OUT;
	}
	else
		lexing_cmd_2(cmd, pmode, set_cmd);
}

void	lexing(t_var *var)
{
	t_commands	*command;
	int			mode;
	int			set_cmd;

	set_cmd = 0;
	mode = ARGS;
	command = var->commands;
	while (command)
	{
		lexing_cmd_1(command, &mode, &set_cmd);
		command = command->next;
	}
}
