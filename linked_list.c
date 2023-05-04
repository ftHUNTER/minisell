/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchmouk <rchmouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 18:51:06 by rchmouk           #+#    #+#             */
/*   Updated: 2023/04/09 02:02:15 by rchmouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parc	*ft_lst_last(t_parc *lst)
{
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lst_add_back(t_parc *lst, t_parc *new)
{
	if (lst == NULL)
	{
		lst = new; 
	}
	else
		(ft_lst_last(lst))->next = new;
}

t_env	*ft_lst_last2(t_env *lst)
{
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lst_add_back2(t_env *lst, t_env *new)
{
	if (lst == NULL)
	{
		lst = new; 
	}
	else
		(ft_lst_last2(lst))->next = new;
}
