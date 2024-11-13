/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line_memory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:37:04 by thelaine          #+#    #+#             */
/*   Updated: 2024/08/12 12:37:53 by thelaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_malloc_readline(t_var *pvar, char *line)
{
	t_line_memory	*line_memory;
	t_line_memory	*last_line;

	line_memory = malloc(sizeof(t_line_memory));
	if (!line_memory)
	{
		free(line);
		clear_all_and_exit(pvar, 1);
	}
	line_memory->line = line;
	line_memory->next = 0;
	if (!pvar->first_line)
	{
		pvar->first_line = line_memory;
		pvar->line_memory = line_memory;
	}
	else
	{
		last_line = pvar->line_memory;
		while (last_line->next)
			last_line = last_line->next;
		last_line->next = line_memory;
	}
}

static int	skip_quotes_readline(char *input)
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
	return (skip_length);
}

static void	split_line_loop(int *len, int start, char *input)
{
	while (*(input + start + *len) != '\n' && *(input + start + *len) != ';'
		&& *(input + start + *len) != '\0')
	{
		if (*(input + start + *len) == '\'' || *(input + start + *len) == '\"')
			*len += skip_quotes_readline(input + *len + start);
		else
			*len += 1;
	}
}

void	split_line(char *input, t_var *pvar)
{
	char	*line;
	int		len;
	int		start;
	int		is_not_over;

	len = 0;
	is_not_over = 1;
	start = 0;
	while (is_not_over)
	{
		split_line_loop(&len, start, input);
		if (*(input + start + len) == '\0')
			is_not_over = 0;
		line = ft_substr_malloc(input, start, len);
		if (!line)
			return (free(input), clear_all_and_exit(pvar, 1));
		start += len + 1;
		len = 0;
		ft_malloc_readline(pvar, line);
	}
	free(input);
}
