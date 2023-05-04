/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchmouk <rchmouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 05:49:49 by rchmouk           #+#    #+#             */
/*   Updated: 2023/04/09 08:36:58 by rchmouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void    ft_replace(char **str, int i, t_env *env)
{
    char    *tmp;
    int     start;
    char    *s1;
    char    *s3;
    char    *big;

    start = i;
    s1 = NULL;
    s3 = NULL;
    big = NULL;
    i++;
    while ((*str)[i] && (*str)[i] != ' ' && (ft_isalpha((*str)[i]) == 1 || ft_isdigit((*str)[i] == 1)))
        i++;
    tmp = ft_substr(*str, start + 1, i - start - 1 );

    while (env)
    {
        if (ft_strncmp(tmp, env->var, ft_strlen(tmp)) == 0 && ft_strlen(tmp) == ft_strlen(env->var))
            break;        
        env = env->next;
    }
    if (env)
    {
        s1 = ft_substr(*str, 0, start);
        s3 = ft_substr(*str, i, ft_strlen(*str) - i);
        s1 = ft_strjoin(s1, env->val);
        big = ft_strjoin(s1, s3);
        *str = big;
    }    
}

char    *ft_expand(char *str, t_env *env)
{
    int i;
    
    i = 0;
    while (str[i])
    {
        
        if(str[i] == '\"')
        {
            i++;
            while (str[i] && str[i] != '\"')
            {
                if(str[i] == '$')
                    ft_replace(&str, i, env);
                i++;
            }
        }
        else if (str[i] == '\'')
        {
            i++;
            while (str[i] && str[i] != '\'')
                i++;
            if(str[i] == '\'')
                i++;
        }
        else
        {
            while (str[i] && str[i] != '\'' && str[i] != '\"')
            {
                if(str[i] == '$')
                    ft_replace(&str, i, env);
                i++;
            }
        }
    }
    return str;
}