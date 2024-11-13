/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:41:29 by thelaine          #+#    #+#             */
/*   Updated: 2024/07/17 19:34:17 by thelaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_sig;

static int	skip_double_quotes(char *input, int *mode)
{
	int	i;

	i = 0;
	while (*input && *input != '\"')
	{
		i++;
		input++;
	}
	if (*input == '\"')
	{
		*mode = IS_NOT_QUOTING;
		i++;
	}
	return (i);
}

static int	skip_single_quotes(char *input, int *mode)
{
	int	i;

	i = 0;
	while (*input && *input != '\'')
	{
		i++;
		input++;
	}
	if (*input == '\'')
	{
		*mode = IS_NOT_QUOTING;
		i++;
	}
	return (i);
}

static int	is_quoting(char *input, int mode)
{
	while (*input)
	{
		if (mode == IS_NOT_QUOTING)
		{
			while (*input && *input != '\"' && *input != '\'')
				input++;
			if (*input == '\"')
			{
				mode = IS_DOUBLE_QUOTING;
				input++;
			}
			else if (*input == '\'')
			{
				mode = IS_SINGLE_QUOTING;
				input++;
			}
		}
		if (mode == IS_DOUBLE_QUOTING)
			input += skip_double_quotes(input, &mode);
		else if (mode == IS_SINGLE_QUOTING)
			input += skip_single_quotes(input, &mode);
	}
	return (mode);
}

void	check_quotes(t_var *var)
{
	int		mode;
	char	*input;

	mode = is_quoting(var->input, IS_NOT_QUOTING);
	while (g_sig == KEEP_GOING && mode != IS_NOT_QUOTING)
	{
		input = ft_readline("quote> ", var, QUOTE);
		if (g_sig != KEEP_GOING)
			break ;
		var->input = ft_strjoin(var->input, "\n", var);
		var->input = ft_strjoin(var->input, input, var);
		ft_free(var, input);
		mode = is_quoting(var->input, IS_NOT_QUOTING);
	}
}
