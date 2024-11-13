/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command_error_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:56:37 by thelaine          #+#    #+#             */
/*   Updated: 2024/07/17 19:38:46 by thelaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_quotes(char *input, int *type)
{
	char	quote_type;
	int		skip_length;

	skip_length = 1;
	quote_type = *input;
	while (*(input + skip_length) && *(input + skip_length) != quote_type)
	{
		skip_length++;
	}
	if (*(input + skip_length) == quote_type)
		skip_length++;
	*type = NOT_DEFINED;
	return (skip_length);
}

int	is_parse_error(int type, int type_prev)
{
	if (type_prev == PIPELINE && type == PIPELINE)
		return (1);
	if ((type_prev == REDIR_IN || type_prev == HEREDOC) && type == PIPELINE)
		return (1);
	if (type_prev == REDIR_IN || type_prev == REDIR_OUT
		|| type_prev == HEREDOC || type_prev == REDIR_OUT_APPEND)
		return (type == REDIR_IN || type == REDIR_OUT
			|| type == HEREDOC || type == REDIR_OUT_APPEND);
	return (0);
}

void	parsing_error(int type)
{
	if (type == NOT_DEFINED)
		ft_putstr_fd("mnsh: syntax error near unexpected \\n\n", STDERR_FILENO);
	if (type == PIPELINE)
		ft_putstr_fd("mnsh: syntax error near unexpected |\n", STDERR_FILENO);
	if (type == HEREDOC)
		ft_putstr_fd("mnsh: syntax error near unexpected <<\n", STDERR_FILENO);
	if (type == REDIR_IN)
		ft_putstr_fd("mnsh: syntax error near unexpected <\n", STDERR_FILENO);
	if (type == REDIR_OUT)
		ft_putstr_fd("mnsh: syntax error near unexpected >\n", STDERR_FILENO);
	if (type == REDIR_OUT_APPEND)
		ft_putstr_fd("mnsh: syntax error near unexpected >>\n", STDERR_FILENO);
}
