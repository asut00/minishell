/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:59:37 by asuteau           #+#    #+#             */
/*   Updated: 2024/05/29 09:59:42 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_front_env_var(t_env_var **lst, t_env_var *new)
{
	if (lst)
	{
		if (*lst)
			new->next = *lst;
		*lst = new;
	}
	else
		return ;
}

/*
#include <stdio.h>

void ft_lstprint(t_list *lst)
{
    while (lst)
    {
        printf("%s -> ", (char *)lst->content);
        lst = lst->next;
    }
    printf("NULL\n");
}

int main()
{
    t_list *elem1 = ft_lstnew("world");
    t_list *elem2 = ft_lstnew("hello");

    t_list *list = elem1;

    printf("Liste avant l'ajout :\n");
    ft_lstprint(list);

    ft_lstadd_front(&list, elem2);

    printf("Liste après l'ajout :\n");
    ft_lstprint(list);

    free(elem1);
    free(elem2);

    return 0;
}
*/