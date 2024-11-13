/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:55:31 by thelaine          #+#    #+#             */
/*   Updated: 2024/07/22 10:55:55 by thelaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_sig;

static char	*readline_from_memory(t_var *pvar)
{
	char			*input;
	t_line_memory	*line_memory;

	line_memory = pvar->line_memory;
	input = ft_strdup_spe(line_memory->line, pvar);
	pvar->line_memory = line_memory->next;
	return (input);
}

static void	manage_void_input(t_var *var, int mode)
{
	if (mode == MAIN || mode == PIPELINE)
	{
		if (isatty(STDIN_FILENO))
		{
			if (mode == PIPELINE)
				ft_putstr_fd("mnsh: syntax error: unexpected end of file\n", 2);
			ft_putstr_fd("exit\n", 2);
		}
		clear_all_and_exit(var, var->last_cmd_exit_status);
	}
	if (isatty(STDIN_FILENO))
		ft_putstr_fd("mnsh: syntax error: unexpected end of file\n", 2);
	g_sig = STOP_EMPTY;
	rl_replace_line("", 0);
	rl_redisplay();
	rl_done = 1;
}

char	*ft_readline(char *prompt, t_var *pvar, int mode)
{
	char	*input;

	if (!pvar->line_memory)
	{
		ft_clear_line_memory(pvar);
		input = readline(prompt);
		if (!input)
			manage_void_input(pvar, mode);
		if (g_sig == STOP_INT_MAIN)
		{
			ft_change_env_var(pvar, "?", "130");
			g_sig = KEEP_GOING;
		}
		if (g_sig != KEEP_GOING)
			return (NULL);
		split_line(input, pvar);
	}
	return (readline_from_memory(pvar));
}
