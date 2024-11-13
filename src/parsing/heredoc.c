/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:10:08 by thelaine          #+#    #+#             */
/*   Updated: 2024/07/16 14:29:33 by thelaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_sig;

static char	*get_input(int *first_loop, t_var *var, char *input, char *heredoc)
{
	if (*first_loop)
	{
		var->input = ft_strjoin(var->input, "\n", var);
		*first_loop = 0;
	}
	heredoc = ft_strjoin(heredoc, input, var);
	heredoc = ft_strjoin(heredoc, "\n", var);
	ft_free(var, input);
	return (heredoc);
}

static char	*get_heredoc(t_var *var, char *lim)
{
	char	*input;
	char	*heredoc;
	int		first_loop;

	first_loop = 1;
	heredoc = ft_malloc(1, sizeof(char), var);
	heredoc[0] = '\0';
	set_signal_handler(SIGINT, signal_handler_special);
	input = ft_readline("heredoc>", var, HEREDOC);
	while (g_sig == KEEP_GOING && ft_strcmp(input, lim))
	{
		heredoc = get_input(&first_loop, var, input, heredoc);
		input = ft_readline("heredoc>", var, HEREDOC);
		if (g_sig != KEEP_GOING)
			break ;
	}
	var->input = ft_strjoin(var->input, heredoc, var);
	var->input = ft_strjoin(var->input, input, var);
	ft_free(var, input);
	return (heredoc);
}

static void	init_heredoc(t_var *var)
{
	char		**heredocs;
	int			i;
	int			len;
	char		*itoa;
	t_commands	*command;

	i = 0;
	len = 0;
	command = var->commands;
	while (command)
	{
		if (command->type == HEREDOC)
			len ++;
		command = command->next;
	}
	heredocs = ft_malloc(len + 1, sizeof(char *), var);
	while (i < len)
	{
		itoa = ft_itoa(i, var);
		heredocs[i] = ft_strjoin_no_free(".file_tmp_", itoa, var);
		ft_free(var, itoa);
		i++;
	}
	heredocs[i] = NULL;
	var->heredocs = heredocs;
}

static void	create_file(char *content, t_var *var, int i)
{
	int		fd;
	char	*heredoc_name;

	heredoc_name = var->heredocs[i];
	fd = open(heredoc_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("error creating temporary file, abort command\n",
			STDERR_FILENO);
		clear_all_and_exit(var, 2);
	}
	ft_putstr_fd(content, fd);
	close(fd);
}

void	check_heredoc(t_var *var)
{
	t_commands	*command;
	char		*lim;
	char		*content;
	int			i;

	i = 0;
	init_heredoc(var);
	command = var->commands;
	while (command)
	{
		if (command->type == HEREDOC)
		{
			lim = (command->next)->word;
			ft_free(var, command->word);
			content = get_heredoc(var, lim);
			create_file(content, var, i);
			ft_free(var, command->word);
			command->word = var->heredocs[i];
			command->type = FILE_IN;
			i++;
		}
		command = command->next;
	}
}
