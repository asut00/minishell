/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:17:01 by thelaine          #+#    #+#             */
/*   Updated: 2024/07/17 19:14:09 by thelaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_special_char(char c)
{
	if (ft_is_whitespace(c) || c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

static int	count_len_word(char *input)
{
	int		i;
	char	quote;

	i = 0;
	while (1)
	{
		if (*(input + i) == '\"' || *(input + i) == '\'')
		{
			quote = *(input + i);
			i++;
			while (*(input + i) && *(input + i) != quote)
				i++;
			if (!(*(input + i)))
				return (-1);
			i++;
		}
		while (*(input + i) && *(input + i) != '\''
			&& *(input + i) != '\"'
			&& !is_special_char(*(input + i)))
			i++;
		if (!(*(input + i)) || is_special_char(*(input + i)))
			return (i);
	}
}

static int	create_special_char(char **pinput, t_var *var)
{
	t_commands	*new_command;
	char		*word;
	size_t		i;

	(void)var;
	i = 1;
	if (*(*pinput + i) && (**pinput == '<' || **pinput == '>')
		&& **pinput == *(*pinput + i))
		i++;
	word = ft_substr(*pinput, 0, i, var);
	new_command = ft_cmdnew(word, var);
	ft_cmdadd_back(&(var->commands), new_command);
	*pinput += i;
	return (1);
}

static int	create_command(char **pinput, t_var *var)
{
	t_commands	*new_command;
	char		*word;
	size_t		i;

	(void)var;
	i = count_len_word(*pinput);
	if (i > 0)
	{
		word = ft_substr(*pinput, 0, i, var);
		new_command = ft_cmdnew(word, var);
		ft_cmdadd_back(&(var->commands), new_command);
		*pinput += i;
	}
	return (1);
}

void	parsing(t_var *var)
{
	char	*input;

	input = var->input;
	while (*input)
	{
		while (ft_is_whitespace(*input))
			input++;
		if (*input)
		{
			create_command(&input, var);
			if (*input && is_special_char(*input) && !ft_is_whitespace(*input))
				create_special_char(&input, var);
		}
	}
}
