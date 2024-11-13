/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_expanded.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:01:29 by thelaine          #+#    #+#             */
/*   Updated: 2024/08/28 16:01:40 by thelaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_charset(t_var *pvar)
{
	char	*charset;

	charset = ft_malloc(6, sizeof(char), pvar);
	charset[0] = 9;
	charset[1] = 11;
	charset[2] = 12;
	charset[3] = 13;
	charset[4] = 32;
	charset[5] = '\0';
	return (charset);
}

void	write_dollar(t_commands **c, char **f_word, t_var *var, char *var_value)
{
	t_commands	*new_c;
	char		**var_value_splitted;
	int			i;
	char		*charset;

	i = 0;
	if (!var_value)
		return ;
	charset = create_charset(var);
	var_value_splitted = ft_split(var_value, charset, var);
	*f_word = ft_strjoin(*f_word, var_value_splitted[i++], var);
	while (var_value_splitted[i] != 0)
	{
		new_c = ft_cmdnew(var_value_splitted[i], var);
		ft_cmdadd_next(*c, new_c);
		new_c->type = ARGS;
		new_c->word = (*c)->word;
		(*c)->word = *f_word;
		*f_word = var_value_splitted[i++];
		*c = new_c;
	}
}
