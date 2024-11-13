/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c_2                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 19:11:09 by asuteau           #+#    #+#             */
/*   Updated: 2024/07/18 19:11:11 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_sig;

static int	sig_event(void)
{
	return (EXIT_SUCCESS);
}

void	set_signal_handler(int signum, void (*handler)(int))
{
	struct sigaction	sa;

	rl_event_hook = sig_event;
	sa.sa_handler = handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(signum, &sa, NULL);
}
