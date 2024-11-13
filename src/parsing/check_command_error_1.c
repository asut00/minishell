/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command_error_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 19:43:08 by thelaine          #+#    #+#             */
/*   Updated: 2024/07/17 19:35:15 by thelaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_last(int type)
{
	if (type == HEREDOC || type == REDIR_IN
		|| type == REDIR_OUT || type == REDIR_OUT_APPEND)
		return (parsing_error(NOT_DEFINED), 0);
	return (1);
}

static int	select_type(char *input, int *type)
{
	if (*input == '|')
		*type = PIPELINE;
	else if (*input == '>')
	{
		if (*(input + 1) == '>')
			*type = REDIR_OUT_APPEND;
		else
			*type = REDIR_OUT;
	}
	else if (*input == '<')
	{
		if (*(input + 1) == '<')
			*type = HEREDOC;
		else
			*type = REDIR_IN;
	}
	if (*type == HEREDOC || *type == REDIR_OUT_APPEND)
		return (2);
	return (1);
}

static int	is_special(char c)
{
	return (c == '\'' || c == '\"' || c == '>' || c == '<' || c == '|');
}

static int	check_cmd_error_loop(char *input, int type_prev, int type)
{
	while (*input)
	{
		while (ft_is_whitespace(*input))
			input++;
		if (*input == '\'' || *input == '\"')
			input += skip_quotes(input, &type_prev);
		else if (is_special(*input))
		{
			if (type_prev == NOT_DEFINED)
				input += select_type(input, &type_prev);
			else
			{
				input += select_type(input, &type);
				if (is_parse_error(type, type_prev))
					return (parsing_error(type_prev), 0);
			}
		}
		else if (*input)
		{
			type_prev = NOT_DEFINED;
			input++;
		}
	}
	return (check_last(type_prev));
}

int	check_command_error(t_var *var)
{
	char	*input;
	int		type_prev;
	int		type;

	type_prev = NOT_DEFINED;
	type = NOT_DEFINED;
	input = var->input;
	if (*input == '|')
		return (parsing_error(PIPELINE), 0);
	return (check_cmd_error_loop(input, type_prev, type));
}
