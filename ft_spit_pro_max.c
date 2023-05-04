/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spit_pro_max.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchmouk <rchmouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 05:59:10 by rchmouk           #+#    #+#             */
/*   Updated: 2023/04/06 22:36:34 by rchmouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count(int *tab, int len)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while(i < len)
	{
		if(tab[i] == 2)
		{
			while(i < len && tab[i] == 2)
				i++;
			count++;
		}
		else if(tab[i] == 0)
		{
			while(i < len && tab[i] == 0)
				i++;
			count++;			
		}
		else if(tab[i] == 3)
		{
			while(i < len && tab[i] == 3)
				i++;
			count++;			
		}
		else
			i++;
	}
	return count;
}

char	*ft_get_str(char *str, int *tab, int size, int bool)
{
	static int x;
	int len;
	int start;
	
	len = 0;
	start = 0;
	if (bool == 1)
	{
		x = 0;
		return NULL;
	}
	while(x < size)
	{
		if (tab[x] == 0)
		{
			start = x;
			while (x < size && tab[x] == 0)
				x++;
			len = x;
			break;
		}
		else if (tab[x] == 2)
		{
			start = x;
			while (x < size && tab[x] == 2)
				x++;
			len = x;
			break;
		}
		else if (tab[x] == 3)
		{
			start = x;
			while (x < size && tab[x] == 3)
				x++;
			len = x;
			break;
		}
		else
			x++;
	}
	return(ft_substr(str, start, len - start));
}

char	**split_pro_max(int *tab, char *str)
{
	int len;
	int nb;
	char 	**container;
	int i;

	i = 0;
	len = ft_strlen(str);
	nb = count(tab, len);
	container = ft_calloc(sizeof(char *), (nb + 1));
	while (i < nb)
	{
		container[i] = ft_get_str(str, tab, len, 0);
		i++;
	}
	container[i] = ft_get_str(str, tab, len, 1);
	return(container);
}