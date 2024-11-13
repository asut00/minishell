/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:09:21 by thelaine          #+#    #+#             */
/*   Updated: 2024/07/17 19:11:36 by thelaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	dollar(t_commands **c, char **final_word, int *pi, t_var *var)
{
	int		i;
	char	*var_name;

	i = 1;
	while (((*c)->word)[*pi + i] && (ft_isalpha(((*c)->word)[*pi + i])
			|| ((*c)->word)[*pi + i] == '_'))
		i++;
	if (i == 1 && ((*c)->word)[*pi + i] == '?')
		i++;
	else if (i == 1 && (var->mode == NO_QUOTE && (((*c)->word)[*pi + i] == '\''
			|| ((*c)->word)[*pi + i] == '\"')))
	{
		*pi += i;
		return ;
	}
	if (i == 1)
	{
		*final_word = ft_strjoin(*final_word, "$", var);
		*pi += i;
		return ;
	}
	var_name = ft_substr(&(*c)->word[*pi], 1, i - 1, var);
	write_dollar(c, final_word, var, ft_getenv(var, var_name));
	ft_free(var, var_name);
	*pi += i;
}

static int	simple_quote(char *command, char **final_word, int *pi, t_var *var)
{
	int		i;
	char	*str;

	i = 1;
	while (*(command + i) && *(command + i) != '\'')
		i++;
	str = ft_substr(command, 1, i - 1, var);
	*final_word = ft_strjoin(*final_word, str, var);
	*pi += i + 1;
	return (SUCCESS);
}

static void	copy_one_char(char *command, char **final_word, int *pi, t_var *var)
{
	char	*c;

	(void)var;
	c = ft_malloc(2, sizeof(char), var);
	c[0] = command[*pi];
	c[1] = '\0';
	*final_word = ft_strjoin(*final_word, c, var);
	*pi += 1;
	ft_free(var, c);
}

static void	expand_command(t_commands *command, t_var *var)
{
	char	*final_word;
	int		i;

	var->mode = NO_QUOTE;
	i = 0;
	final_word = ft_malloc(1, sizeof(char), var);
	final_word[0] = '\0';
	while ((command->word)[i])
	{
		if ((command->word)[i] == '$')
			dollar(&command, &final_word, &i, var);
		else if ((command->word)[i] == '\'' && var->mode == NO_QUOTE)
			simple_quote(&(command->word)[i], &final_word, &i, var);
		else if ((command->word)[i] == '\"')
		{
			var->mode = 1 - var->mode;
			i++;
		}
		else
			copy_one_char(command->word, &final_word, &i, var);
	}
	ft_free(var, command->word);
	command->word = final_word;
}

void	expand(t_var *var)
{
	t_commands	*command;

	command = var->commands;
	while (command)
	{
		expand_command(command, var);
		command = command->next;
	}
}
