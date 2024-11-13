/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list_manipulator.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:50:46 by thelaine          #+#    #+#             */
/*   Updated: 2024/07/16 17:37:17 by thelaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_commands	*ft_cmdnew(char *word, t_var *var)
{
	t_commands	*new_elem;

	(void)var;
	new_elem = (t_commands *)ft_malloc(1, sizeof(t_commands), var);
	new_elem->word = word;
	new_elem->type = -1;
	new_elem->next = 0;
	return (new_elem);
}

t_commands	*ft_cmdlast(t_commands *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_cmdadd_back(t_commands **lst, t_commands *new)
{
	t_commands	*elem;

	if (!new || !lst)
		return ;
	if (*lst)
	{
		elem = ft_cmdlast(*lst);
		elem->next = new;
	}
	else
		*lst = new;
}

void	ft_cmdadd_next(t_commands *current, t_commands *new)
{
	new->next = current->next;
	current->next = new;
}

void	ft_cmdlst_free(t_var *var)
{
	t_commands	*elem1;
	t_commands	*elem2;

	(void)var;
	if (!(var->commands))
		return ;
	elem1 = var->commands;
	while (elem1)
	{
		elem2 = elem1->next;
		if (elem1->word)
			ft_free(var, elem1->word);
		ft_free(var, elem1);
		elem1 = elem2;
	}
	var->commands = 0;
}
