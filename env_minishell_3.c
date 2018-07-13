/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_minishell_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 15:28:19 by rsibiet           #+#    #+#             */
/*   Updated: 2016/02/15 19:39:50 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			end_2_ft_env_2(char **c, t_env *e, int i)
{
	static char		**s;

	s = NULL;
	while (c[i] != NULL)
	{
		s = ft_strsplit(c[i], '=');
		ft_env_3(c, e, s, i);
		i++;
	}
	ft_putendl_endl(e->env);
}

static void		endb_ft_env_2(char **c, t_env *e, int i, int j)
{
	while (c[j + i] != NULL)
	{
		ft_strdel(&(c[j]));
		c[j] = ft_strdup(c[j + i]);
		j++;
	}
	while (c[j] != NULL)
	{
		ft_strdel(&(c[j]));
		j++;
	}
	e->av = ft_strdup_dup(c);
	ft_strdel(&(e->name));
	e->name = ft_strdup(c[0]);
}

void			end_ft_env_2(char **c, t_env *e, int i)
{
	static char		**s;

	s = NULL;
	if (s == NULL && c[1] != NULL)
		s = ft_strsplit(c[1], '=');
	while (s != NULL && s[1] != NULL && c[i] != NULL)
	{
		ft_strdel_del(&s);
		s = ft_strsplit(c[i], '=');
		i++;
	}
	if (s != NULL)
		ft_strdel_del(&s);
	if (i > 2)
		i--;
	endb_ft_env_2(c, e, i, 0);
}
