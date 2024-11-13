/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:37:51 by thelaine          #+#    #+#             */
/*   Updated: 2024/07/17 19:16:43 by thelaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_str_3(char *word)
{
	return (word[1] == '<' || word[1] == '>' || word[1] == '|');
}

static int	check_str_4(char *word)
{
	return ((word[1] == '<' && word[2] == '<')
		|| (word[1] == '>' && word[2] == '>'));
}

void	pre_expand(t_var *var)
{
	t_commands	*command;
	char		*word;

	command = var->commands;
	while (command)
	{
		word = command->word;
		if (ft_strlen(word) == 3 && check_str_3(word))
			command->type = ARGS;
		if (ft_strlen(word) == 4 && check_str_4(word))
			command->type = ARGS;
		command = command->next;
	}
}
