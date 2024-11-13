/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 19:11:09 by asuteau           #+#    #+#             */
/*   Updated: 2024/07/18 19:11:11 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_sig;

void	set_signal_child_process(void)
{
	set_signal_handler(SIGINT, SIG_DFL);
	set_signal_handler(SIGQUIT, SIG_DFL);
}

void	signal_handler_special(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = STOP_INT;
		rl_replace_line("", 0);
		rl_redisplay();
		rl_done = 1;
	}
}

void	signal_handler_parent(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = STOP_INT_MAIN;
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		g_sig = STOP_QUIT;
		ft_putstr_fd("Quit (core dumped)\n", 2);
	}
}

void	signal_handler_parent_after_readline(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = STOP_INT;
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}
