/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:49:57 by thelaine          #+#    #+#             */
/*   Updated: 2024/07/11 18:05:56 by thelaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig;

static void	main_init(t_var *var, char **env)
{
	g_sig = KEEP_GOING;
	var->env_var = NULL;
	var->commands = 0;
	var->garbage_collector = 0;
	var->heredocs = 0;
	var->last_cmd_exit_status = EXIT_SUCCESS;
	var->line_memory = 0;
	var->first_line = 0;
	var->heredocs = 0;
	var->do_the_exec = TRUE;
	var->saved_stdin = -1;
	var->saved_stdout = -1;
	var_init(var, env);
}

int	main(int ac, char **av, char **env)
{
	t_var		var;

	(void)ac;
	(void)av;
	main_init(&var, env);
	exec(&var);
	return (0);
}
