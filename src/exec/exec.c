/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:41:22 by thelaine          #+#    #+#             */
/*   Updated: 2024/07/18 12:06:42 by thelaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_sig;

static int	check_for_last_pipe(char *input)
{
	int	last_type;

	last_type = NOT_DEFINED;
	while (*input)
	{
		while (ft_is_whitespace(*input))
			input++;
		if (*input == '\'' || *input == '\"')
			input += skip_quotes(input, &last_type);
		else if (*input == '|')
		{
			input++;
			last_type = PIPELINE;
		}
		else if (*input)
		{
			last_type = NOT_DEFINED;
			input++;
		}
	}
	return (last_type);
}

static void	execute_command(t_var *var)
{
	parsing(var);
	if (!var->commands)
		return ;
	var->saved_stdin = dup(STDIN_FILENO);
	if (var->saved_stdin == -1)
		clear_all_and_exit(var, 2);
	var->saved_stdout = dup(STDOUT_FILENO);
	if (var->saved_stdout == -1)
		clear_all_and_exit(var, 2);
	pre_expand(var);
	expand(var);
	lexing(var);
	check_heredoc(var);
	add_history(var->input);
	create_env_for_exec(var);
	pipex_init(var);
	pipex_execute_cmds(var);
	if (dup2(var->saved_stdin, STDIN_FILENO) == -1
		|| dup2(var->saved_stdout, STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("mnsh: dup2 error\n", STDERR_FILENO);
		clear_all_and_exit(var, STDERR_FILENO);
	}
	close(var->saved_stdin);
	close(var->saved_stdout);
}

static int	inside_loop(t_var *var, int *last_type, int first_loop)
{
	char	*input;

	check_quotes(var);
	if (g_sig != KEEP_GOING || !check_command_error(var))
		return (0);
	*last_type = check_for_last_pipe(var->input);
	if (!first_loop)
	{
		input = ft_readline("pipe> ", var, PIPELINE);
		var->input = ft_strjoin(var->input, " ", var);
		var->input = ft_strjoin(var->input, input, var);
		ft_free(var, input);
		if (!check_command_error(var))
			return (0);
		check_quotes(var);
		*last_type = check_for_last_pipe(var->input);
	}
	return (1);
}

static void	readline_loop(t_var *var)
{
	int		last_type;
	int		check_command_error;

	last_type = 0;
	set_signal_handler(SIGINT, signal_handler_special);
	check_command_error = inside_loop(var, &last_type, 1);
	while (g_sig == KEEP_GOING && last_type == PIPELINE && check_command_error)
		check_command_error = inside_loop(var, &last_type, 0);
	set_signal_handler(SIGINT, signal_handler_parent_after_readline);
	if (g_sig == KEEP_GOING && check_command_error)
		execute_command(var);
	else if (!check_command_error)
	{
		add_history(var->input);
		ft_change_env_var(var, "?", "2");
		var->last_cmd_exit_status = 2;
	}
	if (g_sig == STOP_INT)
		ft_change_env_var(var, "?", "130");
	if (g_sig == STOP_QUIT)
		ft_change_env_var(var, "?", "131");
	ft_cleargarbage(var);
}

void	exec(t_var *var)
{
	var->input = NULL;
	while (1)
	{
		set_signal_handler(SIGINT, signal_handler_parent);
		set_signal_handler(SIGQUIT, SIG_IGN);
		var->input = ft_readline("minishell> ", var, MAIN);
		if (ft_strlen(var->input) > 0)
			readline_loop(var);
	}
	return ;
}
