/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchmouk <rchmouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:45:24 by rchmouk           #+#    #+#             */
/*   Updated: 2023/04/16 21:21:25 by rchmouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	ft_count_arg(char **container, int j)
{
	int in;
	int	out;
	int ap;
	int	herd;
	int x;
	
	in = 0;
	out = 0;
	ap = 0;
	herd = 0;
	x = 0;
	
	while (container[j] && ft_strncmp(container[j], "|",ft_strlen(container[j])) != 0)
	{
		if (ft_strncmp(container[j], "<", ft_strlen(container[j])) == 0)
			in = 1;
		else if (ft_strncmp(container[j], ">", ft_strlen(container[j])) == 0)
			out = 1;
		else if (ft_strncmp(container[j], ">>", ft_strlen(container[j])) == 0)
			ap = 1;
		else if (ft_strncmp(container[j], "<<", ft_strlen(container[j])) == 0)
			herd = 1;
		else if (in == 1)
			in = 0;
		else if (out == 1)
			out = 0;
		else if (ap == 1)
			ap = 0;
		else if (herd == 1)
			herd = 0;
		else
			x++;
		
		j++;
	}
	return x;
}

void	print_dubl(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putstr_fd(str[i], 1);
		printf("\n");
		i++;
	}
	printf("\n");
}

typedef struct s_fill
{
	int	in;
	int	out;
	int	ap;
	int	herd;
	int	arg;
	int	in_count;
	int	out_count;
	int	ap_count;
	int	herd_count;
	int	arg_count;
	int	in_index;
	int	out_index;
	int	ap_index;
	int	herd_index;
	int	arg_index;

}		t_fill;

int	*string_to_nbr(char *str)
{
	int	i;
	int	len;
	int	*nb_str;
	int	lock;

	i = 0;
	lock = 0;
	len = ft_strlen(str);
	nb_str = calloc(sizeof(int), len);
	while (i < len)
	{
		if (lock == 0)
		{
			if (str[i] == ' ')
				nb_str[i] = 1;
			else if (str[i] == '<' || str[i] == '>' || str[i] == '|')
				nb_str[i] = 2;
			else if (str[i] == '\"')
				lock = 1;
		}
		else if (str[i] == '\"')
			lock = 0;
		i++;
	}
	return (nb_str);
}

t_parc	*ft_fill_node(char **container,int x)
{
	t_parc		*all;
	t_fill		a;
	static int	i;
	static int	j;

	if(x == 1)
	{
		i = 0;
		j = 0;
		return NULL;
	}
	a.in = 0;
	a.out = 0;
	a.ap = 0;
	a.herd = 0;
	a.arg = 0;
	a.in_count = 0;
	a.out_count = 0;
	a.ap_count = 0;
	a.herd_count = 0;
	a.arg_count = 0;
	a.in_index = 0;
	a.out_index = 0;
	a.ap_index = 0;
	a.herd_index = 0;
	a.arg_index = 0;
	all = malloc(sizeof(t_parc));
	if(j > 0)
		j++;
	a.arg_count = ft_count_arg(container, j); 
	while (container[j] && ft_strncmp(container[j], "|",ft_strlen(container[j])) != 0)
	{
		if (ft_strncmp(container[j], "<", ft_strlen(container[j])) == 0)
			a.in_count++;
		else if (ft_strncmp(container[j], ">", ft_strlen(container[j])) == 0)
			a.out_count++;
		else if (ft_strncmp(container[j], ">>", ft_strlen(container[j])) == 0)
			a.ap_count++;
		else if (ft_strncmp(container[j], "<<", ft_strlen(container[j])) == 0)
			a.herd_count++;
		j++;
	}
	all->infile = malloc(sizeof(char *) * (a.in_count + 1));
	all->outfile = malloc(sizeof(char *) * (a.out_count + 1));
	all->apend = malloc(sizeof(char *) * (a.ap_count + 1));
	all->heredoc = malloc(sizeof(char *) * (a.herd_count + 1));
	all->arg = malloc(sizeof(char *) * (a.arg_count + 1));
	if(i > 0)
		i++;
	while (container[i] && ft_strncmp(container[i], "|",ft_strlen(container[i])) != 0)
	{
		if (ft_strncmp(container[i], "<", ft_strlen(container[i])) == 0)
			a.in = 1;
		else if (ft_strncmp(container[i], ">", ft_strlen(container[i])) == 0)
			a.out = 1;
		else if (ft_strncmp(container[i], ">>", ft_strlen(container[i])) == 0)
			a.ap = 1;
		else if (ft_strncmp(container[i], "<<", ft_strlen(container[i])) == 0)
			a.herd = 1;
		else if (a.in == 1)
		{
			all->infile[a.in_index++] = container[i];
			a.in = 0;
		}
		else if (a.out == 1)
		{
			all->outfile[a.out_index++] = container[i];
			a.out = 0;
		}
		else if (a.ap == 1)
		{
			all->apend[a.ap_index++] = container[i];
			a.ap = 0;
		}
		else if (a.herd == 1)
		{
			all->heredoc[a.herd_index++] = container[i];
			a.herd = 0;
		}
		else
			all->arg[a.arg_index++] = container[i];
		i++;
	}
	all->infile[a.in_count] = NULL;
	all->outfile[a.out_count] = NULL;
	all->apend[a.ap_count] = NULL;
	all->heredoc[a.herd_count] = NULL;
	all->arg[a.arg_count] = NULL;
	all->next = NULL;
	return (all);
}

t_parc	*ft_fill_lst(char **container)
{
	t_parc *lst;
	int i;

	lst = ft_fill_node(container, 0);
	i = 0;
	while(container[i])
	{
		if(ft_strncmp(container[i], "|", ft_strlen(container[i])) == 0)
			break;
		i++;
	}
	while(container[i])
	{
		if(ft_strncmp(container[i], "|", ft_strlen(container[i])) == 0)
			ft_lst_add_back(lst, ft_fill_node(container, 0));
		i++;
	}
	ft_fill_node(container, 1);
	return lst;
}

char  *ft_var(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if(str[i] == '=')
			break;
		i++;
	}
	return (ft_substr(str, 0, i));
}

char  *ft_val(char *str)
{
	int i;
	int start;

	i = 0;
	while(str[i])
	{
		if(str[i] == '=')
			break;
		i++;
	}
	start = i + 1;
	return(ft_substr(str, start, ft_strlen(str) - start));
}

t_env *ft_fill_lst2(char **env)
{
	int i;
	t_env *new;
	t_env *tmp;

	i = 0;
	tmp = malloc(sizeof(t_env));
	tmp->var = ft_var(env[i]);
	tmp->val = ft_val(env[i]);
	tmp->next = NULL;
	new = tmp;
	while(env[i])
	{
		tmp = malloc(sizeof(t_env));
		tmp->var = ft_var(env[i]);
		tmp->val = ft_val(env[i]);
		tmp->next = NULL;
		ft_lst_add_back2(new, tmp);
		i++;
	}
	return(new);
}

int	main(int ac, char **av, char **env)
{
	char	*buffer;
	int		*nb_str;
	char	**container;
	t_parc *all;
	t_env *list;
	// int i = 0;
	// int len;

	while (ac && av)
	{
		buffer = readline(">minishell: ");
		if(buffer[0])
			add_history(buffer);
		list = ft_fill_lst2(env);
		buffer = ft_expand(buffer, list);
		nb_str = string_to_nbr(buffer);
		// len = ft_strlen(buffer);
		// printf(">>>>>>>>>>>>");
		// i = 0;
		// while (i < len)
		// {
		// 	printf("%d", nb_str[i++]);
		// }
		printf("\n");
		container = split_pro_max(nb_str, buffer);
		all = ft_fill_lst(container);
		// while (all)
		// {
		// 	print_dubl(all->infile);
		// 	print_dubl(all->outfile);
		// 	print_dubl(all->apend);
		// 	print_dubl(all->heredoc);
		// 	print_dubl(all->arg);
		// 	printf("==========\n");
		// 	all = all->next;
		// }
	}
	return (0);
}

