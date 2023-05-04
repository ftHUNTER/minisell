/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchmouk <rchmouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 19:40:41 by rchmouk           #+#    #+#             */
/*   Updated: 2023/04/09 06:49:15 by rchmouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_list
{
	char			**infile;
	char			**outfile;
	char			**apend;
	char			**heredoc;
	char			**arg;
	struct s_list	*next;
}					t_parc;

typedef struct s_list2
{
	char			*var;
	char			*val;
	struct s_list2	*next;
}					t_env;

int					ft_count(char *str, char c);
char				*ft_put(char *str, int x, char c);
t_parc				*ft_lst_last(t_parc *lst);
void				ft_lst_add_back(t_parc *lst, t_parc *new);
t_parc				*ft_lst_new(char *arg, int index);
char				**split_pro_max(int *tab, char *str);
char				*ft_expand(char *str, t_env *env);
char				**split_pro_max(int *tab, char *str);
void				ft_lst_add_back2(t_env *lst, t_env *new);

#endif
